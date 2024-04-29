%{
#include "pxml_parser.hpp"
#include <Lexer.hpp>

#define YY_DECL yy::parser::symbol_type Lexer::lex()

#define yyterminate() return yy::parser::make_END(loc())

%}

%option noyywrap c++ nounput noinput batch yylineno stack
%option outfile="pxml_lexer.cpp"

%x Tag String StrEscape TagTail Comment

%%

\<!(?i:DOCTYPE).*\> { pos.line += 1; pos.column = 1; return yy::parser::make_DOCTYPE(loc()); }

\{\%                { loc(); yy_push_state(Comment); }                        
<Comment>\%\}       { loc(); yy_pop_state(); }
<Comment>[^%]+      { loc(); }
<Comment>%          { loc(); }
<Comment>[\n]                   { pos.line += 1; pos.column = 1; }
<Comment>[[:space:]\t\v\r]+     { loc(); }

\<\/[[:alpha:]][[:alnum:]]*     { yymore(); BEGIN(TagTail); }
<TagTail>\{\%                   { loc(); yy_push_state(Comment); }
<TagTail>[\n]                   { pos.line += 1; pos.column = 1; }
<TagTail>[[:space:]\t\v\r]+     { loc(); }
<TagTail>\>                     { BEGIN(INITIAL); return yy::parser::make_TAIL(YYText(), loc()); }

\<[[:alnum:]]+                  { BEGIN(Tag); return yy::parser::make_TAG(std::string(YYText()).substr(1), loc()); }
<Tag>\{\%                       { loc(); yy_push_state(Comment); }
<Tag>[\n]                       { pos.line += 1; pos.column = 1; }
<Tag>[[:space:]\t\v\r]+         { loc(); }
<Tag>\/\>                       { BEGIN(INITIAL); return yy::parser::make_INLINE(loc());}
<Tag>\>                         { BEGIN(INITIAL); return yy::parser::make_CLOSE(loc());}
<Tag>\"                         { yymore(); BEGIN(String); }
<Tag>=                          { return yy::parser::make_EQUAL(loc()); }

<Tag>("true"|"false")           { return yy::parser::make_BOOL(std::string(YYText()) == "true", loc()); }
<Tag>[[:alpha:]][[:alnum:]]*    { return yy::parser::make_ID(YYText(), loc()); }
<Tag>[0-9\-]+(\.[0-9]*)?([eE][+\-]?[0-9]+)?  { return yy::parser::make_NUMBER(std::stod(YYText()), loc()); }

<String>\\                      { yymore(); BEGIN(StrEscape); }
<String>\"                      { BEGIN(Tag); return yy::parser::make_STRING(YYText(), loc()); }
<String>[^\\\"]+                { yymore(); }
<StrEscape>.                    { yymore(); BEGIN(String); }

[\n]                                { pos.line += 1; pos.column = 1; return yy::parser::make_SPACE(YYText(), loc());}
[[:space:]\t\v\r]+                  { return yy::parser::make_SPACE(YYText(), loc()); }
&("amp"|"lt"|"gt"|"apos"|"quot");   { return yy::parser::make_ENTITY(YYText(), loc()); }
<<EOF>>                             { yyterminate(); }
\\\<                                { return yy::parser::make_TEXT("<", loc()); }
.                                   { return yy::parser::make_TEXT(YYText(), loc()); }

%%

location_t Lexer::loc(){
    position_t old = pos;
    pos.column += YYLeng();
    return location_t(old, pos);
}

Lexer::Lexer(std::filesystem::path path, std::istream& stream) : yyFlexLexer(stream, std::cout){
    pos.path = path;
}

int yyFlexLexer::yylex(){
    return -1;
}