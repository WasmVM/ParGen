%{
#include "pxml_parser.hpp"
#include <Lexer.hpp>

#define YY_DECL yy::parser::symbol_type Lexer::lex()

#define yyterminate() return yy::parser::make_END(location_t(pos));

%}

%option noyywrap c++ nounput noinput batch yylineno
%option outfile="pxml_lexer.cpp"

%x Tag TagName String StrEscape

%%

\<!(?i:DOCTYPE).*\>             { std::cout << "DOCTYPE"; }

<TagName>\/[[:alpha:]][[:alnum:]]*[ \t\v\r\n]*\>    { std::cout << "Tail " << YYText() << std::endl; BEGIN(INITIAL);}
<TagName>[[:alpha:]][[:alnum:]]*                    { std::cout << "Tag " << YYText() << std::endl; BEGIN(Tag);}

<Tag>[ \t\v\r\n]                {}
<Tag>\/?\>                      { BEGIN(INITIAL); }
<Tag>\"                         { yymore(); BEGIN(String); }
<Tag>=                          { std::cout << "Equal"<< std::endl; }

<Tag>("true"|"false")           { std::cout << "Bool " << YYText() << std::endl; }
<Tag>[[:alpha:]][[:alnum:]]*    { std::cout << "ID " << YYText() << std::endl; }
<Tag>[0-9\-]+(\.[0-9]*)?([eE][+\-]?[0-9]+)?  { std::cout << "Number " << YYText() << std::endl; }

<String>\\                      { yymore(); BEGIN(StrEscape); }
<String>\"                      { std::cout << "String " << YYText() << std::endl; BEGIN(Tag); }
<String>.                       { yymore(); }
<StrEscape>.                    { yymore(); BEGIN(String); }

\<                                  { BEGIN(TagName); }
[ \t\v\r]+                          { std::cout << " "; }
[\n]+                               { std::cout << std::endl; }
&("amp"|"lt"|"gt"|"apos"|"quot");   { std::cout << "Entity " << YYText() << std::endl;}
.                                   { std::cout << "Char " << YYText() << std::endl; }

%%

void Lexer::update_pos(){
    pos.line = lineno();
    pos.column += YYLeng();
}

Lexer::Lexer(std::filesystem::path path) : yyFlexLexer(stream, std::cout){
    pos.path = path;
    stream.open(path);
}

Lexer::~Lexer(){
    stream.close();
}

int yyFlexLexer::yylex(){
    return -1;
}