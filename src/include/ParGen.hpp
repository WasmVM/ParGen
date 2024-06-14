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

struct Grammar {
    std::string target;
    std::vector<std::string> depends;
    std::string content;
};

struct Group : public std::list<std::variant<Rule, Use, Group>> {
    std::string name;
};

struct ParGen;

struct Component {
    std::string class_name;
    std::filesystem::path header_path;
    std::filesystem::path source_path;
    std::string header_prologue;
    std::string header_epilogue;
    std::string source_prologue;
    std::string source_epilogue;
    std::vector<std::string> members;
    std::vector<std::string> functions;
    virtual void generate_header(std::ostream& output) = 0;
    virtual void generate_source(std::ostream& output) = 0;
};

struct Tokens : public std::list<Token>, Component{

    std::string name_space = "Pargen::Tokens";

    Tokens(ParGen& parent) : std::list<Token>(), parent(parent){
        class_name = "Token";
        header_path = "Token.hpp";
        source_path = "Token.cpp";
    }
    void generate_header(std::ostream& output);
    void generate_source(std::ostream& output);

private:
    ParGen& parent;
};

struct Lexer : public std::list<std::variant<Rule, Group>>, Component{

    std::string new_line = "\n";
    std::string return_type;

    Lexer(ParGen& parent) : std::list<std::variant<Rule, Group>>(), new_line("\\n"), parent(parent){
        class_name = "Lexer";
        header_path = "Lexer.hpp";
        source_path = "Lexer.cpp";
    }
    void generate_header(std::ostream& output);
    void generate_source(std::ostream& output);

    ParGen& parent;
};

struct Parser : public std::list<Grammar>, Component {

    std::string start = "";
    std::string return_type = "void";

    Parser(Pargen::ParGen& parent) : std::list<Grammar>(), parent(parent){
        class_name = "Parser";
        header_path = "Parser.hpp";
        source_path = "Parser.cpp";
    }
    void generate_header(std::ostream& output);
    void generate_source(std::ostream& output);

    ParGen& parent;
};

struct Options {
    bool debug = false;
};

struct ParGen {

    ParGen(Options options = {}) : tokens(*this), lexer(*this), parser(*this), options(options){}
    void load(std::filesystem::path pxml_path);

    std::string name_space = "Pargen";
    std::list<std::filesystem::path> includes;
    Tokens tokens;
    Lexer lexer;
    Parser parser;
    Options options;
};

} // namespace Pargen

#endif