#include <iostream>
#include <fstream>

#include <ansi_color.h>
#include <lex.hpp>

using namespace std;

int main(int argc, char **argv)
{
	argc--;
	if(argc < 1){
		cerr << ANSI_RED << "錯誤：" << ANSI_RESET "沒有輸入檔案"  << endl;
		return 1;
	}
	for(int i=0; i<argc; ++i){
		// Open input file
		ifstream fin(argv[i+1]);
		Lexer lexer(fin,argv[i+1]);
		lexer.lex();
		if(lexer.isError){
			cout << lexer.errorString;
			fin.close();
			delete lexer.tokens;
			return 1;
		}
		cout << ANSI_CYAN << "** File " << argv[i+1] << " **" << ANSI_RESET << endl;
		while(!lexer.tokens->empty()){
			Token *tok = lexer.tokens->front();
			cout << tok->type;
			cout << " : " << tok->value << endl;
			delete tok;
			lexer.tokens->pop_front();
		}
		// Close file
		fin.close();
		delete lexer.tokens;
	}
	
	
	return 0;
}

