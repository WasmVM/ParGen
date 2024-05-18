%require "3.8.1"
%language "c++"
%header
%define api.token.raw
%define api.token.constructor
%define api.value.type variant
%locations
%define api.filename.type {std::filesystem::path}
%define parse.error detailed
%define parse.lac full
%parse-param { Lex& lexer }{ PXML::Pxml& pxml }

%code requires {
    #include <list>
    #include <utility>
    #include <filesystem>
    #include <Pxml.hpp>
#ifndef yyFlexLexerOnce
    #include <FlexLexer.h>
#endif
    struct Lex;
}

%code {
    #include <exception.hpp>
    #include <Lex.hpp>
    #define yylex() lexer.lex()

    PXML::Position to_pos(yy::location& loc){
        PXML::Position pos {
            .path = *loc.begin.filename,
            .line = (size_t)loc.begin.line,
            .column = (size_t)loc.begin.column,
        };
        return pos;
    }
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

pxml :  DOCTYPE spaces element spaces END 
    {
        pxml = $3;
        pxml.pos = to_pos(@3);
    }

content :   element { $$.first = to_pos(@1); $$.second = $1; }
    |       text    { $$.first = to_pos(@1); $$.second = $1; }

body :  body content
        { 
            if(!$1.empty() && std::holds_alternative<std::string>($1.back().second) && std::holds_alternative<std::string>($2.second)){
                std::get<std::string>($1.back().second) += std::get<std::string>($2.second);
            }else{
                $1.emplace_back($2);
            }
            $$ = $1;
        }
    |   %empty              {}

element :   TAG attr_list CLOSE body TAIL
        {
            if($1 != $5){
                error(@5, "tag not match");
            }
            $$.tag = $1;
            $$.pos = to_pos(@1);
            for(auto attr_pair : $2){
                $$[attr_pair.first] = attr_pair.second;
            }
            $$.children.insert($$.children.end(), $4.begin(), $4.end());
        }
    |       TAG attr_list INLINE
        {
            $$.tag = $1;
            $$.pos = to_pos(@1);
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

attribute : ID EQUAL value  { $$.first = $1; $$.second = $3; $$.second.first = to_pos(@1);}
    |       ID  { $$.first = $1; $$.second.first = to_pos(@1);}

value : BOOL    { $$.first = to_pos(@1); $$.second.emplace<bool>($1); }
    |   NUMBER  { $$.first = to_pos(@1); $$.second.emplace<double>($1); }
    |   STRING  { $$.first = to_pos(@1); $$.second.emplace<std::string>($1.substr(1, $1.size() - 2)); }

%%

#include <sstream>

void yy::parser::error(yy::location const& loc, std::string const& msg){
    yy::location l = loc;
    throw Exception::SyntaxError(msg, to_pos(l));
}