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
#include <regex>
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

void elem_header(std::string& prologue, std::string& epilogue, PXML::Pxml& pxml){
    // attributes
    bool insert_top = true;
    int indent = -1;
    for(auto attribute : pxml){
        if(attribute.first == "position"){
            std::string position = std::get<std::string>(attribute.second);
            if(position == "top"){
                insert_top = true;
            }else if(position == "bottom"){
                insert_top = false;
            }else{
                throw Exception::Exception("invalid position in <header>");
            }
        }else if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second);
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <header>");
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child)){
            throw Exception::Exception("only texts are allowed in <header>");
        }
        content += std::get<std::string>(child);
    }
    // Fix indent
    if(indent >= 0){
        // measure indent
        size_t space_pos = content.find_first_not_of(" \t\n\r\v");
        std::string spaces = content.substr(0, space_pos);
        content = std::regex_replace(content, std::regex(spaces), "\n" + std::string(indent, ' '));
    }
    // Insert
    if(insert_top){
        prologue += content;
    }else{
        epilogue += content;
    }
}

void elem_tokens(ParGen& pargen, PXML::Pxml& pxml){
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "class"){
            pargen.tokens.class_name = std::get<std::string>(attribute.second);
        }else if(attribute.first == "namespace"){
            pargen.tokens.name_space = std::get<std::string>(attribute.second);
        }else if(attribute.first == "headerFile"){
            pargen.tokens.header_path = std::get<std::string>(attribute.second);
        }
        else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <tokens>");
        }
    }
    // children
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(*child_it)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(*child_it);
            if(child_pxml.tag == "include"){
                elem_include(pxml, child_pxml, pargen.includes, child_it);
            }else if(child_pxml.tag == "header"){
                elem_header(pargen.tokens.prologue, pargen.tokens.epilogue, child_pxml);
            }else if(child_pxml.tag == "token"){
                // TODO:
            }else if(child_pxml.tag == "member"){
                // TODO:
            }else if(child_pxml.tag == "source"){
                // TODO:
            }else{
                throw Exception::Exception("invalid element under <tokens>");
            }
        }
    }
}