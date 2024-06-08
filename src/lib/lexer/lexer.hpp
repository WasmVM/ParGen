#ifndef ParGen_pxml_Lexer_types_DEF
#define ParGen_pxml_Lexer_types_DEF

#include <ParGen.hpp>

#include <set>
#include <algorithm>
#include <list>
#include <variant>
#include <deque>

using char_t = std::istream::int_type;

struct Autometa {

    Autometa(Pargen::Lexer& lexer);

    struct Action {
        enum Flags : uint8_t {
            None = 0,
            More = 1,
            Pop = 2
        };
        Flags flags = None;
        std::string pxml_state;
        std::string content = "";
        std::optional<std::string> push;
    };
    
    enum class StateType {None, Final, Start, End};
    
    struct Char : public std::optional<char_t> {
        static constexpr char_t eof = std::istream::traits_type::eof();
        Char(std::optional<char_t> value = std::nullopt, bool negate = false)
            : std::optional<char_t>(value), negate(negate){}

        bool operator<(const Char& rhs) const {
            if(negate != rhs.negate){
                return negate;
            }else if(has_value() != rhs.has_value()){
                return !has_value();
            }else if(has_value()){
                return value() < rhs.value();
            }
            return false;
        }
        bool negate;
    };

    struct State : public std::deque<std::pair<Char, size_t>> {
        State() = default;
        State(const State&);
        StateType type;
        std::optional<size_t> action_id;
    };

    std::deque<State> states;
    std::unordered_map<std::string, size_t> group_map;
    std::deque<Action> actions;
    std::ostream& dump(std::ostream& os);
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

struct CharNode : public Node {

    struct Char : public std::set<char_t>{
        static constexpr char_t eof = std::istream::traits_type::eof();
        enum Class {Number, Alphabet, Space};
        bool negate = false;
        Char() = default;
        Char(const Class cl);
        Char(const char_t ch){
            insert(ch);
        }

        bool is_any() const{
            return contains('\0');
        }

        Char operator!(){
            negate = !negate;
            return *this;
        }
        Char operator+(const Char& rhs){
            Char result;
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
        Char& operator+=(const Char& rhs){
            *this = (*this + rhs);
            return *this;
        }
    };

    Char value;
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

using namespace Pargen;

void resolve_use(std::list<std::variant<Rule, Group>>& rules);
Node* parse_pattern(std::string& pattern);
std::ostream& operator<< (std::ostream& os, CharNode::Char& character);
std::ostream& operator<< (std::ostream& os, Autometa::Char& character);
std::ostream& operator<< (std::ostream& os, Autometa& autometa);

#endif