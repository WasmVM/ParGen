#ifndef Luison_pxml_Lexer_DEF
#define Luison_pxml_Lexer_DEF

#include <iostream>
#include <filesystem>

struct Lexer : public yyFlexLexer {
    Lexer(std::filesystem::path path, std::istream& stream);
    yy::parser::symbol_type lex();
    location_t loc();
private:
    position_t pos;
};

#endif