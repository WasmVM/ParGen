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

#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <optional>
#include <variant>
#include <cctype>
#include <fstream>
#include <memory>
#include <functional>
#include <algorithm>
#include <set>
#include <unordered_map>

using namespace Pargen;

/* Use */

static void resolve_use(std::list<std::variant<Rule, State>>& rules){

    std::unordered_map<std::string, Rule> rule_map;

    std::function<void(std::list<std::variant<Rule, Use, State>>&)> collect_rule = 
        [&collect_rule, &rule_map](std::list<std::variant<Rule, Use, State>>& state)
    {
        for(std::variant<Rule, Use, State>& elem : state){
            std::visit(overloaded {
                [&](Rule& rule){
                    if(!rule.id.empty()){
                        rule_map[rule.id] = rule;
                    }
                },
                [&](State& st){
                    collect_rule(st);
                },
                [](Use&){}
            }, elem);
        }
    };

    std::function<void(std::list<std::variant<Rule, Use, State>>&)> resolve_state_use = 
        [&resolve_state_use, &rule_map](std::list<std::variant<Rule, Use, State>>& state)
    {
        for(std::variant<Rule, Use, State>& elem : state){
            std::visit(overloaded {
                [&](State& st){
                    resolve_state_use(st);
                },
                [&](Use& use){
                    if(rule_map.contains(use.id)){
                        elem.emplace<Rule>(rule_map[use.id]);
                    }else{
                        throw Exception::Exception("rule id '" + use.id + "' not exist");
                    }
                },
                [](Rule&){}
            }, elem);
        }
    };

    for(std::variant<Rule, State>& elem : rules){
        std::visit(overloaded {
            [&](Rule& rule){
                if(!rule.id.empty()){
                    rule_map[rule.id] = rule;
                }
            },
            [&](State& state){
                collect_rule(state);
            }
        }, elem);
    }
    for(std::variant<Rule, State>& elem : rules){
        std::visit(overloaded {
            [](Rule&){},
            [&](State& state){
                resolve_state_use(state);
            }
        }, elem);
    }
}

/* Character */

struct CharType : public std::set<char>{
    enum Class {Number, Alphabet, Space};
    bool negate = false;
    CharType() = default;

    CharType(const char ch){
        insert(ch);
    }

    CharType(const Class cl){
        switch(cl){
            case Number:
                insert({'0','1','2','3','4','5','6','7','8','9'});
            break;
            case Alphabet:
                insert({
                    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
                });
            break;
            case Space:
                insert({' ', '\t', '\r', '\v', '\f', '\n'});
            break;
        }
    }

    operator bool(){
        return negate || !empty();
    }

    bool is_any(){
        return negate && empty();
    }

    CharType operator!(){
        negate = !negate;
        return *this;
    }
    CharType operator+(const CharType& rhs){
        CharType result;
        result.negate = true;
        if(negate == rhs.negate){
            if(negate){
                std::set_intersection(begin(), end(), rhs.begin(), rhs.end(), std::inserter(result, result.end()));
            }else{
                std::set_union(begin(), end(), rhs.begin(), rhs.end(), std::inserter(result, result.end()));
                result.negate = false;
            }
        }else{
            if(negate){
                std::set_difference(begin(), end(), rhs.begin(), rhs.end(), std::inserter(result, result.end()));
            }else{
                std::set_difference(rhs.begin(), rhs.end(), begin(), end(), std::inserter(result, result.end()));
            }
        }
        return result;
    }
    CharType& operator+=(const CharType& rhs){
        *this = (*this + rhs);
        return *this;
    }
};

/* Node */

struct Node {
    enum Type {Char, Group};
    const Type type;
    size_t min = 1, max = 1;
    Node* next = nullptr;
    int id;
    Node(Type type) : type(type){
        static int serial = 0;
        id = serial++;
    }
    virtual ~Node(){
        if(next != nullptr){
            delete next;
            next = nullptr;
        }
    }
};

struct CharNode : public Node{
    CharType char_type;
    CharNode() : Node(Node::Char){}
};

struct GroupNode : public Node{
    std::list<Node*> children;
    GroupNode() : Node(Node::Group){}
    ~GroupNode(){
        if(next != nullptr){
            delete next;
            next = nullptr;
        }
        for(Node* child : children){
            if(child != nullptr){
                delete child;
                child = nullptr;
            }
        }
    }
};

static CharType escape_sequence(std::string::iterator& it, const std::string::iterator& end){
    char ch = *(++it);
    switch(ch){
        case 'x':
            if(it != end && std::next(it) != end){
                std::string hex;
                hex += *(++it); 
                hex += *(++it);
                if(std::isxdigit(hex[0]) && std::isxdigit(hex[1])){
                    return (char)std::stoi(hex, nullptr, 16);
                }else{
                    throw Exception::Exception("expected 2 hex digits for hex escape in pattern");
                }
            }else{
                throw Exception::Exception("too few characters for hex escape in pattern");
            }
        break;
        case 't':
            return '\t';
        break;
        case 'r':
            return '\r';
        break;
        case 'v':
            return '\v';
        break;
        case 'f':
            return '\f';
        break;
        case 'n':
            return '\n';
        break;
        case 'd':
            return CharType(CharType::Number);
        break;
        case 'D':
            return !CharType(CharType::Number);
        break;
        case 's':
            return CharType(CharType::Space);
        break;
        case 'S':
            return !CharType(CharType::Space);
        break;
        case 'w':
            return CharType(CharType::Alphabet) + CharType(CharType::Number);
        break;
        case 'W':
            return !(CharType(CharType::Alphabet) + CharType(CharType::Number));
        break;
        case 'a':
            return CharType(CharType::Alphabet);
        break;
        case 'A':
            return !CharType(CharType::Alphabet);
        break;
        default:
            return ch;
    }
}

static Node* parse_pattern(std::string& pattern){
    std::stack<GroupNode*> groups;
    Node* root = nullptr;
    Node* current = nullptr;
    Node** next = &root;
    size_t level = 0;
    for(auto it = pattern.begin(); it != pattern.end(); ++it){
        switch(*it){
            case '[':{
                CharType char_type;
                bool negate = false;
                if(it != pattern.end()){
                    if(*(std::next(it)) == '^'){
                        negate = true;
                        ++it;
                    }
                    ++it;
                }
                std::optional<char> last = std::nullopt;
                while((it != pattern.end()) && (*it != ']')){
                    if(*it == '\\'){
                        if(std::next(it) == pattern.end()){
                            throw Exception::Exception("expected character after '\\' in pattern");
                        }else{
                            CharType escaped = escape_sequence(it, pattern.end());
                            char_type += escaped;
                            if(!escaped.negate && escaped.size() == 1){
                                last = *escaped.begin();
                            }else{
                                last.reset();
                            }
                        }
                    }else if(*it == '-'){
                        if(std::next(it) == pattern.end()){
                            throw Exception::Exception("expected character after '-' in pattern");
                        }else if(char_type.empty()){
                            throw Exception::Exception("expected character before '-' in pattern");
                        }else if(!last.has_value()){
                            throw Exception::Exception("invalid character before '-' in pattern");
                        }else{
                            ++it;
                            for(char ch = (last.value() + 1); ch <= *it; ++ch){
                                char_type += ch;
                            }
                        }
                    }else{
                        char_type += *it;
                    }
                    ++it;
                }
                if(negate){
                    char_type = !char_type;
                }
                if(char_type == false){
                    throw Exception::Exception("empty [] in pattern");
                }
                CharNode* node = new CharNode;
                node->char_type = char_type;
                current = node;
                *next = node;
                next = &(node->next);
            }break;
            case '\\':{
                if(it != pattern.end()){
                    CharNode* node = new CharNode;
                    node->char_type = escape_sequence(it, pattern.end());
                    current = node;
                    *next = node;
                    next = &(node->next);
                }else{
                    throw Exception::Exception("expected a character after '\\' in pattern");
                }
            }break;
            case '{':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '{'");
                }
                std::string str = "";
                while(std::isdigit(*(++it))){
                    str += *it;
                }
                if(str.empty()){
                    throw Exception::Exception("invalid '{' qualifier");
                }
                current->min = std::stoi(str);
                if(*it == ','){
                    str = "0";
                    while(std::isdigit(*(++it))){
                        str += *it;
                    }
                    if(str.empty()){
                        throw Exception::Exception("invalid '{' qualifier");
                    }
                    current->max = std::stoi(str);
                }else{
                    current->max = current->min;
                }
                if(*it != '}'){
                    throw Exception::Exception("'{' is not close with '}' in pattern {min,max} qualifier");
                }
                if(current->max != 0 && (current->min > current->max)){
                    throw Exception::Exception("min can't be greater than max in pattern {min,max} qualifier");
                }
            }break;
            case '}':{
                throw Exception::Exception("'}' without previous '{'");
            }break;
            case '+':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '+'");
                }
                current->min = 1;
                current->max = 0;
            }break;
            case '*':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '*'");
                }
                current->min = 0;
                current->max = 0;
            }break;
            case '?':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '?'");
                }
                current->min = 0;
                current->max = 1;
            }break;
            case '(':{
                GroupNode* node = new GroupNode;
                *next = node;
                groups.push(node);
                node->children.emplace_back(nullptr);
                current = nullptr;
                next = &(node->children.back());
                level += 1;
            }break;
            case ')':{
                if(level == 0){
                    throw Exception::Exception("')' without previous '('");
                }
                current = groups.top();
                next = &(groups.top()->next);
                groups.pop();
                level -= 1;
            }break;
            case '|':{
                if(groups.empty()){
                    if(current == nullptr){
                        throw Exception::Exception("pattern or group can't begin with '|'");
                    }
                    GroupNode* node = new GroupNode;
                    node->children.emplace_back(root);
                    root = node;
                    groups.push(node);
                }
                groups.top()->children.emplace_back(nullptr);
                current = nullptr;
                next = &(groups.top()->children.back());
            }break;
            case '.':{
                CharNode* node = new CharNode;
                node->char_type.negate = true;
                current = node;
                *next = node;
                next = &(node->next);
            }break;
            default:{
                CharNode* node = new CharNode;
                node->char_type += *it;
                current = node;
                *next = node;
                next = &(node->next);
            }break;
        }
    }
    if(root == nullptr){
        throw Exception::Exception("empty pattern");
    }
    return root;
}

/* Autometa */

struct Autometa {

    Autometa(Lexer& lexer);

    struct Action {
        enum Flags : uint8_t {
            None = 0,
            More = 1,
            Pop = 2,
            Push = 4
        };
        Flags flags = None;
        std::string content = "";
    };

    using Transition = std::variant<size_t, std::string, Action*>;

    struct State : public std::unordered_map<char, Transition> {
        bool neg = false;
        size_t fall = 0;
        size_t min = 1;
        size_t max = 1;
    };

    std::deque<State> states;
    std::unordered_map<std::string, std::deque<State>::iterator> state_map;
    std::deque<Action> actions;
};

struct FiniteState {
    using Edge = std::pair<std::optional<CharType>, size_t>;
    bool final = false;
    std::list<Edge> edges;
};

static std::deque<FiniteState>* create_nfa(Node* root, std::deque<FiniteState>* nfa = nullptr){
    bool initial = (nfa == nullptr);
    if(initial){
        nfa = new std::deque<FiniteState>(2);
    }
    Node* cur = root;
    while(cur != nullptr){
        size_t end_id = (size_t)-1;
        switch(cur->type){
            case Node::Char:{
                CharNode* node = (CharNode*)cur;
                std::list<FiniteState*> accepted;
                for(size_t m = 0; m < std::max(std::max(node->min, (size_t)1), node->max); ++m){
                    FiniteState& back = nfa->back();
                    // Create state
                    back.edges.emplace_back(FiniteState::Edge{node->char_type, nfa->size()});
                    nfa->emplace_back();
                    // Add accepted edges
                    if(m >= node->min){
                        accepted.emplace_back(&back);
                    }
                }
                end_id = nfa->size() - 1;
                // Handle loop
                if(node->max == 0){
                    nfa->back().edges.emplace_back(FiniteState::Edge{node->char_type, end_id});
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
                    end_id = nfa->size() - 1;
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
        nfa->back().final = true;
    }
    return nfa;
}

static void convert_to_dfa(std::deque<FiniteState>& nfa){
    // Collect 
}

std::ostream& operator<< (std::ostream& os, CharType& type){
    if(type.negate){
        os << "not ";
    }
    if(type.is_any()){
        return os << "any";
    }
    std::string characters(type.begin(), type.end());
    std::stable_sort(characters.begin(), characters.end());
    for(char ch : characters){
        if(std::isspace(ch)){
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
        }else{
            os << "'" << ch << "'";
        }
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, std::deque<FiniteState>& nfa){
    size_t i = 0;
    for(FiniteState& state : nfa){
        os << "S" << i;
        if(state.final){
            os << " [shape = doublecircle]";
        }else{
            os << " [shape = circle]";
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

std::deque<Autometa::State> create_states(Pargen::Rule& rule){
    static int rule_id = 0;
    std::deque<Autometa::State> states;
    std::shared_ptr<Node> root(parse_pattern(rule.pattern));
    std::shared_ptr<std::deque<FiniteState>> nfa(create_nfa(root.get()));
    // dump 
    std::ofstream fout("state" + std::to_string(rule_id++) + ".dot");
    fout << "digraph {" << std::endl;
    fout << *nfa << std::endl;
    fout << "}" << std::endl;
    fout.close();
    return states;
}

Autometa::Autometa(Lexer& lexer){

    resolve_use(lexer);
    for(std::variant<Pargen::Rule, Pargen::State>& elem : lexer){
        std::visit(overloaded {
            [&](Pargen::Rule& rule){
                std::deque<Autometa::State> new_states = create_states(rule);
                auto inserted = states.insert(states.end(), new_states.begin(), new_states.end());
                if(!state_map.contains("")){
                    state_map[""] = inserted;
                }
            },
            [&](Pargen::State& state){
                
            }
        }, elem);
    }
}

/* Lexer */

void Pargen::Lexer::generate_header(std::ostream& os){
    // prologue
    os << "/** generated by ParGen **/" << std::endl;
    {
        std::string guard = class_name;
        std::replace(guard.begin(), guard.end(), ':', '_');
        os << "#ifndef ParGen_" << guard << "_guard" << std::endl;
        os << "#define ParGen_" << guard << "_guard" << std::endl;
    }
    os << header_prologue << std::endl;
    os << "#include <iostream>" << std::endl;
    os << "#include <stack>" << std::endl;
    os << "#include <filesystem>" << std::endl;
    if(!parent.tokens.empty()){
        os << "#include " << parent.tokens.header_path.filename() << std::endl;
    }

    // pargen namespace
    os << "\nnamespace " << parent.name_space << " {\n" << std::endl;

    // Lexer class
    os << "struct " << class_name << " {" << std::endl;
    os << "    " << class_name << "(std::filesystem::path filepath, std::istream& stream);" << std::endl;
    os << "    " << parent.tokens.class_name << " get();" << std::endl;
    // Funcs
    for(std::string& func : functions){
        os << func << std::endl;
    }
    // Members
    for(std::string& member : members){
        os << member << std::endl;
    }
    os << "    Position pos;" << std::endl;
    os << "    std::string text = \"\";" << std::endl;
    os << "protected:" << std::endl;
    os << "    std::deque<size_t> stack;" << std::endl;
    os << "    size_t cur = 0;" << std::endl;
    os << "    std::istream& stream;" << std::endl;
    os << "    std::istream::int_type fetch();" << std::endl;
    os << "};\n" << std::endl;

    // close namespace
    os << "} // namespace " << parent.name_space << std::endl;

    // epilogue
    os << header_epilogue << std::endl;
    os << "#endif " << std::endl;
}

void Pargen::Lexer::generate_source(std::ostream& os){

    // Create Autometa
    Autometa autometa(*this);

    // prologue
    os << "/** generated by ParGen **/" << std::endl;
    os << "#include " << header_path << std::endl;
    os << source_prologue << std::endl;

    // includes & namespace
    os << "\nnamespace " << parent.name_space << " {\n" << std::endl;

    // constructor
    os << class_name << "::" << class_name << "(std::filesystem::path path, std::istream& stream) :\n"
        "  stream(stream)\n{\n"
        "    pos.path = path;\n"
        "}\n" << std::endl;

    // fetch
    os << "std::istream::int_type " << class_name << "::fetch(){\n"
        "    std::istream::int_type res = stream.get();\n"
        "    if(res != std::istream::traits_type::eof()){\n"
        "        text += res;\n"
        "        if(text.ends_with(\"" << new_line << "\")){\n"
        "            pos.line += 1;\n"
        "            pos.column = 0;\n"
        "        }else{\n"
        "            pos.column += 1;\n"
        "        }\n"
        "    }\n"
        "    return res;\n"
        "}\n" << std::endl;

    // states TODO: use array instead
    os << "static const std::vector<std::pair<std::pair<size_t, size_t>, size_t[256]>> __states = {" << std::endl;
    os << "};\n" << std::endl;

    // functions
    for(std::string func : functions){
        // Write function
        std::string signature = append_func_name(func, class_name);
        if(signature.starts_with("template")){
            os << "// TODO : " << signature << "\n" << std::endl;
        }else{
            os << signature << "{" << std::endl;
            os << "    // TODO : implement function here" << std::endl;
            os << "}\n" << std::endl;
        }
    }

    // get
    os << parent.tokens.class_name << " " << class_name << "::get(){" << std::endl;
    os << "}\n" << std::endl;

    // close namespace
    os << "} // namespace " << parent.name_space << "\n" << std::endl;

    // epilogue
    os << source_epilogue << std::endl;
}