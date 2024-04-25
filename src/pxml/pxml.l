%{

%}

%option noyywrap c++
%option outfile="pxml_parser.cpp"

%%
\<!(?i:DOCTYPE).*\>  { std::cout << "DOCTYPE"; }
%%
