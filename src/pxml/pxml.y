%require "3.8.1"
%language "c++"
%header
%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%locations
%define api.location.type {location_t}
%define parse.error detailed
%define parse.lac full
%parse-param { Lexer& lexer }{ PXML::Pxml& pxml }

%code requires {
    #include <filesystem>
    #include <Pxml.hpp>
#ifndef yyFlexLexerOnce
    #include <FlexLexer.h>
#endif
    struct Lexer;
    struct position_t {
        std::filesystem::path path = "";
        size_t line = 1;
        size_t column = 1;
    };
    struct location_t {
        location_t(position_t pos = position_t()) : begin(pos), end(pos){}
        position_t begin, end;
    };
}

%code {
    #include <exception.hpp>
    #include <Lexer.hpp>
    #define yylex() lexer.lex()
}

%token DOCTYPE EQUAL
%token <bool> BOOL
%token <double> NUMBER
%token <std::string> TAG TAIL STRING CHAR ID
%token END 0

%%

%start pxml;

pxml :  DOCTYPE element

body :  element
    |   text

element :   TAG attr_list body TAIL

text : text CHAR
    |   %empty

attr_list : attr_list attribute
    |   %empty

attribute : ID EQUAL value
    |       ID

value : BOOL
    |   NUMBER
    |   STRING

%%

#include <sstream>

void yy::parser::error(location_t const& loc, std::string const& msg){
    std::stringstream ss;
    ss << loc.begin.path.string() << ":" << loc.begin.line << ":" << loc.begin.column << " error: " << msg;
    throw Exception::Exception(ss.str());
}