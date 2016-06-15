#ifndef PARSER_HPP
#define PARSER_HPP

#include <general.hpp>
#include <parserFunc.hpp>

using namespace std;

class Parser{
public:
	Parser(list<Token *> *tokens);
    ~Parser();
	void parse();
    ASTNode *getTree();
private:
	ParserParam param;
};

#endif
