#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
	argc--;
	if(argc < 1){
		cout << "沒有輸入檔案" << endl;
		return 1;
	}
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	int r = 1;
	while(!fin.eof()){
		string line;
		getline(fin,line);
		stringstream ss(line);
		vector<string> parts;
		string target, arrow;
		ss >> target;
		ss >> arrow;
		while(!ss.eof()){
			string part;
			ss >> part;
			parts.push_back(part);
		}
		fout << "bool rule" << r << "(ParserParam &param){\n\tTokenType *parts = new TokenType["<< parts.size() <<"];" << endl;
		for(int i=0; i<parts.size(); ++i){
			fout << "\tparts[" << i << "] = " << parts.at(i) << ";" << endl;
		}
		fout << "\treturn reduce(param, " << target << ", parts, " << parts.size() << ");\n}" << endl;
		r++;
	}	
	fin.close();
	fout.close();
	return 0;
}
