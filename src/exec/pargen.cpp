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
#include <exception.hpp>
#include "color.hpp"
#include "CommandParser.hpp"

#ifndef PARGEN_VERSION
#define PARGEN_VERSION "dev"
#endif

int main(int argc, const char* argv[]){

    // Parse argv
    CommandParser args(argc, argv, {
        CommandParser::Optional("--version", "Show version", "-v"),
        CommandParser::Repeated("--includes", "Add directory to include files search list", 1, "-I"),
        CommandParser::Fixed("input_file", "Path of main PXML file", (unsigned int)-1)
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

    try{

    }catch(Exception::Exception &e){
        std::cerr << args.program.filename().string() << ": " COLOR_Error ": " << e.what() << std::endl;
        return -1;
    }
    return 0;
}