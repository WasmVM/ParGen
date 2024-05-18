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
#include <unordered_map>
#include <unordered_set>

using namespace Pargen;

static void collect_rule(std::list<std::variant<Rule, Use, State>>& state, std::unordered_map<std::string, Rule>& rule_map){
    for(std::variant<Rule, Use, State>& elem : state){
        std::visit(overloaded {
            [&](Rule& rule){
                if(!rule.id.empty()){
                    rule_map[rule.id] = rule;
                }
            },
            [&](State& st){
                collect_rule(st, rule_map);
            },
            [](Use&){}
        }, elem);
    }
}

static void resolve_use(std::list<std::variant<Rule, Use, State>>& state, std::unordered_map<std::string, Rule>& rule_map){
    for(std::variant<Rule, Use, State>& elem : state){
        std::visit(overloaded {
            [&](State& st){
                resolve_use(st, rule_map);
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
}

static void resolve_use(std::list<std::variant<Rule, State>>& rules){
    std::unordered_map<std::string, Rule> rule_map;
    for(std::variant<Rule, State>& elem : rules){
        std::visit(overloaded {
            [&](Rule& rule){
                if(!rule.id.empty()){
                    rule_map[rule.id] = rule;
                }
            },
            [&](State& state){
                collect_rule(state, rule_map);
            }
        }, elem);
    }
    for(std::variant<Rule, State>& elem : rules){
        std::visit(overloaded {
            [](Rule&){},
            [&](State& state){
                resolve_use(state, rule_map);
            }
        }, elem);
    }
}

enum class CharClass {
    Number, NotNumber,
    Alphabet, NotAlphabet,
    Alnum, NotAlnum,
    Space, NotSpace,
};

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
        }
    }
};

struct CharType {
    bool negate = false;
    std::vector<std::variant<char, CharClass>> chars;
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
        }
        for(Node* child : children){
            if(child != nullptr){
                delete child;
            }
        }
    }
};

static std::vector<std::variant<char, CharClass>> escape_sequence(std::string::iterator& it, const std::string::iterator& end){
    std::vector<std::variant<char, CharClass>> characters;
    char ch = *(++it);
    switch(ch){
        case 'x':
            if(it != end && std::next(it) != end){
                std::string hex;
                hex += *(++it); 
                hex += *(++it);
                if(std::isxdigit(hex[0]) && std::isxdigit(hex[1])){
                    characters.emplace_back((char)std::stoi(hex, nullptr, 16));
                }else{
                    throw Exception::Exception("expected 2 hex digits for hex escape in pattern");
                }
            }else{
                throw Exception::Exception("too few characters for hex escape in pattern");
            }
        break;
        case 't':
            characters.emplace_back('\t');
        break;
        case 'r':
            characters.emplace_back('\r');
        break;
        case 'v':
            characters.emplace_back('\v');
        break;
        case 'f':
            characters.emplace_back('\f');
        break;
        case 'n':
            characters.emplace_back('\n');
        break;
        case 'd':
            characters.emplace_back(CharClass::Number);
        break;
        case 'D':
            characters.emplace_back(CharClass::NotNumber);
        break;
        case 's':
            characters.emplace_back(CharClass::Space);
        break;
        case 'S':
            characters.emplace_back(CharClass::NotSpace);
        break;
        case 'w':
            characters.emplace_back(CharClass::Alnum);
        break;
        case 'W':
            characters.emplace_back(CharClass::NotAlnum);
        break;
        case 'a':
            characters.emplace_back(CharClass::Alphabet);
        break;
        case 'A':
            characters.emplace_back(CharClass::NotAlphabet);
        break;
        default:
            characters.emplace_back(ch);
    }
    return characters;
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
                std::vector<std::variant<char, CharClass>> characters;
                bool negate = false;
                if(it != pattern.end()){
                    if(*(std::next(it)) == '^'){
                        negate = true;
                        ++it;
                    }
                    ++it;
                }
                while((it != pattern.end()) && (*it != ']')){
                    if(*it == '\\'){
                        if(std::next(it) == pattern.end()){
                            throw Exception::Exception("expected character after '\\' in pattern");
                        }else{
                            std::vector<std::variant<char, CharClass>> escapes = escape_sequence(it, pattern.end());
                            characters.insert(characters.end(), escapes.begin(), escapes.end());
                        }
                    }else if(*it == '-'){
                        if(std::next(it) == pattern.end()){
                            throw Exception::Exception("expected character after '-' in pattern");
                        }else if(characters.empty()){
                            throw Exception::Exception("expected character before '-' in pattern");
                        }else if(std::holds_alternative<char>(characters.back())){
                            ++it;
                            for(char ch = std::get<char>(characters.back()) + 1; ch <= *it; ++ch){
                                characters.emplace_back(ch);
                            }
                        }
                    }else{
                        characters.emplace_back(*it);
                    }
                    ++it;
                }
                if(characters.empty()){
                    throw Exception::Exception("empty [] in pattern");
                }
                CharNode* node = new CharNode;
                node->char_type.chars = characters;
                node->char_type.negate = negate;
                current = node;
                *next = node;
                next = &(node->next);
            }break;
            case '\\':{
                if(it != pattern.end()){
                    std::vector<std::variant<char, CharClass>> characters = escape_sequence(it, pattern.end());
                    CharNode* node = new CharNode;
                    node->char_type.chars = characters;
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
                node->char_type.chars.emplace_back(*it);
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

struct NFAState {
    using Edge = std::pair<std::optional<CharType>, size_t>;
    bool final = false;
    std::list<Edge> edges;
};

static void convert_to_nfa(Node* root, std::deque<NFAState>& nfa){
    Node* cur = root;
    while(cur != nullptr){
        size_t start_id = nfa.size() - 1;
        size_t end_id = (size_t)-1;
        switch(cur->type){
            case Node::Char:{
                CharNode* node = (CharNode*)cur;
                std::list<NFAState*> accepted;
                for(size_t m = 0; m < std::max(std::max(node->min, (size_t)1), node->max); ++m){
                    NFAState& back = nfa.back();
                    back.edges.emplace_back(NFAState::Edge{node->char_type, nfa.size()});
                    nfa.emplace_back();
                    if(m >= node->min){
                        accepted.emplace_back(&back);
                    }
                }
                end_id = nfa.size() - 1;
                if(node->max == 0){
                    nfa.back().edges.emplace_back(NFAState::Edge{node->char_type, end_id});
                }
                for(NFAState* state : accepted){
                    state->edges.emplace_back(NFAState::Edge{std::nullopt, end_id});
                }
            }break;
            case Node::Group:{
                GroupNode* node = (GroupNode*)cur;
                if(!node->children.empty()){

                }
            }break;
        }
        cur = cur->next;
    }
}

std::ostream& operator<< (std::ostream& os, CharType& type){
    if(type.negate){
        os << "not ";
    }
    for(std::variant<char, CharClass> ch : type.chars){
        std::visit(overloaded {
            [&os](char& c){
                os << "'" << c << "'";
            },
            [&os](CharClass& c){
                switch(c){
                    case CharClass::Number:
                        os << "number";
                    break;
                    case CharClass::NotNumber:
                        os << "not-number";
                    break;
                    case CharClass::Alphabet:
                        os << "alpha";
                    break;
                    case CharClass::NotAlphabet:
                        os << "not-alpha";
                    break;
                    case CharClass::Alnum:
                        os << "alnum";
                    break;
                    case CharClass::NotAlnum:
                        os << "not-alnum";
                    break;
                    case CharClass::Space:
                        os << "space";
                    break;
                    case CharClass::NotSpace:
                        os << "not-space";
                    break;
                }
            },
        }, ch);
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, std::deque<NFAState>& nfa){
    size_t i = 0;
    for(NFAState& state : nfa){
        os << "S" << i;
        if(state.final){
            os << " [shape = doublecircle]";
        }else{
            os << " [shape = circle]";
        }
        os << ";" << std::endl;
        for(NFAState::Edge& edge: state.edges){
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
    Node* root = parse_pattern(rule.pattern);
    std::deque<NFAState> nfa(1);
    convert_to_nfa(root, nfa);
    // dump 
    std::ofstream fout("state" + std::to_string(rule_id++) + ".dot");
    fout << "digraph {" << std::endl;
    fout << nfa << std::endl;
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
                // TODO:
            }
        }, elem);
    }
}

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
            os << "// TODO: " << signature << "\n" << std::endl;
        }else{
            os << signature << "{" << std::endl;
            os << "    // TODO: implement function here" << std::endl;
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