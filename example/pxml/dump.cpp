
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>

#include <PxmlLexer.hpp>
#include <PxmlParser.hpp>
#include <Util.hpp>
#include <exception.hpp>

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
                os << std::regex_replace(value, std::regex("<"), "\\<");
            }
        }, child.second);
    }
    os << "</" << pxml.tag << ">";
    return os;
}

int main(int argc, char* argv[]){
    std::filesystem::path input_path(argv[1]);
    std::ifstream fin(input_path);

    std::string output_path = "dump.pxml";
    if(argc == 3){
        output_path = argv[2];
    }

    ParsePxml::PxmlLexer lexer(input_path, fin);
    ParsePxml::PxmlParser parser(lexer);
    try{
        PXML::Pxml pxml = parser.parse();
        std::ofstream fout(output_path);
        fout << "<!DOCTYPE pxml>" << std::endl;
        fout << pxml;
        fout.close();
    }catch(UnknownToken& e){
        std::cerr << e.pos << " " << e.what() << std::endl;
    }catch(ParsePxml::ParseError& e){
        std::cerr << e.pos << " " <<  e.what() << std::endl;
    }catch(Exception::Exception& e){
        std::cerr << e.what() << std::endl;
    }

    fin.close();
    return 0;
}