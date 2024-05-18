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
#include <exception.hpp>
#include <ParGen.hpp>
#include "color.hpp"
#include "CommandParser.hpp"

#ifndef PARGEN_VERSION
#define PARGEN_VERSION "dev"
#endif

int main(int argc, const char* argv[]){

    // Parse argv
    CommandParser args(argc, argv, {
        CommandParser::Optional("--version", "Show version", "-v"),
        CommandParser::Optional("--namespace", "Override namespace of generated objects", 1, "-n"),
        CommandParser::Repeated("--includes", "Add directory to include files search list", 1, "-I"),
        CommandParser::Fixed("pxml_file", "Path of main PXML file")
    },
        "pargen : lexer and parser generator"
    );

    // Show version only
    if(args["version"]){
        std::cout << "pargen version " << PARGEN_VERSION << std::endl;
        return 0;
    }

    // Warnings
    Exception::Warning::regist([](std::string message){
        std::cerr << COLOR_Warning ": " << message << std::endl;
    });

    // Run
    try{
        // Check pxml_file existance
        if(!args["pxml_file"]){
            throw Exception::Exception("no main pxml file");
        }
        std::filesystem::path pxml_file = std::get<std::string>(args["pxml_file"].value());
        // Create ParGen
        Pargen::ParGen pargen;
        pargen.includes.emplace_front(pxml_file.parent_path());
        if(args["includes"]){
            std::vector<std::string> includes = std::get<std::vector<std::string>>(args["includes"].value());
            for(std::string inc : includes){
                pargen.includes.emplace_back(inc);
            }
        }
        // Load pxml
        pargen.load(pxml_file);
        // Generate token files
        if(!pargen.tokens.empty()){
            std::ofstream header_out(pargen.tokens.header_path, std::ios::trunc);
            pargen.tokens.generate_header(header_out);
            header_out.close();
            std::ofstream source_out(pargen.tokens.source_path, std::ios::trunc);
            pargen.tokens.generate_source(source_out);
            source_out.close();
        }
        // Generate lexer files
        if(!pargen.lexer.empty()){
            std::ofstream header_out(pargen.lexer.header_path, std::ios::trunc);
            pargen.lexer.generate_header(header_out);
            header_out.close();
            std::ofstream source_out(pargen.lexer.source_path, std::ios::trunc);
            pargen.lexer.generate_source(source_out);
            source_out.close();
        }
        
    }catch(Exception::SyntaxError& err){
        std::cerr << err.pos.path.string() << ":" << err.pos.line << ":" << err.pos.column
            << " " COLOR_Error ": " << err.what() << std::endl;
        return -2;
    }catch(Exception::Exception &err){
        std::cerr << args.program.filename().string() << " " COLOR_Error ": " << err.what() << std::endl;
        return -1;
    }
    return 0;
}