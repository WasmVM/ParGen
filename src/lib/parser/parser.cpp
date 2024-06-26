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

#include <map>
#include <set>
#include <deque>
#include <vector>
#include <memory>
#include <numeric>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>
#include <unordered_set>

#include "parser.hpp"

void Pargen::Parser::generate_header(std::ostream& os){
    // prologue
    os << "/** generated by ParGen **/" << std::endl;
    {
        std::string guard = class_name;
        std::replace(guard.begin(), guard.end(), ':', '_');
        os << "#ifndef ParGen_" << guard << "_guard" << std::endl;
        os << "#define ParGen_" << guard << "_guard" << std::endl;
    }
    os << header_prologue << std::endl;

    os << "#include <map>" << std::endl;
    os << "#include <stack>" << std::endl;
    if(!parent.tokens.empty()){
        os << "#include " << parent.tokens.header_path.filename() << std::endl;
    }
    if(parent.lexer.empty()){
        os << "#include <any>" << std::endl;
    }else{
        os << "#include " << parent.lexer.header_path.filename() << std::endl;
    }

    // pargen namespace
    os << "\nnamespace " << parent.name_space << " {\n" << std::endl;

    // Parser class
    os << "struct " << class_name << " {" << std::endl;
    os << "    " << class_name << "(" << parent.lexer.class_name << "& lexer);" << std::endl;
    os << "    " << return_type << " parse();" << std::endl;
    // Funcs
    for(std::string& func : functions){
        os << func << std::endl;
    }
    // Members
    for(std::string& member : members){
        os << member << std::endl;
    }
    os << "protected:" << std::endl;
    os << "    using term_t = size_t;" << std::endl;
    os << "    using Act = std::pair<bool, size_t>; // true: shift, false: reduce" << std::endl;
    os << "    using State = std::map<term_t, std::vector<Act>>;" << std::endl;
    if(parent.lexer.empty()){
        os << "    using token_t = std::any;" << std::endl;
    }else{
        if(parent.lexer.return_type.empty()){
            if(parent.tokens.empty()){
                os << "    using token_t = std::any;" << std::endl;
            }else{
                os << "    using token_t = " << parent.tokens.class_name << ";" << std::endl;
            }
        }else{
            os << "    using token_t = " << parent.lexer.return_type << ";" << std::endl;
        }
        os << "    " << parent.lexer.class_name << "& lexer;" << std::endl;
    }
    os << "    static std::vector<State> table;" << std::endl;
    os << "    std::pair<term_t,token_t> fetch();" << std::endl;
    os << "};\n" << std::endl;

    // close namespace
    os << "} // namespace " << parent.name_space << std::endl;

    // epilogue
    os << header_epilogue << std::endl;
    os << "#endif " << std::endl;
}

void Pargen::Parser::generate_source(std::ostream& os){

    // Create GLR parser
    GLRParser parser(*this);

    // dump terms
    if(parent.options.debug){
        std::ofstream fout("terms.txt");
        parser.dump_terms(fout);
        fout.close();
    }

    // dump grammars
    if(parent.options.debug){
        std::ofstream fout("grams.txt");
        parser.dump_grammars(fout);
        fout.close();
    }

    // dump states
    if(parent.options.debug){
        std::ofstream fout("states.dot");
        parser.dump_states(fout);
        fout.close();
    }

    // prologue
    os << "/** generated by ParGen **/" << std::endl;
    os << "#include " << header_path << std::endl;
    os << source_prologue << std::endl;

    // includes & namespace
    os << "\nnamespace " << parent.name_space << " {" << std::endl;
    if(!parent.tokens.empty()){
        os << "\nusing namespace " << parent.tokens.name_space << ";\n" << std::endl;
    }

    // constructor
    os << class_name << "::" << class_name << "(" << parent.lexer.class_name << "& lexer) : lexer(lexer) {}\n" << std::endl;

    // fetch
    os << "std::pair<" << class_name << "::term_t, " << class_name << "::token_t> " << class_name << "::fetch(){" << std::endl;
    if(!parent.lexer.empty() && parent.lexer.return_type.empty() && !parent.tokens.empty()){
        os << "    " << parent.tokens.class_name << " res = lexer.get();" << std::endl;
        os << "    return {res.index(), res};" << std::endl;
    }else{
        os << "    /* TODO: return pair as below:" << std::endl;
        std::unordered_set<std::string> nterms;
        std::transform(begin(), end(), std::inserter(nterms, nterms.end()), [](Pargen::Grammar& gram){
            return gram.target;
        });
        for(auto term_pair : parser.term_map){
            if(!nterms.contains(term_pair.first)){
                os << "      {" << term_pair.second << ", " << term_pair.first << "}" << std::endl;
            }
        }
        os << "    */" << std::endl;
    }
    os << "}\n" << std::endl;

    // actions
    for(size_t action_id = 0; action_id < parser.actions.size(); ++action_id){
        GLRParser::Action& action = parser.actions[action_id];
        std::string return_type = parser.type_map[action.result];
        if(return_type.empty()){
            return_type = "void";
        }
        os << "static " << return_type << " action_"<< action_id << "(";
        bool has_first = false;
        if(!parent.tokens.empty()){
            os << "Position _pos[]";
            has_first = true;
        }
        for(size_t param_id = 0; param_id < action.params.size(); ++param_id){
            term_t term = action.params[param_id];
            if(!parser.term_map.is_term(term) && parser.type_map[term].empty()){
                continue;
            }
            if(has_first){
                os << ", ";
            }else{
                has_first = true;
            }
            if(parser.term_map.is_term(term)){
                os << parent.tokens.name_space << "::" << parser.term_map[term].value();
            }else{
                os << parser.type_map[term];
            }
            os << " _op" << param_id;
        }
        os << "){" << action.body << "\n}" << std::endl;
    }
    os << std::endl;

    // table
    os << "std::vector<" << class_name << "::State> " << class_name << "::table = {" << std::endl;
    for(const GLRParser::State& state : parser.states){
        std::map<term_t, std::list<std::pair<bool, size_t>>> acts;
        // Shift
        for(const std::pair<const term_t, size_t>& edge : state.edges){
            acts[edge.first].emplace_back(true, edge.second);
        }
        // Reduce
        for(const GLRParser::Grammar& prod : state.productions){
            if(prod.dot_pos == prod.depends.size()){
                if(prod.target == 0){
                    acts[prod.target] = {};
                }else{
                    for(term_t lookahead : prod.lookahead){
                        acts[lookahead].emplace_back(false, prod.action.value());
                    }
                }
            }
        }
        // Output state
        os << "    {";
        for(auto act_pair : acts){
            // Term
            os << "{" << act_pair.first << ", {";
            for(std::pair<bool, size_t> act : act_pair.second){
                os << "{" << act.first << "," << act.second << "},";
            }
            os << "}},";
        }
        os << "}," << std::endl;
    }
    os << "};\n" << std::endl;

    // parse
    os << "void " << class_name << "::parse(){" << std::endl;
    
    os << "}\n" << std::endl;

    // functions
    for(std::string func : functions){
        // Write function
        std::string signature = append_func_name(func, class_name);
        if(signature.starts_with("template")){
            os << "// TODO: " << signature << "\n" << std::endl;
        }else{
            os << signature << "{" << std::endl;
            os << "    // TODO: implement function here" << std::endl;
            os << "}\n" << std::endl;
        }
    }

    // close namespace
    os << "} // namespace " << parent.name_space << "\n" << std::endl;

    // epilogue
    os << source_epilogue << std::endl;
}

GLRParser::GLRParser(Pargen::Parser& parser) : term_map(create_term_map(parser)), parser(parser) {
    // Prepare grammar
    read_grammar();
    std::map<term_t, std::set<term_t>> first_sets = create_first_sets();
    
    // Create grammar map
    std::map<term_t, std::set<Grammar>> gram_map;
    for(Grammar gram : grammars){
        gram_map[gram.target].insert(gram);
    }

    // Create states
    if(term_map[parser.start] == TermMap::none){
        throw Exception::Exception("can't find grammar for start");
    }
    std::deque<std::set<Grammar>> gram_queue {{Grammar {
        .target = TermMap::start,
        .depends = {term_map[parser.start]},
        .lookahead = {TermMap::eof}
    }}};
    std::list<State> state_list;
    {
        std::set<Grammar> created;
        while(!gram_queue.empty()){
            State state(gram_queue.front(), gram_map, first_sets);
            gram_queue.pop_front();
            std::map<term_t, std::set<Grammar>> prod_map;
            for(Grammar gram : state.productions){
                if(!created.contains(gram)){
                    if(gram.dot_pos != 0){
                        created.emplace(gram);
                    }
                    if(gram.dot_pos != gram.depends.size()){
                        size_t pos = gram.dot_pos;
                        gram.dot_pos += 1;
                        prod_map[gram.depends[pos]].emplace(gram);
                    }
                }
            }
            for(auto prod_pair : prod_map){
                gram_queue.push_back(prod_pair.second);
            }
            state_list.emplace_back(state);
        }
    }
    
    // Merge states
    bool modified = true;
    std::vector<std::list<State>::iterator> removed;
    while(modified){
        modified = false;
        size_t state_id = 0;
        for(auto lhs = state_list.begin(); lhs != state_list.end(); lhs = std::next(lhs)){
            if(std::find(removed.begin(), removed.end(), lhs) == removed.end()){
                for(auto rhs = state_list.begin(); rhs != state_list.end(); rhs = std::next(rhs)){
                    if((lhs != rhs)
                        && (std::find(removed.begin(), removed.end(), rhs) == removed.end())
                        && lhs->merge(*rhs)
                    ){
                        modified = true;
                        if(std::none_of(removed.begin(), removed.end(), [&](std::list<State>::iterator& elem){
                            return elem == rhs;
                        })){
                            removed.emplace_back(rhs);
                        }
                        break;
                    }
                }
                state_id += 1;
            }
        }
    }
    for(auto rem : removed){
        state_list.erase(rem);
    }
    states.assign(state_list.begin(), state_list.end());
    state_list.clear();
    removed.clear();

    // Create edges
    std::list<std::pair<Grammar, size_t>> edge_list;
    for(size_t state_id = 0; state_id < states.size(); ++state_id){
        State& state = states[state_id];
        for(Grammar& gram : state.productions){
            if(gram.dot_pos != 0){
                edge_list.emplace_back(gram, state_id);
            }
        }
    }
    for(State& state : states){
        std::set<term_t> linked;
        for(Grammar prod : state.productions){
            if(prod.dot_pos < prod.depends.size()){
                term_t term = prod.depends[prod.dot_pos];
                prod.dot_pos += 1;
                if(!linked.contains(term)){
                    for(auto edge_pair : edge_list){
                        Grammar& edge_gram = edge_pair.first;
                        if((edge_gram.target == prod.target) && (edge_gram.dot_pos == prod.dot_pos) && (edge_gram.depends == prod.depends)
                            && std::includes(edge_gram.lookahead.begin(), edge_gram.lookahead.end(), prod.lookahead.begin(), prod.lookahead.end())
                        ){
                            state.edges[term] = edge_pair.second;
                            linked.emplace(term);
                            break;
                        }
                    }
                }
            }
        }
    }
}

TermMap GLRParser::create_term_map(Pargen::Parser& parser){
    // Collect terminals
    std::set<std::string> terms, nterms;
    {
        std::set<std::string> all_terms;
        for(Pargen::Grammar gram : parser){
            nterms.insert(gram.target);
            all_terms.insert(gram.depends.begin(), gram.depends.end());
        }
        std::set_difference(all_terms.begin(), all_terms.end(), nterms.begin(), nterms.end(), std::inserter(terms, terms.end()));
    }

    // Assign term_map
    if(parser.parent.tokens.empty()){
        return TermMap(std::vector<std::string>(terms.begin(), terms.end()), nterms);
    }else{
        std::vector<std::string> tokens;
        for(Pargen::Token& token : parser.parent.tokens){
            tokens.emplace_back(token.name);
        }
        return TermMap(tokens, nterms);
    }
}

void GLRParser::read_grammar(){
    // Read grammars
    std::set<term_t> empties;
    for(Pargen::Grammar& gram : parser){
        // target
        term_t target = term_map[gram.target];
        if(target == TermMap::none){
            throw Exception::Exception("unknown terminal '" + gram.target + "'");
        }
        // action
        Action& action = actions.emplace_back();
        action.result = target;
        if(!type_map.contains(target)){
            type_map[target] = gram.type;
        }
        action.body = gram.content;
        // grammar
        if(gram.depends.empty()){
            // Empty grammar
            if(empties.contains(target)){
                throw Exception::Exception("multiple empty grammar for '" + gram.target + "'");
            }
            empties.emplace(target);
        }else{
            Grammar grammar;
            grammar.target = target;
            grammar.action = actions.size();
            grammar.param_indices.resize(gram.depends.size());
            std::iota(grammar.param_indices.begin(), grammar.param_indices.end(), 0);
            std::transform(gram.depends.begin(), gram.depends.end(), std::back_inserter(grammar.depends), [&](std::string& dep){
                if(term_map[dep] == TermMap::none){
                    throw Exception::Exception("unknown terminal '" + dep + "'");
                }
                return term_map[dep];
            });
            action.params.assign(grammar.depends.begin(), grammar.depends.end());
            grammars.emplace(grammar);
        }
    }

    // Expand empty grammar
    for(auto gram_it = grammars.begin(); gram_it != grammars.end(); gram_it = std::next(gram_it)){
        Grammar gram = *gram_it;
        for(size_t dep_idx = 0; dep_idx < gram.depends.size(); ++dep_idx){
            if(empties.contains(gram.depends[dep_idx])){
                Grammar new_gram = gram;
                new_gram.depends.erase(new_gram.depends.begin() + dep_idx);
                new_gram.param_indices.erase(new_gram.param_indices.begin() + dep_idx);
                if((new_gram.depends.size() > 1 || (new_gram.depends.size() == 1 && new_gram.target != new_gram.depends[0]))
                    && std::find(grammars.begin(), grammars.end(), new_gram) == grammars.end()
                ){
                    grammars.emplace(new_gram);
                }
            }
        }
    }
}

std::map<term_t, std::set<term_t>> GLRParser::create_first_sets(){
    std::map<term_t, std::set<term_t>> first_sets;
    // Insert terminals
    for(auto term_pair : term_map){
        if(!term_pair.first.empty() && term_map.is_term(term_pair.second)){
            first_sets[term_pair.second].emplace(term_pair.second);
        }
    }

    // Initialize non-terminals
    std::set<term_t> modified;
    for(const GLRParser::Grammar& gram : grammars){
        if(term_map.is_term(gram.depends.front())){
            modified.emplace(gram.target);
            first_sets[gram.target].emplace(gram.depends.front());
        }
    }

    // Update non-terminals
    while(!modified.empty()){
        std::set<term_t> checking = modified;
        modified.clear();
        for(const GLRParser::Grammar& gram : grammars){
            if(checking.contains(gram.depends.front())){
                for(term_t term : first_sets[gram.depends.front()]){
                    if(!first_sets[gram.target].contains(term)){
                        modified.emplace(gram.target);
                        first_sets[gram.target].emplace(term);
                    }
                }
            }
        }
    }
    return first_sets;
}

GLRParser::State::State(std::set<Grammar> grammars, std::map<term_t, std::set<Grammar>>& gram_map, std::map<term_t, std::set<term_t>>& first_sets){
    // Insert grammar
    std::list<Grammar> produced(grammars.begin(), grammars.end());
    productions.insert(productions.end(), grammars.begin(), grammars.end());
    std::map<term_t, std::set<term_t>> lookaheads;
    for(Grammar& prod : productions){
        if(prod.dot_pos < prod.depends.size() - 1){
            std::set<term_t>& first = first_sets[prod.depends[prod.dot_pos + 1]];
            lookaheads[prod.depends[prod.dot_pos]].insert(first.begin(), first.end());
        }
    }
    // Expand productions
    for(Grammar grammar : grammars){
        if(grammar.dot_pos != grammar.depends.size()){
            for(Grammar& prod : productions){
                // produce grammar
                for(Grammar gram : gram_map[prod.depends[prod.dot_pos]]){
                    // lookahead
                    if(lookaheads.contains(gram.target)){
                        gram.lookahead = lookaheads[gram.target];
                    }else{
                        gram.lookahead = prod.lookahead;
                    }
                    std::list<Grammar>::iterator found = std::find_if(productions.begin(), productions.end(), [&](Grammar rhs){
                        return (gram.target == rhs.target) && (gram.dot_pos == rhs.dot_pos) && (gram.depends == rhs.depends);
                    });
                    if(found == productions.end()){
                        produced.emplace_back(gram);
                        productions.emplace_back(gram);
                        if(gram.dot_pos < gram.depends.size() - 1){
                            std::set<term_t>& first = first_sets[gram.depends[gram.dot_pos + 1]];
                            lookaheads[gram.depends[gram.dot_pos]].insert(first.begin(), first.end());
                        }
                    }else{
                        found->lookahead.insert(gram.lookahead.begin(), gram.lookahead.end());
                    }
                }
            }
        }
    }
}

bool GLRParser::State::merge(State& state){
    const auto comp = [](const Grammar& lhs, const Grammar& rhs){
        return (lhs.target == rhs.target) && (lhs.dot_pos == rhs.dot_pos) && (lhs.depends == rhs.depends);
    };
    std::list<std::pair<Grammar*, Grammar*>> merge_pairs;
    for(Grammar& prod_l : state.productions){
        bool found = false;
        for(Grammar& prod_r : productions){
            if(comp(prod_l, prod_r)){
                found = true;
                merge_pairs.emplace_back(&prod_r, &prod_l);
                break;
            }
        }
        if(!found){
            return false;
        }
    }
    for(auto merge_pair : merge_pairs ){
        merge_pair.first->lookahead.insert(merge_pair.second->lookahead.begin(), merge_pair.second->lookahead.end());
    }
    return true;
}

bool operator<(const GLRParser::Grammar& lhs, const GLRParser::Grammar& rhs){
    if(lhs.target != rhs.target){
        return lhs.target < rhs.target;
    }
    if(lhs.depends.size() != rhs.depends.size()){
        return lhs.depends.size() < rhs.depends.size();
    }
    for(size_t i = 0; i < lhs.depends.size(); ++i){
        if(lhs.depends[i] != rhs.depends[i]){
            return lhs.depends[i] < rhs.depends[i];
        }
    }
    if(lhs.dot_pos != rhs.dot_pos){
        return lhs.dot_pos < rhs.dot_pos;
    }
    if(lhs.lookahead.size() != rhs.lookahead.size()){
        return lhs.lookahead.size() < rhs.lookahead.size();
    }
    std::vector<term_t> look_l(lhs.lookahead.begin(), lhs.lookahead.end());
    std::sort(look_l.begin(), look_l.end());
    std::vector<term_t> look_r(rhs.lookahead.begin(), rhs.lookahead.end());
    std::sort(look_r.begin(), look_r.end());
    for(size_t i = 0; i < look_l.size(); ++i){
        if(look_l[i] != look_r[i]){
            return look_l[i] < look_r[i];
        }
    }
    if(lhs.action.has_value() && rhs.action.has_value()){
        return lhs.action.value() < rhs.action.value();
    }
    return !lhs.action.has_value() && rhs.action.has_value();
}

std::ostream& operator<<(std::ostream& os, GLRParser& parser){

}