%{
#include "pxml_parser.hpp"
#include <Lex.hpp>

#define YY_DECL yy::parser::symbol_type Lex::lex()

#define yyterminate() return yy::parser::make_END(loc)

#define YY_USER_ACTION  loc.columns(yyleng);

%}

%option noyywrap c++ nounput noinput batch yylineno stack
%option outfile="pxml_lexer.cpp"

%x Tag String StrEscape TagTail Comment

%%

%{
  loc.step();
%}

\<!(?i:DOCTYPE).+\> { return yy::parser::make_DOCTYPE(loc); }

\{\%                { loc.step(); yy_push_state(Comment); }   
<Comment>[\n]       { loc.lines(); loc.step(); }
<Comment>[[:space:]\t\v\r]+     {}
<Comment>[^%\{\}]+  {}
<Comment>\{\%       { yy_push_state(Comment); }   
<Comment>\%\}       { yy_pop_state(); }
<Comment>[%\{\}]    {}

\<\/[[:alpha:]][[:alnum:]]*     { yymore(); BEGIN(TagTail); }
<TagTail>\{\%                   { yy_push_state(Comment); }
<TagTail>[\n]                   { loc.lines(); loc.step(); }
<TagTail>[[:space:]\t\v\r]+     {}
<TagTail>\>                     {
                                    BEGIN(INITIAL);
                                    std::string tag(YYText());
                                    tag = tag.substr(2, tag.size() - 3);
                                    return yy::parser::make_TAIL(tag, loc);
                                }

\<[[:alnum:]]+                  { BEGIN(Tag); return yy::parser::make_TAG(std::string(YYText()).substr(1), loc); }
<Tag>\{\%                       { yy_push_state(Comment); }
<Tag>[\n]                       { loc.lines(); loc.step(); }
<Tag>[[:space:]\t\v\r]+         {}
<Tag>\/\>                       { BEGIN(INITIAL); return yy::parser::make_INLINE(loc);}
<Tag>\>                         { BEGIN(INITIAL); return yy::parser::make_CLOSE(loc);}
<Tag>\"                         { yymore(); BEGIN(String); }
<Tag>=                          { return yy::parser::make_EQUAL(loc); }

<Tag>("true"|"false")           { return yy::parser::make_BOOL(std::string(YYText()) == "true", loc); }
<Tag>[[:alpha:]][[:alnum:]]*    { return yy::parser::make_ID(YYText(), loc); }
<Tag>[0-9\-]+(\.[0-9]*)?([eE][+\-]?[0-9]+)?  { return yy::parser::make_NUMBER(std::stod(YYText()), loc); }

<String>\\                      { yymore(); BEGIN(StrEscape); }
<String>\"                      { BEGIN(Tag); return yy::parser::make_STRING(YYText(), loc); }
<String>[^\\\"]+                { yymore(); }
<StrEscape>.                    { yymore(); BEGIN(String); }

[\n]                                { loc.lines(); loc.step(); return yy::parser::make_SPACE(YYText(), loc);}
[[:space:]\t\v\r]+                  { return yy::parser::make_SPACE(YYText(), loc); }
&("amp"|"lt"|"gt"|"apos"|"quot");   { return yy::parser::make_ENTITY(YYText(), loc); }
<<EOF>>                             { yyterminate(); }
\\\<                                { return yy::parser::make_TEXT("<", loc); }
.                                   { return yy::parser::make_TEXT(YYText(), loc); }

%%

int yyFlexLexer::yylex(){
    return -1;
}