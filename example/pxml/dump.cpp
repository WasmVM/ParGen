
#include <iostream>
#include <filesystem>
#include <fstream>

#include <PxmlLexer.hpp>
#include <PxmlParser.hpp>
#include <Util.hpp>

using namespace PXML;

int main(int argc, char* argv[]){
    std::filesystem::path input_path(argv[1]);
    std::ifstream fin(input_path);

    PXML::PxmlLexer lexer(input_path, fin);
    PXML::PxmlParser parser(lexer);
    try{
        parser.parse();
    }catch(UnknownToken& e){
        std::cerr << e.what() << std::endl;
    }

    fin.close();
    return 0;
}