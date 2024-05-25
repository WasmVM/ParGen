#ifndef ParGen_ParGen_DEF
#define ParGen_ParGen_DEF

#include <string>
#include <utility>
#include <variant>
#include <optional>
#include <list>
#include <regex>
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

struct Rule {
    std::string id;
    std::string pattern;
    std::optional<std::string> push = std::nullopt;
    bool pop = false;
    bool more = false;
    std::string content;
};

struct Use {
    std::string id;
};

struct State : public std::list<std::variant<Rule, Use, State>> {
    std::string name;
};

struct ParGen;

struct Tokens : public std::list<Token> {

    std::string class_name = "Token";
    std::string name_space = "Pargen::Tokens";
    std::filesystem::path header_path = "Token.hpp";
    std::filesystem::path source_path = "Token.cpp";
    std::string header_prologue;
    std::string header_epilogue;
    std::string source_prologue;
    std::string source_epilogue;
    std::vector<std::string> members;
    std::vector<std::string> functions;

    Tokens(ParGen& parent) : std::list<Token>(), parent(parent){}
    void generate_header(std::ostream& output);
    void generate_source(std::ostream& output);

private:
    ParGen& parent;
};

struct Lexer : public std::list<std::variant<Rule, State>>{

    std::string class_name = "Lexer";
    std::string new_line;
    std::filesystem::path header_path = "Lexer.hpp";
    std::filesystem::path source_path = "Lexer.cpp";
    std::string header_prologue;
    std::string header_epilogue;
    std::string source_prologue;
    std::string source_epilogue;
    std::vector<std::string> members;
    std::vector<std::string> functions;

    Lexer(ParGen& parent) : new_line("\\n"), parent(parent) {}
    void generate_header(std::ostream& output);
    void generate_source(std::ostream& output);

    ParGen& parent;
};

struct Options {
    bool debug = false;
};

struct ParGen {

    ParGen(Options options = {}) : tokens(*this), lexer(*this), options(options){}
    void load(std::filesystem::path pxml_path);

    std::string name_space = "Pargen";
    std::list<std::filesystem::path> includes;
    Tokens tokens;
    Lexer lexer;
    Options options;
};

} // namespace Pargen

#endif