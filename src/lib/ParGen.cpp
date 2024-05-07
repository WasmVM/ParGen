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

#include <ParGen.hpp>

#include <iostream>
#include <exception.hpp>

using namespace Pargen;

void elem_include(PXML::Pxml& parent, PXML::Pxml& pxml, std::list<std::filesystem::path>& includes, std::list<PXML::Pxml::Child>::iterator& pxml_pos);
void elem_tokens(ParGen& pargen, Tokens& tokens, PXML::Pxml& pxml);
void elem_lexer(ParGen& pargen, Lexer& lexer, PXML::Pxml& pxml);

void ParGen::load(std::filesystem::path pxml_path){
    // Parse pxml file
    PXML::Parser pxml_parser;
    pxml_parser.parse(pxml_path);
    PXML::Pxml& pxml = pxml_parser.pxml;

    // Parse pxml tree
    if(pxml.tag != "pxml"){
        throw Exception::Exception("the root element should be <pxml>");
    }
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "namespace"){
            name_space = std::get<std::string>(attribute.second);
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in root <pxml>");
        }
    }
    // children
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(*child_it)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(*child_it);
            if(child_pxml.tag == "include"){
                elem_include(pxml, child_pxml, includes, child_it);
            }else if(child_pxml.tag == "tokens"){
                elem_tokens(*this, tokens, child_pxml);
            }else if(child_pxml.tag == "lexer"){
                elem_lexer(*this, lexer, child_pxml);
            }else{
                throw Exception::Exception("invalid element under <pxml>");
            }
        }
    }
}