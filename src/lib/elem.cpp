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
#include <fstream>
#include <regex>
#include <utility>
#include <exception.hpp>
#include <Util.hpp>
#include <pxml_parser.hpp>
#include "Lex.hpp"

using namespace Pargen;

void elem_include(PXML::Pxml& parent, PXML::Pxml& pxml, std::list<std::filesystem::path>& includes, std::list<PXML::Pxml::Child>::iterator& pxml_pos){
    // attributes
    std::filesystem::path resolved_src;
    for(auto attribute : pxml){
        if(attribute.first == "src"){
            // Resolve src
            std::filesystem::path src = std::get<std::string>(attribute.second.second);
            for(std::filesystem::path& include_path : includes){
                if(std::filesystem::exists(include_path / src)){
                    resolved_src = include_path / src;
                    break;
                }
            }
            if(resolved_src.empty()){
                throw Exception::SyntaxError("source '" + src.string() + "' not exist", attribute.second.first);
            }
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <include>", attribute.second.first);
        }
    }

    // Parse pxml file & insert into parent
    PXML::Pxml included;
    {
        std::ifstream stream(resolved_src);
        Lex lex(resolved_src, stream);
        yy::parser parser(lex, included);
        parser();
        stream.close();
    }

    for(auto& attribute : included){
        parent[attribute.first] = attribute.second;
    }
    parent.children.insert(std::next(pxml_pos), included.children.begin(), included.children.end());
}

// (insert_top, content)
std::pair<bool, std::string> elem_header(PXML::Pxml& pxml){
    // attributes
    bool insert_top = true;
    int indent = -1;
    for(auto attribute : pxml){
        if(attribute.first == "position"){
            std::string position = std::get<std::string>(attribute.second.second);
            if(position == "top"){
                insert_top = true;
            }else if(position == "bottom"){
                insert_top = false;
            }else{
                throw Exception::SyntaxError("invalid position in <header>", attribute.second.first);
            }
        }else if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <header>", attribute.second.first);
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child.second)){
            throw Exception::SyntaxError("only texts are allowed in <header>", child.first);
        }
        content += std::get<std::string>(child.second);
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
            std::string position = std::get<std::string>(attribute.second.second);
            if(position == "top"){
                insert_top = true;
            }else if(position == "bottom"){
                insert_top = false;
            }else{
                throw Exception::SyntaxError("invalid position in <source>", attribute.second.first);
            }
        }else if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <source>", attribute.second.first);
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child.second)){
            throw Exception::SyntaxError("only texts are allowed in <source>", child.first);
        }
        content += std::get<std::string>(child.second);
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
            indent = std::get<double>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <function>", attribute.second.first);
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child.second)){
            throw Exception::Exception("only texts are allowed in <function>");
        }
        content += std::get<std::string>(child.second);
    }
    return handle_indent(indent, content);
}

std::string elem_member(PXML::Pxml& pxml){
    // attributes
    int indent = 4;
    for(auto attribute : pxml){
        if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <member>", attribute.second.first);
        }
    }
    // Content
    std::string content;
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child.second)){
            throw Exception::SyntaxError("only texts are allowed in <member>", child.first);
        }
        content += std::get<std::string>(child.second);
    }
    // Fix indent
    return handle_indent(indent, content);
}

std::string elem_type(PXML::Pxml& pxml){
    std::string type_str;
    // attributes
    for(auto attribute : pxml){
        throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <type>", attribute.second.first);
    }
    // children
    for(PXML::Pxml::Child& child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child.second)){
            throw Exception::SyntaxError("invalid element under <type>", child.first);
        }else{
            type_str += std::get<std::string>(child.second);
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
            token.name = std::get<std::string>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <token>", attribute.second.first);
        }
    }
    // children
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(child_it->second)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(child_it->second);
            if(child_pxml.tag == "include"){
                elem_include(pxml, child_pxml, pargen.includes, child_it);
            }else if(child_pxml.tag == "type"){
                token.types.emplace_back(elem_type(child_pxml));
            }else if(child_pxml.tag == "member"){
                token.members.emplace_back(elem_member(child_pxml));
            }else if(child_pxml.tag == "function"){
                token.functions.emplace_back(elem_function(child_pxml));
            }else{
                throw Exception::SyntaxError("invalid element under <token>", child_pxml.pos);
            }
        }
    }
    return token;
}

Rule elem_rule(ParGen& pargen, PXML::Pxml& pxml){
    Rule rule;
    // attributes
    int indent = 4;
    for(auto attribute : pxml){
        if(attribute.first == "id"){
            rule.id = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "pattern"){
            rule.pattern = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "push"){
            rule.push = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "indent"){
            indent = std::get<double>(attribute.second.second);
        }else if(attribute.first == "pop"){
            if(std::holds_alternative<std::monostate>(attribute.second.second)){
                rule.pop = true;
            }else{
                rule.pop = std::get<bool>(attribute.second.second);
            }
            rule.pop = true;
        }else if(attribute.first == "more"){
            if(std::holds_alternative<std::monostate>(attribute.second.second)){
                rule.more = true;
            }else{
                rule.more = std::get<bool>(attribute.second.second);
            }
            rule.more = true;
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <rule>", attribute.second.first);
        }
    }
    // Content
    for(PXML::Pxml::Child child : pxml.children){
        if(std::holds_alternative<PXML::Pxml>(child.second)){
            throw Exception::SyntaxError("only texts are allowed in <rule>", child.first);
        }
        rule.content += std::get<std::string>(child.second);
    }
    rule.content = handle_indent(indent, rule.content);
    return rule;
}

Use elem_use(PXML::Pxml& pxml){
    Use use;
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "id"){
            use.id = std::get<std::string>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <use>", attribute.second.first);
        }
    }
    // Content
    if(!pxml.children.empty()){
        throw Exception::SyntaxError("<use> should no have children", pxml.pos);
    }
    return use;
}

Group elem_group(ParGen& pargen, PXML::Pxml& pxml){
    Group group;
    // attributes
    int indent = 4;
    for(auto attribute : pxml){
        if(attribute.first == "name"){
            group.name = std::get<std::string>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <group>", attribute.second.first);
        }
    }
    // Content
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(child_it->second)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(child_it->second);
            if(child_pxml.tag == "include"){
                elem_include(pxml, child_pxml, pargen.includes, child_it);
            }else if(child_pxml.tag == "rule"){
                group.emplace_back(elem_rule(pargen, child_pxml));
            }else if(child_pxml.tag == "group"){
                group.emplace_back(elem_group(pargen, child_pxml));
            }else if(child_pxml.tag == "use"){
                group.emplace_back(elem_use(child_pxml));
            }else{
                throw Exception::SyntaxError("invalid element under <lexer>", child_pxml.pos);
            }
        }
    }
    return group;
}

void elem_tokens(ParGen& pargen, Tokens& tokens, PXML::Pxml& pxml){
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "class"){
            tokens.class_name = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "namespace"){
            tokens.name_space = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "headerFile"){
            tokens.header_path = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "sourceFile"){
            tokens.source_path = std::get<std::string>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <tokens>", attribute.second.first);
        }
    }
    // children
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(child_it->second)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(child_it->second);
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
                throw Exception::SyntaxError("invalid element under <tokens>", child_pxml.pos);
            }
        }
    }
}

void elem_lexer(ParGen& pargen, Lexer& lexer, PXML::Pxml& pxml){
    // attributes
    for(auto attribute : pxml){
        if(attribute.first == "class"){
            lexer.class_name = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "newLine"){
            lexer.new_line = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "headerFile"){
            lexer.header_path = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "sourceFile"){
            lexer.source_path = std::get<std::string>(attribute.second.second);
        }else if(attribute.first == "return"){
            lexer.return_type = std::get<std::string>(attribute.second.second);
        }else{
            throw Exception::SyntaxError("unknown attribute '" + attribute.first + "' in <lexer>", attribute.second.first);
        }
    }
    // children
    for(auto child_it = pxml.children.begin(); child_it != pxml.children.end(); ++child_it){
        if(std::holds_alternative<PXML::Pxml>(child_it->second)){
            PXML::Pxml& child_pxml = std::get<PXML::Pxml>(child_it->second);
            if(child_pxml.tag == "include"){
                elem_include(pxml, child_pxml, pargen.includes, child_it);
            }else if(child_pxml.tag == "header"){
                auto header_pair = elem_header(child_pxml);
                if(header_pair.first){
                    lexer.header_prologue += header_pair.second;
                }else{
                    lexer.header_epilogue += header_pair.second;
                }
            }else if(child_pxml.tag == "member"){
                lexer.members.emplace_back(elem_member(child_pxml));
            }else if(child_pxml.tag == "source"){
                auto source_pair = elem_source(child_pxml);
                if(source_pair.first){
                    lexer.source_prologue += source_pair.second;
                }else{
                    lexer.source_epilogue += source_pair.second;
                }
            }else if(child_pxml.tag == "function"){
                lexer.functions.emplace_back(elem_function(child_pxml));
            }else if(child_pxml.tag == "rule"){
                lexer.emplace_back(elem_rule(pargen, child_pxml));
            }else if(child_pxml.tag == "group"){
                lexer.emplace_back(elem_group(pargen, child_pxml));
            }else{
                throw Exception::SyntaxError("invalid element under <lexer>", child_pxml.pos);
            }
        }
    }
}