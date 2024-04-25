%{

%}

%option noyywrap c++
%option outfile="pxml_parser.cpp"

%x Tag TagName String StrEscape

%%

\<!(?i:DOCTYPE).*\>             { std::cout << "DOCTYPE"; }

<TagName>\/[[:alpha:]][[:alnum:]]*[ \t\v\r\n]*\>    { std::cout << "Tail " << YYText() << std::endl; BEGIN(INITIAL);}
<TagName>[[:alpha:]][[:alnum:]]*                    { std::cout << "Tag " << YYText() << std::endl; BEGIN(Tag);}

<Tag>[ \t\v\r\n]                {}
<Tag>\/?\>                      { BEGIN(INITIAL); }
<Tag>\"                         { yymore(); BEGIN(String); }
<Tag>=                          {}

<Tag>((true)|(false))           { std::cout << "Bool " << YYText() << std::endl; }
<Tag>[[:alpha:]][[:alnum:]]*    { std::cout << "Attribute " << YYText() << std::endl; }
<Tag>[0-9\-]+(\.[0-9]*)?([eE][+\-]?[0-9]+)?  { std::cout << "Number " << YYText() << std::endl; }

<String>\\                      { yymore(); BEGIN(StrEscape); }
<String>\"                      { std::cout << "String " << YYText() << std::endl; BEGIN(Tag); }
<String>.                       { yymore(); }
<StrEscape>.                    { yymore(); BEGIN(String); }

\<                              { std::cout << "Text " << YYText() << std::endl; BEGIN(TagName);}
.                               { yymore(); }

%%
