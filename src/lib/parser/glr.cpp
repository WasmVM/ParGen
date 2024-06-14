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
#include <vector>
#include <algorithm>
#include <exception.hpp>

static TermMap create_term_map(Pargen::Parser& parser){
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
        return TermMap(std::vector<std::string>(terms.begin(), terms.end()), nterms);
    }else{
        std::vector<std::string> tokens;
        for(Pargen::Token& token : parser.parent.tokens){
            tokens.emplace_back(token.name);
        }
        return TermMap(tokens, nterms);
    }
}

GLRParser::GLRParser(Pargen::Parser& parser) : term_map(create_term_map(parser)), parser(parser) {
    read_grammar();
}

void GLRParser::read_grammar(){
    // Read grammars
    std::set<term_t> empties;
    for(Pargen::Grammar& gram : parser){
        if(gram.depends.empty()){
            // Empty grammar
            if(term_map[gram.target] == TermMap::none){
                throw Exception::Exception("unknown terminal '" + gram.target + "'");
            }
            empties.emplace(term_map[gram.target]);
        }else{
            Grammar grammar;
            grammar.target = term_map[gram.target];
            grammar.action = actions.size();
            actions.emplace_back(gram.content);
            std::transform(gram.depends.begin(), gram.depends.end(), std::back_inserter(grammar.depends), [&](std::string& dep){
                if(term_map[dep] == TermMap::none){
                    throw Exception::Exception("unknown terminal '" + dep + "'");
                }
                return term_map[dep];
            });
            grammars.emplace(grammar);
        }
    }

    // Expand empty grammar
    for(auto gram_it = grammars.begin(); gram_it != grammars.end(); gram_it = std::next(gram_it)){
        Grammar gram = *gram_it;
        for(size_t dep_idx = 0; dep_idx < gram.depends.size(); ++dep_idx){
            if(empties.contains(gram.depends[dep_idx])){
                Grammar new_gram = gram;
                new_gram.depends.erase(new_gram.depends.begin() + dep_idx);
                if((new_gram.depends.size() > 1 || (new_gram.depends.size() == 1 && new_gram.target != new_gram.depends[0]))
                    && std::find(grammars.begin(), grammars.end(), new_gram) == grammars.end()
                ){
                    grammars.emplace(new_gram);
                }
            }
        }
    }
}

std::ostream& GLRParser::dump_terms(std::ostream& os){
    std::vector<std::pair<std::string, term_t>> term_list(term_map.begin(), term_map.end());
    std::sort(term_list.begin(), term_list.end(),
        [](const std::pair<std::string, term_t>& lhs, const std::pair<std::string, term_t>& rhs){
            return lhs.second < rhs.second;
        }
    );
    for(std::pair<std::string, term_t>& term_pair : term_list){
        os << "[" << (term_map.is_term(term_pair.second) ? "term" : "non-term") << "]"
            << term_pair.second << "," << term_pair.first << std::endl;
    }
    return os;
}

std::ostream& GLRParser::dump_grammars(std::ostream& os){
    for(Grammar gram : grammars){
        os << term_map[gram.target].value() << " :";
        for(size_t i = 0; i < gram.depends.size(); ++i){
            if(i == gram.dot_pos){
                os << " .";
            }
            os << " " << term_map[gram.depends[i]].value();
        }
        if(gram.dot_pos == gram.depends.size()){
            os << " .";
        }
        if(!gram.lookahead.empty()){
            os << " {";
            for(term_t look : gram.lookahead){
                os << term_map[look].value() << ",";
            }
            os << "}";
        }
        if(gram.action){
            os << " [" << gram.action.value() << "]";
        }
        os << std::endl;
    }
    return os;
}

bool operator<(const GLRParser::Grammar& lhs, const GLRParser::Grammar& rhs){
    if(lhs.target != rhs.target){
        return lhs.target < rhs.target;
    }
    if(lhs.depends.size() != rhs.depends.size()){
        return lhs.depends.size() < rhs.depends.size();
    }
    for(size_t i = 0; i < lhs.depends.size(); ++i){
        if(lhs.depends[i] != rhs.depends[i]){
            return lhs.depends[i] < rhs.depends[i];
        }
    }
    if(lhs.dot_pos != rhs.dot_pos){
        return lhs.dot_pos < rhs.dot_pos;
    }
    if(lhs.lookahead.size() != rhs.lookahead.size()){
        return lhs.lookahead.size() < rhs.lookahead.size();
    }
    std::vector<term_t> look_l(lhs.lookahead.begin(), lhs.lookahead.end());
    std::sort(look_l.begin(), look_l.end());
    std::vector<term_t> look_r(rhs.lookahead.begin(), rhs.lookahead.end());
    std::sort(look_r.begin(), look_r.end());
    for(size_t i = 0; i < look_l.size(); ++i){
        if(look_l[i] != look_r[i]){
            return look_l[i] < look_r[i];
        }
    }
    if(lhs.action.has_value() && rhs.action.has_value()){
        return lhs.action.value() < rhs.action.value();
    }
    return !lhs.action.has_value() && rhs.action.has_value();
}