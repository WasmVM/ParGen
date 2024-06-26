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

#include <Util.hpp>

#include <regex>

std::string strip(std::string str, bool lead, bool trail){
    size_t lead_pos = lead ? str.find_first_not_of(" \t\n\r\v") : 0;
    if(trail){
        size_t trail_pos = str.find_last_not_of(" \t\n\r\v");
        return str.substr(lead_pos, trail_pos - lead_pos + 1);
    }else{
        return str.substr(lead_pos);
    }
}

std::string append_func_name(std::string func, std::string name_space){
    // Trim leading & trailing spaces
    func = strip(func);
    // Decouple function signature
    {
        std::string param;
        for(size_t i = func.size() - 1, level = 0; i > 0; --i){
            if(func[i] == ')'){
                level += 1;
            }else if(func[i] == '('){
                level -= 1;
                if(level == 0){
                    param = func.substr(i, func.find_last_not_of(';') - i + 1);
                    func = strip(func.substr(0, i));
                }
            }
        }
        std::string name = func.substr(func.find_last_of(" \t\n\r\v") + 1);
        func = func.substr(0, func.find_last_of(" \t\n\r\v"));
        if(func.starts_with("template")){
            func = func.substr(8);
            // Get template declaration
            std::string template_args;
            for(size_t i = 0, level = 0; i < func.size(); ++i){
                if(func[i] == '<'){
                    level += 1;
                }else if(func[i] == '>'){
                    level -= 1;
                    if(level == 0){
                        template_args = func.substr(0, i + 1);
                        func = func.substr(i + 1);
                        break;
                    }
                }
            }
            func = strip(func, true, false);
            return "template<> " + func + " " + name_space + "::" + name + template_args + param;
        }else{
            return func + " " + name_space + "::" + name + param;
        }
    }
}

std::string handle_indent(int indent, std::string content){
    if(indent >= 0){
        // measure indent
        size_t space_pos = content.find_first_not_of(" \t\n\r\v");
        if(space_pos != std::string::npos){
            std::string spaces = content.substr(0, space_pos);
            content = content.substr(space_pos);
            content = std::regex_replace(content, std::regex(spaces), "\n" + std::string(indent, ' '));
        }
        content = "\n" + std::string(indent, ' ') + content;
        content = content.substr(0, content.find_last_not_of(" \t\n\r\v") + 1);
    }
    return content;
}