#include "lex.hpp"

Lexer::Lexer(ifstream &fin):
	fin(fin)
{
	
}

list<Token *> *Lexer::lex(){
	list<Token *> *tokens = new list<Token *>;
	while(!fin.eof()){
		// Read line
		string line;
		getline(fin,line);
		// Trim both ends
		line = regex_replace(line,regex("^\\s|\\s$",regex::ECMAScript),"");
		// Search token by regex
		smatch strmat;
		// Keyword
		if(regex_search(line,strmat,regex("[^\\w](int|char|return|if|else|while|break|print|read)[^\\w]",regex::ECMAScript))){
			Token *newTok = new Token;
			regex_replace(strmat.str(0),regex("^\\s|\\s$",regex::ECMAScript),"") << endl;
		}
	}	
	return tokens;
}
