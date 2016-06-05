#ifndef LEX_HPP
#define LEX_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <list>

#include "ansi_color.h"

using namespace std;

typedef enum{KEYW,ARIT,COMP,SPEC,CHAR,IDEN,DIGI} TokenType;

class Token{
public:
	TokenType type;
	string value;
};

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
