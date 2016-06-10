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
		fout << "parts = new TokenType["<< parts.size() <<"];";
		for(int i=0; i<parts.size(); ++i){
			fout << "parts[" << i << "] = " << parts.at(i) << "; ";
		}
		fout << "reduce(param, " << target << ", parts, " << parts.size() << ");" << endl;
	}	
	fin.close();
	fout.close();
	return 0;
}
