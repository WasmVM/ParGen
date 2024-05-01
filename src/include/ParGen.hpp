#ifndef ParGen_ParGen_DEF
#define ParGen_ParGen_DEF

#include <string>
#include <list>
#include <iostream>
#include <filesystem>
#include <Pxml.hpp>

namespace Pargen {

struct Token {
    std::string name;
    std::vector<std::string> types;
    std::vector<std::string> members;
    std::vector<std::string> functions;
};

struct ParGen;

struct Tokens : public std::list<Token> {

    std::string class_name = "Token";
    std::string name_space = "Pargen::Tokens";
    std::filesystem::path header_path = "Token.hpp";
    std::filesystem::path source_path = "Token.cpp";
    std::string prologue;
    std::string epilogue;
    std::vector<std::string> members;
    std::vector<std::string> functions;

    Tokens(ParGen& parent) : parent(parent){}
    void generate_header(std::ostream& output);

private:
    ParGen& parent;
};

struct ParGen {
    
    ParGen() : tokens(*this){}
    void init(std::filesystem::path pxml_path);

    std::string name_space = "Pargen";
    std::list<std::filesystem::path> includes;
    Tokens tokens;
};

} // namespace Pargen

#endif