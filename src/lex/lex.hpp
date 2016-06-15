#ifndef LEX_HPP
#define LEX_HPP

#include <general.hpp>

class Lexer{
public:
	Lexer(ifstream &fin, char *filename);
	void lex();
	list<Token *> *tokens;
	bool isError;
	string errorString;
private:
	ifstream &fin;
	char *filename;
};
#endif
