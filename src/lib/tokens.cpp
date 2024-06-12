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
#include <regex>
#include <Util.hpp>

using namespace Pargen;

void Pargen::Tokens::generate_header(std::ostream& os){

    // prologue
    os << "/** generated by ParGen **/" << std::endl;
    {
        std::string guard = name_space;
        std::replace(guard.begin(), guard.end(), ':', '_');
        os << "#ifndef ParGen_" << guard << "_guard" << std::endl;
        os << "#define ParGen_" << guard << "_guard" << std::endl;
    }
    os << header_prologue << std::endl;
    os << "#include <iostream>" << std::endl;
    os << "#include <filesystem>" << std::endl;
    os << "#include <variant>" << std::endl;

    // pargen namespace
    os << "\nnamespace " << parent.name_space << " {\n" << std::endl;

    // Position
    os << "struct Position {" << std::endl;
    os << "    std::filesystem::path path;" << std::endl;
    os << "    size_t line = 1;" << std::endl;
    os << "    size_t column = 0;" << std::endl;
    os << "};"<< std::endl;

    // token namespace
    os << "\nnamespace " << name_space << " {\n" << std::endl;

    // Tokens
    std::string token_base = "std::variant<\n  std::monostate";
    for(Token& token : *this){
        // Declaration;
        os << "struct " << token.name << " ";
        token_base += ",\n  " + name_space + "::" + token.name;
        os << "{";
        // Members
        for(std::string& member : token.members){
            os << member << std::endl;
        }
        // Funcs
        for(std::string& func : token.functions){
            os << func << std::endl;
        }
        // Value & Constructor
        os << "\n    " << token.name << "() = default;";
        if(token.types.size() == 1){
            os << "\n    " << token.name << "(" << token.types[0] << " value) : value(value){}";
            os << "\n    " << token.types[0] << " value;";
        }else if(token.types.size() > 1){
            os << "\n    template<typename T>" << token.name << "(T value) : value(value){}";
            os << "\n    std::variant<";
            for(size_t i = 0; i < token.types.size(); ++i){
                if(i > 0){
                    os << ", ";
                }
                os << token.types[i];
            }
            os << "> value;" << std::endl;
        }
        // close
        os << "\n};\n" << std::endl;
    }
    token_base = token_base + "\n>";

    // close namespace
    os << "} // namespace " << name_space << "\n" << std::endl;

    // Token class
    os << "struct " << class_name << " : public " << token_base << " {" << std::endl;
    // Members
    for(std::string& member : members){
        os << member << std::endl;
    }
    // Funcs
    os << "template<typename T> Token(T token, Position pos): " << token_base << "(token), pos(pos){}" << std::endl;
    for(std::string& func : functions){
        os << func << std::endl;
    }
    os << "    Position pos;" << std::endl;
    os << "};\n" << std::endl;

    // close namespace
    os << "} // namespace " << parent.name_space << std::endl;

    // postion output
    os << "\nstd::ostream& operator<< (std::ostream&, " << parent.name_space << "::Position&);"<< std::endl;

    // epilogue
    os << header_epilogue << std::endl;
    os << "#endif " << std::endl;
}

void Pargen::Tokens::generate_source(std::ostream& os){
    // prologue
    os << "/** generated by ParGen **/" << std::endl;
    os << "#include " << header_path << std::endl;
    os << source_prologue << std::endl;

    // functions
    for(std::string func : functions){
        // Write function
        std::string signature = append_func_name(func, parent.name_space + "::" + class_name);
        if(signature.starts_with("template")){
            os << "// TODO: " << signature << "\n" << std::endl;
        }else{
            os << signature << "{" << std::endl;
            os << "    // TODO: implement function here" << std::endl;
            os << "}\n" << std::endl;
        }
    }

    // Token function
    for(Token& token : *this){
        for(std::string func : token.functions){
            // Write function
            std::string signature = append_func_name(func, parent.name_space + "::" + name_space + "::" + token.name);
            if(signature.starts_with("template")){
                os << "// TODO: " << signature << "\n" << std::endl;
            }else{
                os << signature << "{" << std::endl;
                os << "    // TODO: implement function here" << std::endl;
                os << "}\n" << std::endl;
            }
        }
    }

    // Position output
    os << "std::ostream& operator<< (std::ostream& os, " << parent.name_space << "::Position& pos){"<< std::endl;
    os << "    return os << pos.path.string() << \":\" << pos.line << \":\" << pos.column;" << std::endl;
    os << "}" << std::endl;

    // epilogue
    os << source_epilogue << std::endl;
}
