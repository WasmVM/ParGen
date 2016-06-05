#include <iostream>
#include <fstream>

#include "ansi_color.h"
#include "lex.hpp"

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
		Lexer lexer(fin);
		lexer.lex();
		// Close file
		fin.close();
	}
	
	
	return 0;
}

