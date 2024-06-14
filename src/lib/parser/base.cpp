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

    // Read grammars
    std::set<id_t> empties;
    for(Pargen::Grammar& gram : parser){
        if(gram.depends.empty()){
            // Empty grammar
            if(term_map[gram.target] == TermMap::none){
                throw Exception::Exception("unknown terminal '" + gram.target + "'");
            }
            empties.emplace(term_map[gram.target]);
        }else{
            Parser::Grammar& grammar = grammars.emplace_back();
            grammar.target = term_map[gram.target];
            grammar.action = actions.size();
            actions.emplace_back(gram.content);
            std::transform(gram.depends.begin(), gram.depends.end(), std::back_inserter(grammar.depends), [&](std::string& dep){
                if(term_map[dep] == TermMap::none){
                    throw Exception::Exception("unknown terminal '" + dep + "'");
                }
                return term_map[dep];
            });
        }
    }

    // Expand empty grammar
    for(auto gram_it = grammars.begin(); gram_it != grammars.end(); gram_it = std::next(gram_it)){
        Parser::Grammar& gram = *gram_it;
        for(size_t dep_idx = 0; dep_idx < gram.depends.size(); ++dep_idx){
            if(empties.contains(gram.depends[dep_idx])){
                Parser::Grammar new_gram = gram;
                new_gram.depends.erase(new_gram.depends.begin() + dep_idx);
                if((new_gram.depends.size() > 1 || (new_gram.depends.size() == 1 && new_gram.target != new_gram.depends[0]))
                    && std::find(grammars.begin(), grammars.end(), new_gram) == grammars.end()
                ){
                    grammars.emplace_back(new_gram);
                }
            }
        }
    }

    // FIXME: output grammars
    for(Parser::Grammar& gram : grammars){
        std::cout << term_map[gram.target] << " :=";
        for(size_t i = 0; i < gram.depends.size(); ++i){
            if(i == gram.dot_pos){
                std::cout << " .";
            }
            std::cout << " " << term_map[gram.depends[i]];
        }
        if(gram.action){
            std::cout << " [" << gram.action.value() << "]";
        }
        std::cout << std::endl;
    }
}