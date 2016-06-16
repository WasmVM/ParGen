#include <iostream>
#include <fstream>
#include <cstring>

#include <ansi_color.h>
#include <lex.hpp>
#include <parser.hpp>
#include <codegen.hpp>

using namespace std;

int main(int argc, char **argv)
{
	argc--;
	if(argc < 1){
		cerr << ANSI_RED << "錯誤：" << ANSI_RESET "沒有輸入檔案"  << endl;
		return 1;
	}
	for(int i=0; i<argc; ++i){
        cout << ANSI_CYAN << "** File " << argv[i+1] << " **" << ANSI_RESET << endl;
		// Open input file
		ifstream fin(argv[i+1]);
        // Lexer
		Lexer lexer(fin,argv[i+1]);
		lexer.lex();
		if(lexer.isError){
			cout << lexer.errorString;
			fin.close();
			delete lexer.tokens;
			return 1;
		}
        // Parser
		Parser parser(lexer.tokens);
		parser.parse();
        // Codegen
        argv[i+1][strlen(argv[i+1])-1] = 's';
        CodeGen codegen;
        codegen.generate(parser.getTree(), argv[i+1]);
		// Close file
		fin.close();
		delete lexer.tokens;
	}
	
	
	return 0;
}

