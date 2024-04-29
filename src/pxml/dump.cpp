// Copyright 2024 Luis Hsu
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     https://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <fstream>
#include <variant>
#include <exception.hpp>
#include <Util.hpp>
#include <Pxml.hpp>

using namespace PXML;

struct indent {
    static size_t level;
    indent& operator++() {
        level += 1;
        return *this;
    }
    indent& operator--() {
        if(level > 0){
            level -= 1;
        }
        return *this;
    }
};
size_t indent::level = 0;

std::ostream& operator<< (std::ostream& os, indent in) {
    return os << std::string(2 * in.level, ' ');
}

std::ostream& operator<< (std::ostream& os, Pxml& pxml){
    os << "<" << pxml.tag;
    for(auto attribute : pxml){
        os << " " << attribute.first;
        std::visit(overloaded {
            [&](bool& value){
                os << "=" << (value ? "true" : "false");
            },
            [&](std::string& value){
                os << "=" << value;
            },
            [&](double& value){
                os << "=" << value;
            },
            [](auto&){}
        }, attribute.second);
    }
    if(pxml.children.empty()){
        return os << " />";
    }
    os << ">";
    ++indent();
    for(Pxml::Child child : pxml.children){
        std::visit(overloaded {
            [&](auto& value){
                os << value;
            }
        }, child);
    }
    --indent();
    return os << "</" << pxml.tag << ">";
}

int main(int argc, char* argv[]){

    if(argc < 2){
        std::cerr << "error: no input file" << std::endl;
        return -1;
    }

    try {
        PXML::Parser parser;
        parser.parse(argv[1]);

        std::cout << parser.pxml << std::endl;
    }catch(Exception::Exception ex){
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}