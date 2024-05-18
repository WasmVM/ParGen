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

\{\%                { yy_push_state(Comment); loc.step(); }   
<Comment>[\n]       { loc.lines(); loc.step(); }
<Comment>[ \t\v\r]+ { loc.step(); }
<Comment>[^%\{\}]+  { loc.step(); }
<Comment>\{\%       { yy_push_state(Comment); loc.step(); }   
<Comment>\%\}       { yy_pop_state(); loc.step(); }
<Comment>[%\{\}]

\<\/[[:alpha:]][[:alnum:]]*     { yymore(); BEGIN(TagTail); loc.step(); }
<TagTail>[\n]                   { loc.lines(); loc.step(); }
<TagTail>[ \t\v\r]+             { loc.step(); }
<TagTail>\>                     {
                                    BEGIN(INITIAL);
                                    std::string tag(YYText());
                                    tag = tag.substr(2, tag.size() - 3);
                                    return yy::parser::make_TAIL(tag, loc);
                                }

\<[[:alnum:]]+                  { BEGIN(Tag); return yy::parser::make_TAG(std::string(YYText()).substr(1), loc); }
<Tag>[\n]                       { loc.lines(); loc.step(); }
<Tag>[ \t\v\r]+                 { loc.step(); }
<Tag>\/\>                       { BEGIN(INITIAL); return yy::parser::make_INLINE(loc);}
<Tag>\>                         { BEGIN(INITIAL); return yy::parser::make_CLOSE(loc);}
<Tag>\"                         { yymore(); BEGIN(String); loc.step(); }
<Tag>=                          { return yy::parser::make_EQUAL(loc); }

<Tag>("true"|"false")           { return yy::parser::make_BOOL(std::string(YYText()) == "true", loc); }
<Tag>[[:alpha:]][[:alnum:]]*    { return yy::parser::make_ID(YYText(), loc); }
<Tag>[0-9\-]+(\.[0-9]*)?([eE][+\-]?[0-9]+)?  { return yy::parser::make_NUMBER(std::stod(YYText()), loc); }

<String>\\                      { yymore(); BEGIN(StrEscape); loc.step(); }
<String>\"                      { BEGIN(Tag); return yy::parser::make_STRING(YYText(), loc); }
<String>[^\\\"]+                { yymore(); loc.step(); }
<StrEscape>.                    { yymore(); BEGIN(String); loc.step(); }

[\n]                                { loc.lines(); loc.step(); return yy::parser::make_SPACE(YYText(), loc);}
[ \t\v\r]+                          { return yy::parser::make_SPACE(YYText(), loc); }
&("amp"|"lt"|"gt"|"apos"|"quot");   { return yy::parser::make_ENTITY(YYText(), loc); }
<<EOF>>                             { yyterminate(); }
\\\<                                { return yy::parser::make_TEXT("<", loc); }
.                                   { return yy::parser::make_TEXT(YYText(), loc); }

%%

int yyFlexLexer::yylex(){
    return -1;
}