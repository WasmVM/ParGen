
#include <iostream>
#include <filesystem>
#include <fstream>
#include <variant>

#include <PxmlLexer.hpp>
#include <Util.hpp>

using namespace PXML;

std::ostream& operator<<(std::ostream& os, Token& token){
    std::visit(overloaded {
        [&](std::monostate& tok){
            os << "EOF";
        },
        [&](Tokens::Doctype& tok){
            os << "DOCTYPE";
        },
        [&](Tokens::Equal& tok){
            os << "=";
        },
        [&](Tokens::Close& tok){
            os << "Close (>)";
        },
        [&](Tokens::Inline& tok){
            os << "Inline (/>)";
        },
        [&](Tokens::Bool& tok){
            os << "Bool : " << (tok.value ? "true" : "false");
        },
        [&](Tokens::Number& tok){
            os << "Number : " << tok.value;
        },
        [&](Tokens::Tag& tok){
            os << "Tag : " << tok.value;
        },
        [&](Tokens::Tail& tok){
            os << "Tail : " << tok.value;
        },
        [&](Tokens::String& tok){
            os << "String : " << tok.value;
        },
        [&](Tokens::Text& tok){
            os << "Text : " << tok.value;
        },
        [&](Tokens::ID& tok){
            os << "ID : " << tok.value;
        },
        [&](Tokens::Entity& tok){
            os << "Entity : " << tok.value;
        },
        [&](Tokens::Space& tok){
            os << "Space (" << tok.value.size() << ")";
        }
    }, token);
    return os;
}

int main(int argc, char* argv[]){
    std::filesystem::path input_path(argv[1]);
    std::ifstream fin(input_path);
    PXML::PxmlLexer lexer(input_path, fin);

    try{
        for(Token token = lexer.get(); !std::holds_alternative<std::monostate>(token); token = lexer.get()){
            std::cout << token << std::endl;
        }
    }catch(UnknownToken& e){
        std::cerr << e.what() << std::endl;
    }

    fin.close();
    return 0;
}