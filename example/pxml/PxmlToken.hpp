/** generated by ParGen **/
#ifndef ParGen_Tokens_Token_guard
#define ParGen_Tokens_Token_guard

#include <string>
        
#include <iostream>
#include <filesystem>
#include <variant>

namespace PXML {

struct Position {
    std::filesystem::path path;
    size_t line = 1;
    size_t column = 0;
};

namespace Tokens {

struct Doctype {};

struct Equal {};

struct Close {};

struct Inline {};

struct Bool {
    bool value;
};

struct Number {
    double value;
};

struct Tag {
    std::string value;
};

struct Tail {
    std::string value;
};

struct String {
    std::string value;
};

struct Text {
    std::string value;
};

struct ID {
    std::string value;
};

struct Entity {
    std::string value;
};

struct Space {
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
    Position pos;
};

} // namespace PXML

std::ostream& operator<< (std::ostream&, PXML::Position&);

#endif 
