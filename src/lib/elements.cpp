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
#include <utility>
#include <exception.hpp>
#include <Util.hpp>

using namespace Pargen;

static std::string handle_indent(int indent, std::string content){
    if(indent >= 0){
        // measure indent
        size_t space_pos = content.find_first_not_of(" \t\n\r\v");
        if(space_pos != 0){
            std::string spaces = content.substr(0, space_pos);
            content = std::regex_replace(content, std::regex(spaces), "\n" + std::string(indent, ' '));
        }else{
            content = "\n" + std::string(indent, ' ') + content;
        }
        content = content.substr(0, content.find_last_not_of(" \t\n\r\v") + 1);
    }
    return content;
}

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

// (insert_top, content)
std::pair<bool, std::string> elem_header(PXML::Pxml& pxml){
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
    return {insert_top, content};
}

// (insert_top, content)
std::pair<bool, std::string> elem_source(PXML::Pxml& pxml){
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
                throw Exception::Exception("invalid position in <source>");
            }
        }else if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second);
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <source>");
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child)){
            throw Exception::Exception("only texts are allowed in <source>");
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
    return {insert_top, content};
}

std::string elem_function(PXML::Pxml& pxml){
    // attributes
    int indent = 4;
    for(auto attribute : pxml){
        if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second);
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <function>");
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child)){
            throw Exception::Exception("only texts are allowed in <function>");
        }
        content += std::get<std::string>(child);
    }
    return handle_indent(indent, content);
}

std::string elem_member(PXML::Pxml& pxml){
    // attributes
    int indent = 4;
    for(auto attribute : pxml){
        if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second);
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <member>");
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child)){
            throw Exception::Exception("only texts are allowed in <member>");
        }
        content += std::get<std::string>(child);
    }
    // Fix indent
    return handle_indent(indent, content);
}

std::string elem_type(PXML::Pxml& pxml){
    std::string type_str;
    // attributes
    for(auto attribute : pxml){
        throw Exception::Exception("unknown attribute '" + attribute.first + "' in <type>");
    }
    // children
    for(PXML::Pxml::Child& child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child)){
            throw Exception::Exception("invalid element under <type>");
        }else{
            type_str += std::get<std::string>(child);
        }
    }
    // Trim spaces
    type_str = std::regex_replace(type_str, std::regex("\\s+"), " ");
    return strip(type_str);
}

Token elem_token(ParGen& pargen, PXML::Pxml& pxml){
    Token token;
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "name"){
            token.name = std::get<std::string>(attribute.second);
        }else{
            throw Exception::Exception("unknown attribute '" + attribute.first + "' in <token>");
        }
    }
    // children
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(*child_it)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(*child_it);
            if(child_pxml.tag == "include"){
                elem_include(pxml, child_pxml, pargen.includes, child_it);
            }else if(child_pxml.tag == "type"){
                token.types.emplace_back(elem_type(child_pxml));
            }else if(child_pxml.tag == "member"){
                token.members.emplace_back(elem_member(child_pxml));
            }else if(child_pxml.tag == "function"){
                token.functions.emplace_back(elem_function(child_pxml));
            }else{
                throw Exception::Exception("invalid element under <token>");
            }
        }
    }
    return token;
}

void elem_tokens(ParGen& pargen, Tokens& tokens, PXML::Pxml& pxml){
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "class"){
            tokens.class_name = std::get<std::string>(attribute.second);
        }else if(attribute.first == "namespace"){
            tokens.name_space = std::get<std::string>(attribute.second);
        }else if(attribute.first == "headerFile"){
            tokens.header_path = std::get<std::string>(attribute.second);
        }else if(attribute.first == "sourceFile"){
            tokens.source_path = std::get<std::string>(attribute.second);
        }else{
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
                auto header_pair = elem_header(child_pxml);
                if(header_pair.first){
                    tokens.header_prologue += header_pair.second;
                }else{
                    tokens.header_epilogue += header_pair.second;
                }
            }else if(child_pxml.tag == "token"){
                tokens.emplace_back(elem_token(pargen, child_pxml));
            }else if(child_pxml.tag == "member"){
                tokens.members.emplace_back(elem_member(child_pxml));
            }else if(child_pxml.tag == "source"){
                auto source_pair = elem_source(child_pxml);
                if(source_pair.first){
                    tokens.source_prologue += source_pair.second;
                }else{
                    tokens.source_epilogue += source_pair.second;
                }
            }else if(child_pxml.tag == "function"){
                tokens.functions.emplace_back(elem_function(child_pxml));
            }else{
                throw Exception::Exception("invalid element under <tokens>");
            }
        }
    }
}