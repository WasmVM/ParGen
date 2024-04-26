#ifndef Luison_pxml_Lexer_DEF
#define Luison_pxml_Lexer_DEF

#include <fstream>
#include <filesystem>

struct Lexer : public yyFlexLexer {
    Lexer(std::filesystem::path path);
    ~Lexer();
    yy::parser::symbol_type lex();
    void update_pos();
private:
    std::ifstream stream;
    position_t pos;
};

#endif