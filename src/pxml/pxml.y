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
    #include <list>
    #include <utility>
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
%token <std::string> TAG TAIL STRING TEXT ID ENTITY SPACE
%token END 0

%type <PXML::Pxml> element
%type <PXML::Value> value
%type <std::string> text
%type <PXML::Pxml::Child> content
%type <std::list<PXML::Pxml::Child>> body
%type <std::pair<std::string, PXML::Value>> attribute
%type <std::list<std::pair<std::string, PXML::Value>>> attr_list

%%

%start  pxml;

pxml :  DOCTYPE spaces element spaces END   { pxml = $3; }

content :   element { $$ = $1; }
    |       text    { $$ = $1; }

body :  body content        { $1.emplace_back($2); $$ = $1; }
    |   %empty              {}

element :   TAG attr_list CLOSE body TAIL
        {
            $$.tag = $1;
            for(auto attr_pair : $2){
                $$[attr_pair.first] = attr_pair.second;
            }
            $$.children.insert($$.children.end(), $4.begin(), $4.end());
        }
    |       TAG attr_list INLINE
        {
            $$.tag = $1;
            for(auto attr_pair : $2){
                $$[attr_pair.first] = attr_pair.second;
            }
        }


spaces :    spaces SPACE
    |       %empty

text :  TEXT    { $$ = $1; }
    |   SPACE   { $$ = $1; }
    |   ENTITY  
        {
            if($1 == "&amp;"){
                $$ = "&";
            }else if($1 == "&lt;"){
                $$ = "<";
            }else if($1 == "&gt;"){
                $$ = ">";
            }else if($1 == "&apos;"){
                $$ = "'";
            }else if($1 == "&quot;"){
                $$ = "\"";
            }
        }

attr_list : attr_list attribute { $1.emplace_back($2); $$ = $1; }
    |       %empty {}

attribute : ID EQUAL value  { $$.first = $1; $$.second = $3; }
    |       ID  { $$.first = $1; }

value : BOOL    { $$.emplace<bool>($1); }
    |   NUMBER  { $$.emplace<double>($1); }
    |   STRING  { $$.emplace<std::string>($1); }

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