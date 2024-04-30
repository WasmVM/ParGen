#ifndef ParGen_ParGen_DEF
#define ParGen_ParGen_DEF

#include <string>
#include <list>
#include <iostream>
#include <filesystem>
#include <Pxml.hpp>

namespace Pargen {

struct Token {
    enum AccessType {GET, CAST};
    AccessType access;
    std::string name;
};

struct Tokens : public std::list<Token> {
    std::string class_name;
    std::string name_space;
    std::filesystem::path header_path = "Token.hpp";
    std::string prologue;
    std::string epilogue;
    void generate_header(std::ostream& output);
};

struct ParGen {
    
    void init(std::filesystem::path pxml_path);

    std::string name_space;
    std::list<std::filesystem::path> includes;
    Tokens tokens;
};

} // namespace Pargen

#endif