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

#include "parser.hpp"

#include <set>
#include <algorithm>
#include <exception.hpp>

Parser::ParserBase::ParserBase(Pargen::Parser& parser) : parser(parser) {
    // Collect terminals
    std::set<std::string> terms, nterms;
    {
        std::set<std::string> all_terms;
        for(Pargen::Grammar gram : parser){
            nterms.insert(gram.target);
            all_terms.insert(gram.depends.begin(), gram.depends.end());
        }
        std::set_difference(all_terms.begin(), all_terms.end(), nterms.begin(), nterms.end(), std::inserter(terms, terms.end()));
    }

    // Assign term_map
    if(parser.parent.tokens.empty()){
        term_map.assign(std::vector<std::string>(terms.begin(), terms.end()), nterms);
    }else{
        std::vector<std::string> tokens = {"EOF"};
        for(Pargen::Token& token : parser.parent.tokens){
            tokens.emplace_back(token.name);
        }
        term_map.assign(tokens, nterms);
    }
}