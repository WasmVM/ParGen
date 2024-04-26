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
        position_t operator+ (size_t);
    };
    struct location_t {
        location_t(position_t pos = position_t()) : begin(pos), end(pos){}
        location_t(position_t begin, position_t end) : begin(begin), end(end){}
        position_t begin, end;
    };
}

%code {
    #include <exception.hpp>
    #include <Lexer.hpp>
    #define yylex() lexer.lex()
}

%token DOCTYPE EQUAL CLOSE INLINE
%token <bool> BOOL
%token <double> NUMBER
%token <std::string> TAG TAIL STRING CHAR ID ENTITY SPACE
%token END 0

%%

%start  pxml;

pxml :  DOCTYPE spaces element spaces END   {std::cout << "pxml" << std::endl;}

content :   element {std::cout << "content.element" << std::endl;}
    |       text    {std::cout << "content.text" << std::endl;}

body :  body content        {std::cout << "body.content" << std::endl;}
    |   %empty              {std::cout << "body.EMPTY" << std::endl;}

element :   TAG attr_list CLOSE body TAIL     {std::cout << "element.CLOSE" << std::endl;}
    |       TAG attr_list INLINE              {std::cout << "element.INLINE" << std::endl;}


spaces :    spaces SPACE   {std::cout << "spaces.SPACE" << std::endl;}
    |       %empty          {std::cout << "spaces.EMPTY" << std::endl;}

text :  CHAR    {std::cout << "text.CHAR" << std::endl;}
    |   ENTITY  {std::cout << "text.ENTITY" << std::endl;}
    |   SPACE   {std::cout << "text.SPACE" << std::endl;}

attr_list : attr_list attribute {std::cout << "attr_list" << std::endl;}
    |       %empty  {std::cout << "attr_list.EMPTY" << std::endl;}

attribute : ID EQUAL value  {std::cout << "attribute.ID = value" << std::endl;}
    |       ID  {std::cout << "attribute.ID" << std::endl;}

value : BOOL    {std::cout << "value.Bool" << std::endl;}
    |   NUMBER  {std::cout << "value.Number" << std::endl;}
    |   STRING  {std::cout << "value.String" << std::endl;}

%%

#include <sstream>

void yy::parser::error(location_t const& loc, std::string const& msg){
    std::stringstream ss;
    ss << loc.begin.path.filename().string() << ":" << loc.begin.line << ":" << loc.begin.column << " error: " << msg;
    throw Exception::Exception(ss.str());
}

position_t position_t::operator+ (size_t value){
    position_t res(*this);
    res.column += value;
    return res;
}