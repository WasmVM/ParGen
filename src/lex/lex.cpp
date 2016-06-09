#include <lex.hpp>

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
					newTok->type = ID;
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
					newTok->type = NUM;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Keyword
			if(regex_search(line,strmat,regex("^(int|char|return|if|else|while|break|print|read)[^\\w]",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");				
					if(newTok->value == "int"){
						newTok->type = INT;
					}else if (newTok->value == "char"){
						newTok->type = CHAR;
					}else if (newTok->value == "return"){
						newTok->type = RET;
					}else if (newTok->value == "if"){
						newTok->type = IF;
					}else if (newTok->value == "else"){
						newTok->type = ELSE;
					}else if (newTok->value == "while"){
						newTok->type = WHILE;
					}else if (newTok->value == "break"){
						newTok->type = BREAK;
					}else if (newTok->value == "read"){
						newTok->type = READ;
					}else{
						newTok->type = PRINT;
					}
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Comparison
			if(regex_search(line,strmat,regex("(==|!=|<=|>=|<|>|&&|\\|\\|)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					if(newTok->value == "=="){
						newTok->type = EQUA;
					}else if (newTok->value == "!="){
						newTok->type = NEQU;
					}else if (newTok->value == "<="){
						newTok->type = LSEQ;
					}else if (newTok->value == ">="){
						newTok->type = GREQ;
					}else if (newTok->value == "<"){
						newTok->type = GREA;
					}else if (newTok->value == ">"){
						newTok->type = LSTH;
					}else if (newTok->value == "&&"){
						newTok->type = AND;
					}else{
						newTok->type = OR;
					}
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Arithmetic
			if(regex_search(line,strmat,regex("(=|!|\\+|\\-|\\*|\\/)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					if(newTok->value == "="){
						newTok->type = ASSI;
					}else if (newTok->value == "!"){
						newTok->type = OOPS;
					}else if (newTok->value == "+"){
						newTok->type = PLUS;
					}else if (newTok->value == "-"){
						newTok->type = MINUS;
					}else if (newTok->value == "*"){
						newTok->type = MULT;
					}else{
						newTok->type = DIVI;
					}
					line = line.substr(strmat.length());
					tokens->push_back(newTok);
				}
			}
			// Special
			if(regex_search(line,strmat,regex("(\\[|\\]|\\(|\\)|\\{|\\}|;|,)",regex::ECMAScript))){
				if(strmat.position() == 0){
					isMatch = true;
					Token *newTok = new Token;
					newTok->value = regex_replace(strmat.str(0),regex("^\\s*|\\s*$",regex::ECMAScript),"");
					if(newTok->value == "("){
						newTok->type = BRAC_SL;
					}else if (newTok->value == "["){
						newTok->type = BRAC_ML;
					}else if (newTok->value == "]"){
						newTok->type = BRAC_MR;
					}else if (newTok->value == ")"){
						newTok->type = BRAC_SR;
					}else if (newTok->value == "{"){
						newTok->type = BRAC_LL;
					}else if (newTok->value == "}"){
						newTok->type = BRAC_LR;
					}else if (newTok->value == ";"){
						newTok->type = SEMI;
					}else{
						newTok->type = COMMA;
					}
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
