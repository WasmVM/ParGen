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

#include <exception.hpp>

using namespace Pargen;

ParGen::ParGen(std::filesystem::path pxml_path){
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
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<std::string>(child)){
            throw Exception::Exception("children of root <pxml> should be element");
        }
        PXML::Pxml& child_pxml = std::get<PXML::Pxml>(child);
        if(child_pxml.tag == "include"){
            
        }else{
            throw Exception::Exception("invalid element under <pxml>");
        }
    }

}