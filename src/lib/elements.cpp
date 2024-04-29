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

#include <filesystem>
#include <exception.hpp>

using namespace Pargen;

void elem_include(PXML::Pxml& parent, PXML::Pxml& pxml, std::list<std::filesystem::path>& includes, std::list<PXML::Pxml::Child>::iterator& pxml_pos){
    // attributes
    std::filesystem::path resolved_src;
    for(auto attribute : pxml){
        if(attribute.first == "src"){
            // Resolve src
            std::filesystem::path src = std::get<std::string>(attribute.second);
            for(std::filesystem::path& include_path : includes){
                if(std::filesystem::exists(include_path / src)){
                    resolved_src = include_path / src;
                    break;
                }
            }
            if(resolved_src.empty()){
                throw Exception::Exception("source '" + src.string() + "' not exist");
            }
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <include>");
        }
    }
    // Parse pxml file & insert into parent
    PXML::Parser pxml_parser;
    pxml_parser.parse(resolved_src);
    for(auto& attribute : pxml_parser.pxml){
        parent[attribute.first] = attribute.second;
    }
    parent.children.insert(std::next(pxml_pos), pxml_parser.pxml.children.begin(), pxml_parser.pxml.children.end());
}