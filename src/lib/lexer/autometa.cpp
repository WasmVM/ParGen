// Copyright 2024 Luis Hsu
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     https://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <ParGen.hpp>
#include <Util.hpp>
#include <exception.hpp>

#include "lexer.hpp"

#include <stack>
#include <map>
#include <queue>
#include <algorithm>

Autometa::Action::Flags& operator|=(Autometa::Action::Flags& lhs, const Autometa::Action::Flags&& rhs){
    return lhs = (Autometa::Action::Flags)((uint8_t)lhs | (uint8_t)rhs);
}

struct FiniteState {
    using Edge = std::pair<std::optional<CharType>, size_t>;
    Autometa::StateType type;
    std::list<Edge> edges;
};

static std::deque<FiniteState>* create_nfa(Node* root, std::deque<FiniteState>* nfa = nullptr){
    bool initial = (nfa == nullptr);
    if(initial){
        nfa = new std::deque<FiniteState>{
            FiniteState{.type = Autometa::StateType::Error},
            FiniteState{.type = Autometa::StateType::Start},
        };
    }
    Node* cur = root;
    while(cur != nullptr){
        switch(cur->type){
            case Node::Char:{
                CharNode* node = (CharNode*)cur;
                std::list<FiniteState*> accepted;
                for(size_t m = 0; m < std::max(std::max(node->min, (size_t)1), node->max); ++m){
                    FiniteState& back = nfa->back();
                    // Create state
                    if(node->char_type.negate){
                        CharType ch = node->char_type;
                        ch.negate = false;
                        back.edges.emplace_back(FiniteState::Edge{ch, 0});
                        back.edges.emplace_back(FiniteState::Edge{'\0', nfa->size()});
                    }else{
                        back.edges.emplace_back(FiniteState::Edge{node->char_type, nfa->size()});
                    }
                    nfa->emplace_back();
                    // Add accepted edges
                    if(m >= node->min){
                        accepted.emplace_back(&back);
                    }
                }
                size_t end_id = nfa->size() - 1;
                // Handle loop
                if(node->max == 0){
                    FiniteState& back = nfa->back();
                    if(node->char_type.negate){
                        CharType ch = node->char_type;
                        ch.negate = false;
                        back.edges.emplace_back(FiniteState::Edge{ch, 0});
                        back.edges.emplace_back(FiniteState::Edge{'\0', end_id});
                    }else{
                        back.edges.emplace_back(FiniteState::Edge{node->char_type, end_id});
                    }
                }
                // Link accepted states to end
                for(FiniteState* state : accepted){
                    state->edges.emplace_back(FiniteState::Edge{std::nullopt, end_id});
                }
            }break;
            case Node::Group:{
                GroupNode* node = (GroupNode*)cur;
                if(!node->children.empty()){
                    std::list<FiniteState*> accepted;
                    size_t last_start = nfa->size() - 1;
                    for(size_t m = 0; m < std::max(std::max(node->min, (size_t)1), node->max); ++m){
                        FiniteState* start = &nfa->back();
                        last_start = nfa->size() - 1;
                        // Create states
                        if(node->children.size() == 1){
                            // One child
                            create_nfa(node->children.front(), nfa);
                        }else{
                            // Multiple children
                            std::list<FiniteState*> child_ends;
                            for(Node* child : node->children){
                                start->edges.emplace_back(FiniteState::Edge{std::nullopt, nfa->size()});
                                nfa->emplace_back();
                                create_nfa(child, nfa);
                                child_ends.emplace_back(&nfa->back());
                            }
                            size_t child_end_id = nfa->size();
                            // Add final end state
                            nfa->emplace_back();
                            // Link every end to final end state
                            for(FiniteState* end : child_ends){
                                end->edges.emplace_back(FiniteState::Edge{std::nullopt, child_end_id});
                            }
                        }
                        // Add accepted edges
                        if(m >= node->min){
                            accepted.emplace_back(start);
                        }
                    }
                    size_t end_id = nfa->size() - 1;
                    // Handle loop
                    if(node->max == 0){
                        nfa->back().edges.emplace_back(FiniteState::Edge{std::nullopt, last_start});
                    }
                    // Link accepted states to end
                    for(FiniteState* state : accepted){
                        state->edges.emplace_back(FiniteState::Edge{std::nullopt, end_id});
                    }
                }
            }break;
        }
        cur = cur->next;
    }
    // Mark final state
    if(initial){
        nfa->back().type = Autometa::StateType::Final;
    }
    return nfa;
}

static std::deque<FiniteState>* create_dfa(std::deque<FiniteState>* nfa){
    if(nfa->size() < 2){
        return nfa->empty() ? (new std::deque<FiniteState>()) : (new std::deque<FiniteState>(*nfa));
    }

    // Compute e-closure
    std::vector<std::set<size_t>> e_closure(nfa->size());
    for(size_t state_id = 0; state_id < nfa->size(); ++state_id){
        std::set<size_t>& e_states = e_closure[state_id];
        std::stack<size_t> id_stack;
        id_stack.push(state_id);
        while(!id_stack.empty()){
            e_states.emplace(id_stack.top());
            FiniteState& state = nfa->at(id_stack.top());
            id_stack.pop();
            for(FiniteState::Edge& edge : state.edges){
                if(!edge.first.has_value()){
                    id_stack.push(edge.second);
                }
            }
        }
    }
    
    // Create DFA
    std::deque<FiniteState>* dfa = new std::deque<FiniteState> {
        FiniteState{.type = Autometa::StateType::Start}
    };
    std::map<std::set<size_t>, size_t> index_map {{e_closure.at(1), 0}};
    std::queue<std::set<size_t>> set_queue;
    set_queue.emplace(e_closure.at(1));
    while(!set_queue.empty()){
        std::set<size_t> state_set = set_queue.front();
        set_queue.pop();
        // Collect e_closure for each input of transitions
        std::unordered_map<char, std::set<size_t>> transitions;
        for(size_t state_id : state_set){
            for(FiniteState::Edge& edge : nfa->at(state_id).edges){
                if(edge.first.has_value()){
                    for(char ch : edge.first.value()){
                        std::set<size_t>& closure = e_closure[edge.second];
                        transitions[ch].insert(closure.begin(), closure.end());
                    }
                }
            }
        }
        // Transitions
        FiniteState& state = dfa->at(index_map[state_set]);
        for(std::pair<char, std::set<size_t>> transition : transitions){
            // Create new state
            if(!index_map.contains(transition.second)){
                index_map.emplace(transition.second, dfa->size());
                dfa->emplace_back();
                set_queue.emplace(transition.second);
            }
            // Link transition
            state.edges.emplace_back(transition.first, index_map[transition.second]);
        }
    }
    
    // Mark finals
    std::set<size_t> error_set, final_set;
    for(size_t i = 0; i < nfa->size(); ++i){
        if(nfa->at(i).type == Autometa::StateType::Final){
            final_set.emplace(i);
        }else if(nfa->at(i).type == Autometa::StateType::Error){
            error_set.emplace(i);
        }
    }
    for(auto map_pair : index_map){
        std::set<size_t> inter;
        // Error
        std::set_intersection(
            map_pair.first.begin(), map_pair.first.end(),
            error_set.begin(), error_set.end(), 
            std::inserter(inter, inter.end())
        );
        if(!inter.empty()){
            dfa->at(map_pair.second).type = Autometa::StateType::Error;
        }
        // Final
        inter.clear();
        std::set_intersection(
            map_pair.first.begin(), map_pair.first.end(),
            final_set.begin(), final_set.end(), 
            std::inserter(inter, inter.end())
        );
        if(!inter.empty()){
            dfa->at(map_pair.second).type = Autometa::StateType::Final;
        }
    }

    return dfa;
}

std::ostream& operator<< (std::ostream& os, std::deque<FiniteState>& nfa){
    size_t i = 0;
    for(FiniteState& state : nfa){
        os << "S" << i;
        switch(state.type){
            case Autometa::StateType::Final:
                os << " [shape = doublecircle]";
            break;
            case Autometa::StateType::Start:
                os << " [shape = diamond]";
            break;
            case Autometa::StateType::Error:
                os << " [shape = doubleoctagon]";
            break;
            default:
                os << " [shape = circle]";
            break;
        }
        os << ";" << std::endl;
        for(FiniteState::Edge& edge: state.edges){
            os << "S" << i << "-> S" << edge.second << " [label=\"";
            if(edge.first.has_value()){
                os << edge.first.value();
            }else{
                os << "null";
            }
            os << "\"];" << std::endl;
        }
        ++i;
    }
    return os;
}

static void prune_state(std::deque<Autometa::State>& states){
    if(states.size() < 2){
        return;
    }
    // Compute e-closure
    std::vector<std::set<size_t>> e_closure(states.size());
    for(size_t state_id = 0; state_id < states.size(); ++state_id){
        std::set<size_t>& e_states = e_closure[state_id];
        std::stack<size_t> id_stack;
        id_stack.push(state_id);
        while(!id_stack.empty()){
            e_states.emplace(id_stack.top());
            Autometa::State& state = states.at(id_stack.top());
            id_stack.pop();
            for(auto& edge : state){
                if(!edge.first.has_value()){
                    id_stack.push(edge.second);
                }
            }
        }
    }
    
    // Create DFA
    std::deque<Autometa::State> pruned;
    pruned.emplace_back().type = Autometa::StateType::Start;
    std::map<std::set<size_t>, size_t> index_map {{e_closure.at(0), 0}};
    std::queue<std::set<size_t>> set_queue;
    set_queue.emplace(e_closure.at(0));
    while(!set_queue.empty()){
        std::set<size_t> state_set = set_queue.front();
        set_queue.pop();
        // Collect e_closure for each input of transitions
        std::unordered_map<char, std::set<size_t>> transitions;
        for(size_t state_id : state_set){
            for(auto& edge : states.at(state_id)){
                if(edge.first.has_value()){
                    std::set<size_t>& closure = e_closure[edge.second];
                    transitions[edge.first.value()].insert(closure.begin(), closure.end());
                }
            }
        }
        // Transitions
        Autometa::State& state = pruned.at(index_map[state_set]);
        for(std::pair<char, std::set<size_t>> transition : transitions){
            // Create new state
            if(!index_map.contains(transition.second)){
                index_map.emplace(transition.second, pruned.size());
                pruned.emplace_back();
                set_queue.emplace(transition.second);
            }
            // Link transition
            state.emplace_back(transition.first, index_map[transition.second]);
        }
    }
    
    // Mark finals
    std::set<size_t> error_set, final_set;
    for(size_t i = 0; i < states.size(); ++i){
        if(states.at(i).type == Autometa::StateType::Final){
            final_set.emplace(i);
        }else if(states.at(i).type == Autometa::StateType::Error){
            error_set.emplace(i);
        }
    }
    for(auto map_pair : index_map){
        std::set<size_t> inter;
        Autometa::State& pruned_state = pruned.at(map_pair.second);
        // Error
        std::set_intersection(
            map_pair.first.begin(), map_pair.first.end(),
            error_set.begin(), error_set.end(), 
            std::inserter(inter, inter.end())
        );
        if(!inter.empty()){
            pruned_state.type = Autometa::StateType::Error;
        }
        // Final
        inter.clear();
        std::set_intersection(
            map_pair.first.begin(), map_pair.first.end(),
            final_set.begin(), final_set.end(), 
            std::inserter(inter, inter.end())
        );
        if(!inter.empty()){
            pruned_state.type = Autometa::StateType::Final;
        }
        // action
        for(size_t state_id : map_pair.first){
            Autometa::State& state = states.at(state_id);
            if(state.action_id && (!pruned_state.action_id.has_value() || pruned_state.action_id.value() > state.action_id)){
                pruned_state.action_id = state.action_id;
            }
        }
    }

    // Save
    states.swap(pruned);
}

static std::deque<Autometa::State> create_states(Autometa& autometa, Pargen::Rule& rule, bool debug = false, std::string prefix = ""){
    static int rule_id = 0;
    // Parse pattern to Nodes
    std::shared_ptr<Node> root(parse_pattern(rule.pattern));
    // Nodes to NFA
    std::shared_ptr<std::deque<FiniteState>> finites(create_nfa(root.get()));
    // NFA to DFA
    finites = std::shared_ptr<std::deque<FiniteState>>(create_dfa(finites.get()));
    rule_id += 1;
    // Action
    size_t action_id = autometa.actions.size();
    Autometa::Action& action = autometa.actions.emplace_back();
    if(rule.more){
        action.flags = Autometa::Action::More;
    }
    if(rule.pop){
        action.flags |= Autometa::Action::Pop;
    }
    action.push = rule.push;
    action.content = rule.content;
    // DFA to States
    std::deque<Autometa::State> states;
    for(FiniteState& finite_state : *finites.get()){
        Autometa::State& state = states.emplace_back();
        state.type = finite_state.type;
        if(state.type == Autometa::StateType::Final){
            state.action_id = action_id;
        }
        for(FiniteState::Edge finite_edge : finite_state.edges){
            if(finite_edge.first.has_value()){
                state.emplace_back(*finite_edge.first.value().begin(), finite_edge.second);
            }else{
                state.emplace_back(std::nullopt, finite_edge.second);
            }
        }
    }
    return states;
}

static std::deque<Autometa::State> expand_state(Autometa& autometa, std::unordered_map<std::string, size_t>& state_map, Pargen::State& state, bool debug = false){
    std::deque<Autometa::State> states;
    for(std::variant<Pargen::Rule, Pargen::Use, Pargen::State>& elem : state){
        std::visit(overloaded {
            [&](Pargen::Rule& rule){
                std::deque<Autometa::State> new_states = create_states(autometa, rule, debug, state.name + "_");
                size_t state_id = states.size();
                for(Autometa::State& state : new_states){
                    for(auto& edge : state){
                        edge.second += state_id;
                    }
                }
                states.insert(states.end(), new_states.begin(), new_states.end());
                if(state_map.contains(state.name)){
                    states[0].emplace_back(std::nullopt, state_id);
                }else{
                    state_map[state.name] = state_id;
                }
            },
            [&](Pargen::State& state){
                size_t state_id = states.size();
                std::unordered_map<std::string, size_t> new_map;
                std::deque<Autometa::State> new_states = expand_state(autometa, new_map, state, debug);
                prune_state(new_states);
                for(Autometa::State& state : new_states){
                    for(auto& edge : state){
                        edge.second += state_id;
                    }
                }
                for(auto& entry : new_map){
                    state_map[entry.first] = entry.second + state_id;
                }
                state_map[state.name] = state_id;
                states.insert(states.end(), new_states.begin(), new_states.end());
            },
            [](Pargen::Use&){}
        }, elem);
    }
    return states;
}

Autometa::Autometa(Lexer& lexer){
    resolve_use(lexer);
    std::deque<Autometa::State> init_states(1);
    for(std::variant<Pargen::Rule, Pargen::State>& elem : lexer){
        std::visit(overloaded {
            [&](Pargen::Rule& rule){
                std::deque<Autometa::State> new_states = create_states(*this, rule, lexer.parent.options.debug);
                size_t state_id = init_states.size();
                for(Autometa::State& state : new_states){
                    for(auto& edge : state){
                        edge.second += state_id;
                    }
                }
                init_states.insert(init_states.end(), new_states.begin(), new_states.end());
                if(state_id != 0){
                    init_states[0].emplace_back(std::nullopt, state_id);
                }
            },
            [&](Pargen::State& state){
                size_t state_id = states.size();
                std::unordered_map<std::string, size_t> new_map;
                std::deque<Autometa::State> new_states = expand_state(*this, new_map, state, lexer.parent.options.debug);
                prune_state(new_states);
                for(Autometa::State& state : new_states){
                    for(auto& edge : state){
                        edge.second += state_id;
                    }
                }
                for(auto& entry : new_map){
                    state_map[entry.first] = entry.second + state_id;
                }
                state_map[state.name] = state_id;
                states.insert(states.end(), new_states.begin(), new_states.end());
            }
        }, elem);
    }
    prune_state(init_states);
    size_t state_id = states.size();
    for(Autometa::State& state : init_states){
        for(auto& edge : state){
            edge.second += state_id;
        }
    }
    states.insert(states.end(), init_states.begin(), init_states.end());
    state_map[""] = state_id;
}

Autometa::State::State(const Autometa::State& state) :
    std::deque<std::pair<std::optional<char>, size_t>>(state)
{
    type = state.type;
    action_id = state.action_id;
}

std::ostream& operator<< (std::ostream& os, Autometa& autometa){

    static const auto print_char = [&](char ch){
        if(ch == '\0'){
            os << "'\\0'";
        }else if(std::isspace(ch)){
            switch(ch){
                case ' ':
                    os << "' '";
                break;
                case '\t':
                    os << "'\\t'";
                break;
                case '\r':
                    os << "'\\r'";
                break;
                case '\f':
                    os << "'\\f'";
                break;
                case '\v':
                    os << "'\\v'";
                break;
                case '\n':
                    os << "'\\n'";
                break;
            }
        }else if(ch == '\"'){
            os << "'\\\"'";
        }else if(ch == '\\'){
            os << "'\\\\'";
        }else{
            os << "'" << ch << "'";
        }
    };

    std::map<size_t, std::string> rev_map;
    for(auto& state_pair : autometa.state_map){
        rev_map[state_pair.second] = state_pair.first;
    }

    size_t state_id = 0;
    for(Autometa::State& state : autometa.states){
        if(rev_map.contains(state_id)){
            os << "    /* " << rev_map[state_id] << " */" << std::endl;
        }
        std::map<char, size_t> transitions;
        for(auto& transition : state){
            if(transition.first.has_value()){
                transitions[transition.first.value()] = transition.second;
            }
        }
        if(transitions.empty()){
            os << "    {}, // S" << state_id << std::endl;
        }else{
            os << "    {";
            auto start = transitions.begin();
            while(start != transitions.end()){
                auto end = std::adjacent_find(start, transitions.end(), 
                    [](const std::pair<char, size_t>& lhs, const std::pair<char, size_t>& rhs){
                        return (lhs.first == '\0') || (lhs.second != rhs.second) || (rhs.first != lhs.first + 1);
                    }
                );
                os << "{{";
                print_char(start->first);
                if(start != end && (end != transitions.end() || std::prev(end) != start)){
                    os << ",";
                    if(end == transitions.end()){
                        print_char(std::prev(end)->first);
                    }else{
                        print_char(end->first);
                    }
                }
                os << "}," << start->second << "}, ";
                if(end == transitions.end()){
                    break;
                }else{
                    start = std::next(end);
                }
            }
            os << "}, // S" << state_id << std::endl;
        }
        state_id += 1;
    }
    return os;
}

std::ostream& Autometa::dump(std::ostream& os){
    static const auto print_char = [&](char ch){
        if(ch == '\0'){
            os << "any";
        }else if(std::isspace(ch)){
            switch(ch){
                case ' ':
                    os << "'" << ch << "'";
                break;
                case '\t':
                    os << "\\\\t";
                break;
                case '\r':
                    os << "\\\\r";
                break;
                case '\f':
                    os << "\\\\f";
                break;
                case '\v':
                    os << "\\\\v";
                break;
                case '\n':
                    os << "\\\\n";
                break;
            }
        }else if(ch == '\"'){
            os << "'\\\"'";
        }else if(ch == '\\'){
            os << "'\\\\'";
        }else{
            os << "'" << ch << "'";
        }
    };
    size_t i = 0;
    for(Autometa::State& state : states){
        os << "S" << i << " [label=\"S" << i;
        for(auto& state_pair : state_map){
            if(!state_pair.first.empty() && i == state_pair.second){
                os << "\\n" << state_pair.first;
            }
        }
        if(state.action_id){
            os << "\\nAction " << state.action_id.value();
            Autometa::Action& action = actions[state.action_id.value()];
            if(action.flags & Autometa::Action::More){
                os << "\\nMore";
            }
            if(action.flags & Autometa::Action::Pop){
                os << "\\nPop";
            }
            if(action.push){
                os << "\\nPush " << state_map[action.push.value()];
            }
        }
        os << "\"; shape = ";
        switch(state.type){
            case Autometa::StateType::Final:
                os << "doublecircle";
            break;
            case Autometa::StateType::Start:
                os << "diamond";
            break;
            case Autometa::StateType::Error:
                os << "doubleoctagon";
            break;
            default:
                os << "circle";
            break;
        }
        os << "];" << std::endl;

        std::map<char, size_t> transitions;
        for(auto& edge: state){
            if(edge.first.has_value()){
                transitions.emplace(edge.first.value(), edge.second);
            }else{
                os << "S" << i << "-> S" << edge.second << " [label=\"null\"];" << std::endl;
            }
        }
        auto start = transitions.begin();
        while(start != transitions.end()){
            auto end = std::adjacent_find(start, transitions.end(), 
                [](const std::pair<char, size_t>& lhs, const std::pair<char, size_t>& rhs){
                    return (lhs.first == '\0') || (lhs.second != rhs.second) || (rhs.first != lhs.first + 1);
                }
            );
            os << "S" << i << "-> S" << start->second << " [label=\"";
            print_char(start->first);
            if(start != end && (end != transitions.end() || std::prev(end) != start)){
                os << "-";
                if(end == transitions.end()){
                    print_char(std::prev(end)->first);
                }else{
                    print_char(end->first);
                }
            }
            os << "\"];" << std::endl;
            if(end == transitions.end()){
                break;
            }else{
                start = std::next(end);
            }
        }
        ++i;
    }
    return os;
}