#ifndef ParGen_pxml_Lexer_types_DEF
#define ParGen_pxml_Lexer_types_DEF

#include <ParGen.hpp>

#include <set>
#include <algorithm>
#include <list>
#include <variant>
#include <deque>

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

    bool is_any() const{
        return contains('\0');
    }

    CharType operator!(){
        negate = !negate;
        return *this;
    }
    CharType operator+(const CharType& rhs){
        CharType result;
        result.negate = true;
        if(negate == rhs.negate){
            if(is_any() || rhs.is_any()){
                result.negate = negate;
                result.emplace('\0');
            }else if(negate){
                std::set_intersection(begin(), end(), rhs.begin(), rhs.end(), std::inserter(result, result.end()));
            }else{
                std::set_union(begin(), end(), rhs.begin(), rhs.end(), std::inserter(result, result.end()));
                result.negate = false;
            }
        }else{
            if(is_any()){
                result = rhs;
            }else if(rhs.is_any()){
                result = *this;
            }else if(negate){
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

struct Autometa {

    Autometa(Pargen::Lexer& lexer);

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
    enum class StateType {None, Error, Final, Start};
    struct State : public std::deque<std::pair<std::optional<char>, size_t>> {
        StateType type;
        std::optional<size_t> action_id;
    };

    std::deque<State> states;
    std::unordered_map<std::string, size_t> state_map;
    std::deque<Action> actions;
};

using namespace Pargen;

void resolve_use(std::list<std::variant<Rule, State>>& rules);
Node* parse_pattern(std::string& pattern);
std::ostream& operator<< (std::ostream& os, CharType& type);
std::ostream& operator<< (std::ostream& os, Autometa& autometa);

#endif