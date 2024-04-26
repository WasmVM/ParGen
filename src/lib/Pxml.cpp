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

#include <fstream>
#include <Pxml.hpp>
#include <pxml_parser.hpp>
#include <Lexer.hpp>

void PXML::Parser::parse(std::filesystem::path pxml_file){
    // Parse pxml file
    std::ifstream stream(pxml_file);
    Lexer lexer(pxml_file, stream);
    yy::parser parser(lexer, pxml);
    int res = parser();
    stream.close();
    // Parse pxml tree to lexer & parser
}