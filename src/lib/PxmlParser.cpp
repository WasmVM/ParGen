/** generated by ParGen **/
#include "PxmlParser.hpp"

static PXML::Position to_pos(ParsePxml::Position pos){
    return PXML::Position {.path = pos.path, .line = pos.line, .column = pos.column};
}
        
#include <stack>
#include <list>
#include <variant>
#include <vector>
#include <algorithm>
#include <array>

namespace ParsePxml {

using namespace Tokens;

PxmlParser::PxmlParser(PxmlLexer& lexer) : lexer(lexer) {}

std::pair<PxmlParser::term_t, PxmlParser::token_t> PxmlParser::fetch(){
    if(!buffer.empty()){
        auto token = buffer.front();
        buffer.pop_front();
        return token;
    }
    Token res = lexer.get();
    return {res.index() + 1, res};
}

static PXML::Pxml action_1(std::vector<Position> _pos, Tokens::Doctype _op0, std::string _op1, PXML::Pxml _op2, std::string _op3){
    return _op2;
}
static std::list<PXML::Pxml::Child> action_2(std::vector<Position> _pos, std::list<PXML::Pxml::Child> _op0, PXML::Pxml _op1){
    _op0.emplace_back(to_pos(_pos[1]), _op1);
    return _op0;
}
static std::list<PXML::Pxml::Child> action_3(std::vector<Position> _pos, std::list<PXML::Pxml::Child> _op0, std::string _op1){
    _op0.emplace_back(to_pos(_pos[1]), _op1);
    return _op0;
}
static std::list<PXML::Pxml::Child> action_4(std::vector<Position> _pos){
    return {};
}
static PXML::Pxml action_5(std::vector<Position> _pos, Tokens::Tag _op0, std::unordered_map<std::string, PXML::Value> _op1, Tokens::Close _op2, std::list<PXML::Pxml::Child> _op3, Tokens::Tail _op4){
    PXML::Position pos = to_pos(_pos[0]);
    if(_op0.value != _op4.value){
        throw Exception::SyntaxError("tag not match", pos);
    }
    PXML::Pxml elem {.tag = _op0.value, .pos = pos};
    elem.swap(_op1);
    elem.children.swap(_op3);
    return elem;
}
static PXML::Pxml action_6(std::vector<Position> _pos, Tokens::Tag _op0, std::unordered_map<std::string, PXML::Value> _op1, Tokens::Inline _op2){
    PXML::Pxml elem {.tag = _op0.value, .pos = to_pos(_pos[0])};
    elem.swap(_op1);
    return elem;
}
static std::string action_7(std::vector<Position> _pos, std::string _op0, Tokens::Space _op1){
    return _op0 + _op1.value;
}
static std::string action_8(std::vector<Position> _pos){
    return std::string();
}
static std::string action_9(std::vector<Position> _pos, std::string _op0, Tokens::Text _op1){
    return _op0 + _op1.value;
}
static std::string action_10(std::vector<Position> _pos, std::string _op0, Tokens::Space _op1){
    return _op0 + _op1.value;
}
static std::string action_11(std::vector<Position> _pos, std::string _op0, Tokens::Entity _op1){
    return _op0 + _op1.value;
}
static std::string action_12(std::vector<Position> _pos){
    return std::string();
}
static std::unordered_map<std::string, PXML::Value> action_13(std::vector<Position> _pos, std::unordered_map<std::string, PXML::Value> _op0, std::pair<std::string, PXML::Value> _op1){
    _op0.emplace(_op1);
    return _op0;
}
static std::unordered_map<std::string, PXML::Value> action_14(std::vector<Position> _pos, std::unordered_map<std::string, PXML::Value> _op0, Tokens::Space _op1){
    return _op0;
}
static std::unordered_map<std::string, PXML::Value> action_15(std::vector<Position> _pos){
    return {};
}
static std::pair<std::string, PXML::Value> action_16(std::vector<Position> _pos, Tokens::ID _op0, Tokens::Equal _op1, PXML::Value _op2){
    return {_op0.value, _op2};
}
static std::pair<std::string, PXML::Value> action_17(std::vector<Position> _pos, Tokens::ID _op0){
    return {_op0.value, {to_pos(_pos[0]), std::monostate()}};
}
static PXML::Value action_18(std::vector<Position> _pos, Tokens::Bool _op0){
    return {to_pos(_pos[0]), _op0.value};
}
static PXML::Value action_19(std::vector<Position> _pos, Tokens::Number _op0){
    return {to_pos(_pos[0]), _op0.value};
}
static PXML::Value action_20(std::vector<Position> _pos, Tokens::String _op0){
    return {to_pos(_pos[0]), _op0.value};
}

std::vector<PxmlParser::State> PxmlParser::table = {
    {{2, {{3,{}},}},{19, {{5,{}},}},},
    {{8, {{69,{}},}},{14, {{23,{}},}},{18, {{7,{}},}},{20, {{9,{}},}},},
    {{1, {{0,{}},}},},
    {{1, {{2,{1,0,0,1,}},}},{14, {{23,{}},}},{20, {{11,{}},}},},
    {{8, {{69,{}},}},{14, {{13,{}},}},{18, {{15,{}},}},},
    {{1, {{2,{1,0,1,1,}},}},{14, {{13,{}},}},},
    {{1, {{14,{1,1,}},}},{8, {{14,{1,1,}},}},{14, {{14,{1,1,}},}},},
    {{1, {{2,{1,1,1,0,}},}},{14, {{23,{}},}},{20, {{25,{}},}},},
    {{6, {{37,{}},}},{7, {{39,{}},}},{10, {{41,{}},}},{22, {{43,{}},}},},
    {{4, {{28,{1,1,}},}},{5, {{28,{1,1,}},}},{12, {{28,{1,1,}},}},{14, {{28,{1,1,}},}},},
    {{4, {{26,{1,1,}},}},{5, {{26,{1,1,}},}},{12, {{26,{1,1,}},}},{14, {{26,{1,1,}},}},},
    {{1, {{14,{0,1,}},}},{8, {{14,{0,1,}},}},{14, {{14,{0,1,}},}},},
    {{1, {{2,{1,1,1,1,}},}},{14, {{13,{}},}},},
    {{8, {{4,{1,1,}},}},{9, {{4,{1,1,}},}},{11, {{4,{1,1,}},}},{13, {{4,{1,1,}},}},{14, {{4,{1,1,}},}},},
    {{8, {{6,{1,1,}},}},{9, {{6,{1,1,}},}},{11, {{31,{}},{6,{1,1,}},}},{13, {{33,{}},{6,{1,1,}},}},{14, {{35,{}},{6,{1,1,}},}},},
    {{8, {{18,{1,1,}},}},{9, {{18,{1,1,}},}},{11, {{18,{1,1,}},}},{13, {{18,{1,1,}},}},{14, {{18,{1,1,}},}},},
    {{8, {{22,{1,1,}},}},{9, {{22,{1,1,}},}},{11, {{22,{1,1,}},}},{13, {{22,{1,1,}},}},{14, {{22,{1,1,}},}},},
    {{8, {{20,{1,1,}},}},{9, {{20,{1,1,}},}},{11, {{20,{1,1,}},}},{13, {{20,{1,1,}},}},{14, {{20,{1,1,}},}},},
    {{4, {{36,{1,}},}},{5, {{36,{1,}},}},{12, {{36,{1,}},}},{14, {{36,{1,}},}},},
    {{4, {{38,{1,}},}},{5, {{38,{1,}},}},{12, {{38,{1,}},}},{14, {{38,{1,}},}},},
    {{4, {{40,{1,}},}},{5, {{40,{1,}},}},{12, {{40,{1,}},}},{14, {{40,{1,}},}},},
    {{4, {{32,{1,1,1,}},}},{5, {{32,{1,1,1,}},}},{12, {{32,{1,1,1,}},}},{14, {{32,{1,1,1,}},}},},
    {{8, {{69,{}},}},{9, {{51,{}},}},{11, {{73,{}},}},{13, {{75,{}},}},{14, {{77,{}},}},{17, {{53,{}},}},{18, {{67,{}},}},{21, {{55,{}},}},},
    {{1, {{12,{1,0,1,}},}},{8, {{12,{1,0,1,}},}},{9, {{12,{1,0,1,}},}},{11, {{12,{1,0,1,}},}},{13, {{12,{1,0,1,}},}},{14, {{12,{1,0,1,}},}},},
    {{4, {{57,{}},}},{5, {{59,{}},}},{12, {{83,{}},}},{14, {{19,{}},}},{15, {{21,{}},}},},
    {{1, {{10,{1,0,0,1,1,}},}},{8, {{10,{1,0,0,1,1,}},}},{9, {{10,{1,0,0,1,1,}},}},{11, {{10,{1,0,0,1,1,}},}},{13, {{10,{1,0,0,1,1,}},}},{14, {{10,{1,0,0,1,1,}},}},},
    {{8, {{69,{}},}},{9, {{61,{}},}},{11, {{73,{}},}},{13, {{75,{}},}},{14, {{77,{}},}},{18, {{27,{}},}},{21, {{29,{}},}},},
    {{8, {{6,{0,1,}},}},{9, {{6,{0,1,}},}},{11, {{31,{}},{6,{0,1,}},}},{13, {{33,{}},{6,{0,1,}},}},{14, {{35,{}},{6,{0,1,}},}},},
    {{8, {{69,{}},}},{9, {{63,{}},}},{11, {{73,{}},}},{13, {{75,{}},}},{14, {{77,{}},}},{17, {{65,{}},}},{18, {{67,{}},}},{21, {{55,{}},}},},
    {{1, {{12,{1,1,1,}},}},{8, {{12,{1,1,1,}},}},{9, {{12,{1,1,1,}},}},{11, {{12,{1,1,1,}},}},{13, {{12,{1,1,1,}},}},{14, {{12,{1,1,1,}},}},},
    {{1, {{10,{1,0,1,1,1,}},}},{8, {{10,{1,0,1,1,1,}},}},{9, {{10,{1,0,1,1,1,}},}},{11, {{10,{1,0,1,1,1,}},}},{13, {{10,{1,0,1,1,1,}},}},{14, {{10,{1,0,1,1,1,}},}},},
    {{1, {{10,{1,1,1,0,1,}},}},{8, {{10,{1,1,1,0,1,}},}},{9, {{10,{1,1,1,0,1,}},}},{11, {{10,{1,1,1,0,1,}},}},{13, {{10,{1,1,1,0,1,}},}},{14, {{10,{1,1,1,0,1,}},}},},
    {{8, {{69,{}},}},{9, {{71,{}},}},{11, {{73,{}},}},{13, {{75,{}},}},{14, {{77,{}},}},{18, {{27,{}},}},{21, {{29,{}},}},},
    {{8, {{4,{0,1,}},}},{9, {{4,{0,1,}},}},{11, {{4,{0,1,}},}},{13, {{4,{0,1,}},}},{14, {{4,{0,1,}},}},},
    {{4, {{45,{}},}},{5, {{47,{}},}},{12, {{83,{}},}},{14, {{79,{}},}},{15, {{81,{}},}},{16, {{49,{}},}},},
    {{1, {{10,{1,1,1,1,1,}},}},{8, {{10,{1,1,1,1,1,}},}},{9, {{10,{1,1,1,1,1,}},}},{11, {{10,{1,1,1,1,1,}},}},{13, {{10,{1,1,1,1,1,}},}},{14, {{10,{1,1,1,1,1,}},}},},
    {{8, {{18,{0,1,}},}},{9, {{18,{0,1,}},}},{11, {{18,{0,1,}},}},{13, {{18,{0,1,}},}},{14, {{18,{0,1,}},}},},
    {{8, {{22,{0,1,}},}},{9, {{22,{0,1,}},}},{11, {{22,{0,1,}},}},{13, {{22,{0,1,}},}},{14, {{22,{0,1,}},}},},
    {{8, {{20,{0,1,}},}},{9, {{20,{0,1,}},}},{11, {{20,{0,1,}},}},{13, {{20,{0,1,}},}},{14, {{20,{0,1,}},}},},
    {{4, {{28,{0,1,}},}},{5, {{28,{0,1,}},}},{12, {{28,{0,1,}},}},{14, {{28,{0,1,}},}},},
    {{4, {{26,{0,1,}},}},{5, {{26,{0,1,}},}},{12, {{26,{0,1,}},}},{14, {{26,{0,1,}},}},},
    {{3, {{17,{}},}},{4, {{34,{1,}},}},{5, {{34,{1,}},}},{12, {{34,{1,}},}},{14, {{34,{1,}},}},},
};

PXML::Pxml PxmlParser::parse(){
    // Prepare
    std::stack<Stack::iterator> branches;
    Stack stack;
    stack.push(fetch(), 0);
    auto throw_error = [&](term_t term){
        if(branches.empty()){
            throw ParseError(term);
        }
        auto& saved = branches.top();
        auto buf_top = buffer.begin();
        for(auto it = stack.begin(); it != saved; it = std::next(it)){
            if(std::holds_alternative<token_t>(it->elem)){
                buffer.emplace(buf_top, it->term, std::get<token_t>(it->elem));
            }else{
                auto flattened = std::get<Node>(it->elem).flatten();
                buffer.insert(buf_top, flattened.begin(), flattened.end());
            }
        }
        saved->branch += 1;
    };
    // Parse
    while(stack.front().state != End){
        Entry& entry = stack.front();
        State& state = table[entry.state];
        if(state.contains(entry.term)){
            std::vector<Act>& acts = state[entry.term];
            if(entry.branch == 0){
                if(acts.size() > 1){
                    branches.emplace(stack.begin());
                }
            }else if(entry.branch == acts.size() - 1){
                branches.pop();
            }
            Act& act = acts[entry.branch];
            if(act.first & 1){ // Shift
                stack.push(fetch(), act.first >> 1);
            }else{ // Reduce
                if(std::holds_alternative<token_t>(entry.elem)){
                    buffer.emplace_front(entry.term, std::get<token_t>(entry.elem));
                    stack.pop_front();
                }
                stack.reduce(act.first >> 1, act.second);
            }
        }else{
            throw_error(entry.term);
        }
    }
    // Expand tree
    return expand_tree(stack.back());
}

void PxmlParser::Stack::reduce(size_t action, std::vector<bool> param_toggle){
    static const std::vector<term_t> signatures {19,17,17,17,18,18,20,20,21,21,21,21,16,16,16,15,15,22,22,22,};
    if(action == 0){
        emplace_front(Entry {.term = 0, .state = End});
        return;
    }
    Node node = {.action = action, .param_toggle = param_toggle};
    size_t param_count = std::count_if(param_toggle.begin(), param_toggle.end(), [](bool val){return val;});
    for(size_t i = 0; i < param_count; ++i){
        node.children.emplace_front(front());
        pop_front();
    }
    Entry* head = &node.children.front();
    while(std::holds_alternative<Node>(head->elem)){
        Node& child = std::get<Node>(head->elem);
        head = &child.children.front();
    }
    Entry& entry = emplace_front();
    entry.term = signatures[action - 1];
    entry.state = head->state;
    entry.elem.emplace<Node>(node);
}

using item_t = std::variant<std::monostate,
    PxmlParser::token_t,
    PXML::Pxml,
    PXML::Value,
    std::list<PXML::Pxml::Child>,
    std::pair<std::string, PXML::Value>,
    std::string,
    std::unordered_map<std::string, PXML::Value>
>;

PXML::Pxml PxmlParser::expand_tree(Entry& tree){
    std::list<std::variant<Node, token_t>> entry_stack;
    std::list<std::pair<Position, item_t>> param_stack;
    auto extract_entry = [&](Entry& entry){
        if(std::holds_alternative<token_t>(entry.elem)){
            entry_stack.emplace_front(std::get<token_t>(entry.elem));
        }else if(std::holds_alternative<Node>(entry.elem)){
            Node& elem = std::get<Node>(entry.elem);
            Node& node = std::get<Node>(entry_stack.emplace_front(Node {.action = elem.action, .param_toggle = elem.param_toggle}));
            node.children.swap(elem.children);
        }
    };
    extract_entry(tree);
    auto invoke_action = [&](Node& node){
        std::vector<Position> positions(node.param_toggle.size());
        std::vector<item_t> params(node.param_toggle.size());
        Position pos;
        for(size_t i = node.param_toggle.size(); i > 0; --i){
            size_t index = i - 1;
            if(node.param_toggle[index]){
                positions[index] = param_stack.front().first;
                params[index] = param_stack.front().second;
                param_stack.pop_front();
            }
        }
        for(size_t i = 0; i < node.param_toggle.size(); ++i){
            if(node.param_toggle[i]){
                pos = positions[i];
                break;
            }
        }
        switch(node.action){
            case 1: 
                param_stack.emplace_front(pos, action_1(positions,
                    node.param_toggle[0] ? std::get<Tokens::Doctype>(std::get<Token>(params[0])) : Tokens::Doctype(),
                    node.param_toggle[1] ? std::get<std::string>(params[1]) : std::string(),
                    node.param_toggle[2] ? std::get<PXML::Pxml>(params[2]) : PXML::Pxml(),
                    node.param_toggle[3] ? std::get<std::string>(params[3]) : std::string()
                ));
            break;
            case 2: 
                param_stack.emplace_front(pos, action_2(positions,
                    node.param_toggle[0] ? std::get<std::list<PXML::Pxml::Child>>(params[0]) : std::list<PXML::Pxml::Child>(),
                    node.param_toggle[1] ? std::get<PXML::Pxml>(params[1]) : PXML::Pxml()
                ));
            break;
            case 3: 
                param_stack.emplace_front(pos, action_3(positions,
                    node.param_toggle[0] ? std::get<std::list<PXML::Pxml::Child>>(params[0]) : std::list<PXML::Pxml::Child>(),
                    node.param_toggle[1] ? std::get<std::string>(params[1]) : std::string()
                ));
            break;
            case 4: 
                param_stack.emplace_front(pos, action_4(positions
                ));
            break;
            case 5: 
                param_stack.emplace_front(pos, action_5(positions,
                    node.param_toggle[0] ? std::get<Tokens::Tag>(std::get<Token>(params[0])) : Tokens::Tag(),
                    node.param_toggle[1] ? std::get<std::unordered_map<std::string, PXML::Value>>(params[1]) : std::unordered_map<std::string, PXML::Value>(),
                    node.param_toggle[2] ? std::get<Tokens::Close>(std::get<Token>(params[2])) : Tokens::Close(),
                    node.param_toggle[3] ? std::get<std::list<PXML::Pxml::Child>>(params[3]) : std::list<PXML::Pxml::Child>(),
                    node.param_toggle[4] ? std::get<Tokens::Tail>(std::get<Token>(params[4])) : Tokens::Tail()
                ));
            break;
            case 6: 
                param_stack.emplace_front(pos, action_6(positions,
                    node.param_toggle[0] ? std::get<Tokens::Tag>(std::get<Token>(params[0])) : Tokens::Tag(),
                    node.param_toggle[1] ? std::get<std::unordered_map<std::string, PXML::Value>>(params[1]) : std::unordered_map<std::string, PXML::Value>(),
                    node.param_toggle[2] ? std::get<Tokens::Inline>(std::get<Token>(params[2])) : Tokens::Inline()
                ));
            break;
            case 7: 
                param_stack.emplace_front(pos, action_7(positions,
                    node.param_toggle[0] ? std::get<std::string>(params[0]) : std::string(),
                    node.param_toggle[1] ? std::get<Tokens::Space>(std::get<Token>(params[1])) : Tokens::Space()
                ));
            break;
            case 8: 
                param_stack.emplace_front(pos, action_8(positions
                ));
            break;
            case 9: 
                param_stack.emplace_front(pos, action_9(positions,
                    node.param_toggle[0] ? std::get<std::string>(params[0]) : std::string(),
                    node.param_toggle[1] ? std::get<Tokens::Text>(std::get<Token>(params[1])) : Tokens::Text()
                ));
            break;
            case 10: 
                param_stack.emplace_front(pos, action_10(positions,
                    node.param_toggle[0] ? std::get<std::string>(params[0]) : std::string(),
                    node.param_toggle[1] ? std::get<Tokens::Space>(std::get<Token>(params[1])) : Tokens::Space()
                ));
            break;
            case 11: 
                param_stack.emplace_front(pos, action_11(positions,
                    node.param_toggle[0] ? std::get<std::string>(params[0]) : std::string(),
                    node.param_toggle[1] ? std::get<Tokens::Entity>(std::get<Token>(params[1])) : Tokens::Entity()
                ));
            break;
            case 12: 
                param_stack.emplace_front(pos, action_12(positions
                ));
            break;
            case 13: 
                param_stack.emplace_front(pos, action_13(positions,
                    node.param_toggle[0] ? std::get<std::unordered_map<std::string, PXML::Value>>(params[0]) : std::unordered_map<std::string, PXML::Value>(),
                    node.param_toggle[1] ? std::get<std::pair<std::string, PXML::Value>>(params[1]) : std::pair<std::string, PXML::Value>()
                ));
            break;
            case 14: 
                param_stack.emplace_front(pos, action_14(positions,
                    node.param_toggle[0] ? std::get<std::unordered_map<std::string, PXML::Value>>(params[0]) : std::unordered_map<std::string, PXML::Value>(),
                    node.param_toggle[1] ? std::get<Tokens::Space>(std::get<Token>(params[1])) : Tokens::Space()
                ));
            break;
            case 15: 
                param_stack.emplace_front(pos, action_15(positions
                ));
            break;
            case 16: 
                param_stack.emplace_front(pos, action_16(positions,
                    node.param_toggle[0] ? std::get<Tokens::ID>(std::get<Token>(params[0])) : Tokens::ID(),
                    node.param_toggle[1] ? std::get<Tokens::Equal>(std::get<Token>(params[1])) : Tokens::Equal(),
                    node.param_toggle[2] ? std::get<PXML::Value>(params[2]) : PXML::Value()
                ));
            break;
            case 17: 
                param_stack.emplace_front(pos, action_17(positions,
                    node.param_toggle[0] ? std::get<Tokens::ID>(std::get<Token>(params[0])) : Tokens::ID()
                ));
            break;
            case 18: 
                param_stack.emplace_front(pos, action_18(positions,
                    node.param_toggle[0] ? std::get<Tokens::Bool>(std::get<Token>(params[0])) : Tokens::Bool()
                ));
            break;
            case 19: 
                param_stack.emplace_front(pos, action_19(positions,
                    node.param_toggle[0] ? std::get<Tokens::Number>(std::get<Token>(params[0])) : Tokens::Number()
                ));
            break;
            case 20: 
                param_stack.emplace_front(pos, action_20(positions,
                    node.param_toggle[0] ? std::get<Tokens::String>(std::get<Token>(params[0])) : Tokens::String()
                ));
            break;
            default:
            break;
        }
    };
    while(!entry_stack.empty()){
        std::variant<Node, token_t>& entry = entry_stack.front();
        if(std::holds_alternative<token_t>(entry)){
            token_t token = std::get<token_t>(entry);
            param_stack.emplace_front(token.pos, token);
            entry_stack.pop_front();
        }else if(std::holds_alternative<Node>(entry)){
            Node& node = std::get<Node>(entry);
            if(node.children.size() > 0){
                for(auto it = node.children.rbegin(); it != node.children.rend(); it = std::next(it)){
                    extract_entry(*it);
                }
                node.children.clear();
            }else{
                invoke_action(node);
                entry_stack.pop_front();
            }
        }
    }
    return std::get<PXML::Pxml>(param_stack.front().second);
}

std::list<std::pair<PxmlParser::term_t,PxmlParser::token_t>> PxmlParser::Node::flatten(){
    std::list<std::pair<term_t,token_t>> results;
    for(Entry& child : children){
        if(std::holds_alternative<token_t>(child.elem)){
            results.emplace_back(child.term, std::get<token_t>(child.elem));
        }else{
            auto flattened = std::get<Node>(child.elem).flatten();
            results.insert(results.end(), flattened.begin(), flattened.end());
        }
    }
    return results;
}

ParsePxml::ParseError::ParseError(PxmlParser::term_t term){
    static const std::vector<std::string> terms {
        "",
        "EOF",
        "Doctype",
        "Equal",
        "Close",
        "Inline",
        "Bool",
        "Number",
        "Tag",
        "Tail",
        "String",
        "Text",
        "ID",
        "Entity",
        "Space",
        "attribute",
        "attributes",
        "body",
        "element",
        "pxml",
        "spaces",
        "text",
        "value",
    };
    msg = "unexpected " + terms[term];
}
} // namespace ParsePxml


