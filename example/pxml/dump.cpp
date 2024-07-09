
#include <iostream>
#include <filesystem>
#include <fstream>

#include <PxmlLexer.hpp>
#include <PxmlParser.hpp>
#include <Util.hpp>

using namespace ParsePxml;

std::ostream& operator<< (std::ostream& os, PXML::Pxml pxml){
    os << "<" << pxml.tag;
    for(auto& attr : pxml){
        os << " " << attr.first;
        std::visit(overloaded {
            [&](std::monostate){},
            [&](bool value){
                os << "=" << (value ? "true" : "false");
            },
            [&](std::string value){
                os << "=\"" << value << "\"";
            },
            [&](double value){
                os << "=" << value;
            }
        }, attr.second.second);
    }
    os << ">";
    for(auto& child : pxml.children){
        std::visit(overloaded {
            [&](PXML::Pxml value){
                os << value;
            },
            [&](std::string value){
                os << value;
            }
        }, child.second);
    }
    os << "</" << pxml.tag << ">";
    return os;
}

int main(int argc, char* argv[]){
    std::filesystem::path input_path(argv[1]);
    std::ifstream fin(input_path);

    ParsePxml::PxmlLexer lexer(input_path, fin);
    ParsePxml::PxmlParser parser(lexer);
    try{
        PXML::Pxml pxml = parser.parse();
        std::ofstream fout("dump.pxml");
        fout << "<!DOCTYPE pxml>" << std::endl;
        fout << pxml;
        fout.close();
    }catch(UnknownToken& e){
        std::cerr << e.pos << " " << e.what() << std::endl;
    }

    fin.close();
    return 0;
}