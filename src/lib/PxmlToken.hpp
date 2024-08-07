/** generated by ParGen **/
#ifndef ParGen_Tokens_guard
#define ParGen_Tokens_guard

#include <string>
        
#include <iostream>
#include <filesystem>
#include <variant>

namespace ParsePxml {

struct Position {
    std::filesystem::path path;
    size_t line = 1;
    size_t column = 0;
};

namespace Tokens {

struct Doctype {
    Doctype() = default;
};

struct Equal {
    Equal() = default;
};

struct Close {
    Close() = default;
};

struct Inline {
    Inline() = default;
};

struct Bool {
    Bool() = default;
    Bool(bool value) : value(value){}
    bool value;
};

struct Number {
    Number() = default;
    Number(double value) : value(value){}
    double value;
};

struct Tag {
    Tag() = default;
    Tag(std::string value) : value(value){}
    std::string value;
};

struct Tail {
    Tail() = default;
    Tail(std::string value) : value(value){}
    std::string value;
};

struct String {
    String() = default;
    String(std::string value) : value(value){}
    std::string value;
};

struct Text {
    Text() = default;
    Text(std::string value) : value(value){}
    std::string value;
};

struct ID {
    ID() = default;
    ID(std::string value) : value(value){}
    std::string value;
};

struct Entity {
    Entity() = default;
    Entity(std::string value) : value(value){}
    std::string value;
};

struct Space {
    Space() = default;
    Space(std::string value) : value(value){}
    std::string value;
};

} // namespace Tokens

struct Token : public std::variant<
  std::monostate,
  Tokens::Doctype,
  Tokens::Equal,
  Tokens::Close,
  Tokens::Inline,
  Tokens::Bool,
  Tokens::Number,
  Tokens::Tag,
  Tokens::Tail,
  Tokens::String,
  Tokens::Text,
  Tokens::ID,
  Tokens::Entity,
  Tokens::Space
> {
template<typename T> Token(T token, Position pos): std::variant<
  std::monostate,
  Tokens::Doctype,
  Tokens::Equal,
  Tokens::Close,
  Tokens::Inline,
  Tokens::Bool,
  Tokens::Number,
  Tokens::Tag,
  Tokens::Tail,
  Tokens::String,
  Tokens::Text,
  Tokens::ID,
  Tokens::Entity,
  Tokens::Space
>(token), pos(pos){}
    Position pos;
};

} // namespace ParsePxml

std::ostream& operator<< (std::ostream&, ParsePxml::Position&);

#endif 
