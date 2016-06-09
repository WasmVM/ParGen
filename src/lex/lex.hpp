#ifndef LEX_HPP
#define LEX_HPP
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <list>

#include <ansi_color.h>

using namespace std;

typedef enum{INT,CHAR,ID,SEMI,BRAC_ML,BRAC_SL,COMMA,BRAC_LL,
MINUS,OOPS,NUM,BREAK,IF,ELSE,WHILE,PRINT,READ,RET,ASSI,
PLUS,MULT,DIVI,EQUA,NEQU,LSTH,LSEQ,GREA,GREQ,AND,OR,BRAC_MR,BRAC_SR,
BRAC_LR,END,DL,DL_,D,VD,VD_,VDL,PDLT,PDLT_,PD,B,T,SL,S,E,EIT,EAT,E_,ELT,ELT_,UO,BO,PR} TokenType;

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
