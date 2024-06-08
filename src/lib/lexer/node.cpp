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
#include <Util.hpp>
#include <exception.hpp>

#include "lexer.hpp"

#include <stack>

using namespace Pargen;

static CharNode::Char escape_sequence(std::string::iterator& it, const std::string::iterator& end){
    char ch = *(++it);
    switch(ch){
        case 'x':
            if(it != end && std::next(it) != end){
                std::string hex;
                hex += *(++it); 
                hex += *(++it);
                if(std::isxdigit(hex[0]) && std::isxdigit(hex[1])){
                    return std::stoi(hex, nullptr, 16);
                }else{
                    throw Exception::Exception("expected 2 hex digits for hex escape in pattern");
                }
            }else{
                throw Exception::Exception("too few characters for hex escape in pattern");
            }
        break;
        case 't':
            return '\t';
        break;
        case 'r':
            return '\r';
        break;
        case 'v':
            return '\v';
        break;
        case 'f':
            return '\f';
        break;
        case 'n':
            return '\n';
        break;
        case 'd':
            return CharNode::Char(CharNode::Char::Number);
        break;
        case 'D':
            return !CharNode::Char(CharNode::Char::Number);
        break;
        case 's':
            return CharNode::Char(CharNode::Char::Space);
        break;
        case 'S':
            return !CharNode::Char(CharNode::Char::Space);
        break;
        case 'w':
            return CharNode::Char(CharNode::Char::Alphabet) + CharNode::Char(CharNode::Char::Number);
        break;
        case 'W':
            return !(CharNode::Char(CharNode::Char::Alphabet) + CharNode::Char(CharNode::Char::Number));
        break;
        case 'a':
            return CharNode::Char(CharNode::Char::Alphabet);
        break;
        case 'A':
            return !CharNode::Char(CharNode::Char::Alphabet);
        break;
        default:
            return ch;
    }
}

CharNode::Char::Char(const Class cl){
    switch(cl){
        case Number:
            insert({'0','1','2','3','4','5','6','7','8','9'});
        break;
        case Alphabet:
            insert({
                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
            });
        break;
        case Space:
            insert({' ', '\t', '\r', '\v', '\f', '\n'});
        break;
    }
}

std::ostream& operator<< (std::ostream& os, CharNode::Char& character){
    if(character.negate){
        os << "not ";
    }
    if(character.is_any()){
        return os << "any";
    }
    std::string characters(character.begin(), character.end());
    std::stable_sort(characters.begin(), characters.end());
    for(char ch : characters){
        if(std::isspace(ch)){
            switch(ch){
                case ' ':
                    os << "'" << ch << "'";
                break;
                case '\t':
                    os << "\\\\t";
                break;
                case '\r':
                    os << "\\\\r";
                break;
                case '\f':
                    os << "\\\\f";
                break;
                case '\v':
                    os << "\\\\v";
                break;
                case '\n':
                    os << "\\\\n";
                break;
            }
        }else if(ch == '\"'){
            os << "'\\\"'";
        }else if(ch == '\\'){
            os << "'\\\\'";
        }else{
            os << "'" << ch << "'";
        }
    }
    return os;
}

Node* parse_pattern(std::string& pattern){
    std::stack<GroupNode*> groups;
    Node* root = nullptr;
    Node* current = nullptr;
    Node** next = &root;
    size_t level = 0;
    for(auto it = pattern.begin(); it != pattern.end(); ++it){
        switch(*it){
            case '[':{
                CharNode::Char value;
                bool negate = false;
                if(it != pattern.end()){
                    if(*(std::next(it)) == '^'){
                        negate = true;
                        ++it;
                    }
                    ++it;
                }
                std::optional<char> last = std::nullopt;
                for(;(it != pattern.end()) && (*it != ']');++it){
                    if(*it == '\\'){
                        if(std::next(it) == pattern.end()){
                            throw Exception::Exception("expected character after '\\' in pattern");
                        }else{
                            CharNode::Char escaped = escape_sequence(it, pattern.end());
                            value += escaped;
                            if(!escaped.negate && escaped.size() == 1){
                                last = *escaped.begin();
                            }else{
                                last.reset();
                            }
                        }
                    }else if(*it == '-'){
                        if(++it == pattern.end()){
                            throw Exception::Exception("expected character after '-' in pattern");
                        }else if(value.empty()){
                            throw Exception::Exception("expected character before '-' in pattern");
                        }else if(!last.has_value()){
                            throw Exception::Exception("invalid character before '-' in pattern");
                        }else{
                            for(char ch = (last.value() + 1); ch <= *it; ++ch){
                                value += ch;
                            }
                        }
                    }else{
                        value += *it;
                        last = *it;
                    }
                    
                }
                if(negate){
                    value = !value;
                }
                if(!value.negate && value.empty()){
                    throw Exception::Exception("empty [] in pattern");
                }
                CharNode* node = new CharNode;
                node->value = value;
                current = node;
                *next = node;
                next = &(node->next);
            }break;
            case '\\':{
                if(it != pattern.end()){
                    CharNode* node = new CharNode;
                    node->value = escape_sequence(it, pattern.end());
                    current = node;
                    *next = node;
                    next = &(node->next);
                }else{
                    throw Exception::Exception("expected a character after '\\' in pattern");
                }
            }break;
            case '{':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '{'");
                }
                std::string str = "";
                while(std::isdigit(*(++it))){
                    str += *it;
                }
                if(str.empty()){
                    throw Exception::Exception("invalid '{' qualifier");
                }
                current->min = std::stoi(str);
                if(*it == ','){
                    str = "0";
                    while(std::isdigit(*(++it))){
                        str += *it;
                    }
                    if(str.empty()){
                        throw Exception::Exception("invalid '{' qualifier");
                    }
                    current->max = std::stoi(str);
                }else{
                    current->max = current->min;
                }
                if(*it != '}'){
                    throw Exception::Exception("'{' is not close with '}' in pattern {min,max} qualifier");
                }
                if(current->max != 0 && (current->min > current->max)){
                    throw Exception::Exception("min can't be greater than max in pattern {min,max} qualifier");
                }
            }break;
            case '}':{
                throw Exception::Exception("'}' without previous '{'");
            }break;
            case '+':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '+'");
                }
                current->min = 1;
                current->max = 0;
            }break;
            case '*':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '*'");
                }
                current->min = 0;
                current->max = 0;
            }break;
            case '?':{
                if(current == nullptr){
                    throw Exception::Exception("pattern or group can't begin with '?'");
                }
                current->min = 0;
                current->max = 1;
            }break;
            case '(':{
                GroupNode* node = new GroupNode;
                *next = node;
                groups.push(node);
                node->children.emplace_back(nullptr);
                current = nullptr;
                next = &(node->children.back());
                level += 1;
            }break;
            case ')':{
                if(level == 0){
                    throw Exception::Exception("')' without previous '('");
                }
                current = groups.top();
                next = &(groups.top()->next);
                groups.pop();
                level -= 1;
            }break;
            case '|':{
                if(groups.empty()){
                    if(current == nullptr){
                        throw Exception::Exception("pattern or group can't begin with '|'");
                    }
                    GroupNode* node = new GroupNode;
                    node->children.emplace_back(root);
                    root = node;
                    groups.push(node);
                }
                groups.top()->children.emplace_back(nullptr);
                current = nullptr;
                next = &(groups.top()->children.back());
            }break;
            case '.':{
                CharNode* node = new CharNode;
                node->value += '\0';
                current = node;
                *next = node;
                next = &(node->next);
            }break;
            default:{
                CharNode* node = new CharNode;
                node->value += *it;
                current = node;
                *next = node;
                next = &(node->next);
            }break;
        }
    }
    if(root == nullptr){
        throw Exception::Exception("empty pattern");
    }
    return root;
}
