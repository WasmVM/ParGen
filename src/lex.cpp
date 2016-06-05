#include "lex.hpp"

Lexer::Lexer(ifstream &fin, char *filename):
	tokens(NULL),fin(fin),filename(filename)
{
	
}

void Lexer::lex(){
	// Preset
	isError = false;
	if(!tokens){
		tokens = new list<Token *>;
	}
	errorString = "";
	// Load
	int lineNum = 0;
	while(!fin.eof()){
		// Read line
		string line;
		getline(fin,line);
		++lineNum;
		// Search token by regex
		smatch strmat;
		bool isMatch = false;
		do{
			isMatch = false;
			// Trim both ends
			line = regex_replace(line,regex("^\\s*|\\s*$",regex::ECMAScript),"");
			// Comment
			if(regex_search(line,strmat,regex("\\/\\/.*",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					break;
				}
			}
			// Char
			if(regex_search(line,strmat,regex("\\\".\\\"",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = CHAR;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Identifier
			if(regex_search(line,strmat,regex("(id[A-Z][a-z0-9]*)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = IDEN;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Digit
			if(regex_search(line,strmat,regex("[0-9]+",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = DIGI;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Keyword
			if(regex_search(line,strmat,regex("[^\\w]*(int|char|return|if|else|while|break|print|read)[^\\w]",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = KEYW;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Comparison
			if(regex_search(line,strmat,regex("(==|!=|<=|>=|<|>|&&|\\|\\|)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = COMP;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Arithmetic
			if(regex_search(line,strmat,regex("(=|!|\\+|\\-|\\*|\\/)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = ARIT;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Special
			if(regex_search(line,strmat,regex("(\\[|\\]|\\(|\\)|\\{|\\}|;|,)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->type = SPEC;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				};
			}
			// Error
			if(!isMatch){
				line = regex_replace(line,regex("^\\s*|\\s*$",regex::ECMAScript),"");
				if(line.size() > 0){
					isError = true;
					stringstream ss(errorString);
					ss << ANSI_WHITE << filename << ':' << lineNum << ":" ANSI_RED " 錯誤：未定義的符號 " ANSI_WHITE "'" << line << '\'' << ANSI_RESET << endl; 
					errorString = ss.str();
				}
				break;
			}
		}while(1);
	}
}
