#ifndef LEX_HPP
#define LEX_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>

#include "ansi_color.h"

using namespace std;

typedef enum{KEY,ARITH,COMP,SPEC,CHAR,COMM} TokenType;

class Token{
public:
	TokenType type;
	string value;
};

class Lexer{
public:
	Lexer(ifstream &fin);
	list<Token *> *lex();
private:
	ifstream &fin;
};
#endif
