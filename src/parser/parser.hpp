#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <list>

#include <lex.hpp>
#include <parserFunc.hpp>

using namespace std;

class Parser{
public:
	Parser(list<Token *> *tokens);
	void parse();
	bool isAccept;
private:
	ParserParam param;
};

#endif
