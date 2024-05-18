#ifndef ParGen_pxml_Lexer_DEF
#define ParGen_pxml_Lexer_DEF

#include <iostream>
#include <filesystem>
#include <location.hh>

struct Lex : public yyFlexLexer {
    Lex(std::filesystem::path filename, std::istream& stream) : yyFlexLexer(stream, std::cout){
        loc.initialize(new std::filesystem::path(filename));
    };
    yy::parser::symbol_type lex();
private:
    yy::location loc;
};

#endif