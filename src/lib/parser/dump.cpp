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

#include "parser.hpp"

std::ostream& GLRParser::print_grammar(std::ostream& os, const GLRParser::Grammar& gram){
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
        os << " (";
        for(term_t look : gram.lookahead){
            os << term_map[look].value() << ",";
        }
        os << ")";
    }
    os << " [" << gram.action << "]";
    return os;
}

std::ostream& GLRParser::dump_terms(std::ostream& os){
    std::vector<std::pair<std::string, term_t>> term_list(term_map.begin(), term_map.end());
    std::sort(term_list.begin(), term_list.end(),
        [](const std::pair<std::string, term_t>& lhs, const std::pair<std::string, term_t>& rhs){
            return lhs.second < rhs.second;
        }
    );
    for(std::pair<std::string, term_t>& term_pair : term_list){
        os << "[" << (term_map.is_term(term_pair.second) ? "term" : "non-term") << "] "
            << term_pair.second << "," << term_pair.first << std::endl;
    }
    return os;
}

std::ostream& GLRParser::dump_grammars(std::ostream& os){
    for(Grammar gram : grammars){
        print_grammar(os, gram) << std::endl;
    }
    return os;
}

std::ostream& GLRParser::dump_states(std::ostream& os){
    os << "digraph {" << std::endl;
    os << "  node [shape=\"box\"]" << std::endl;
    size_t state_id = 0;
    for(State& state : states){
        // node
        os << "S" << state_id << " [label=<<table border=\"0\" cellborder=\"0\" cellspacing=\"0\">";
        os << "<tr><td>S" << state_id <<"</td></tr>" << state_id;
        for(const Grammar& prod : state.productions){
            os << "<tr><td>";
            if(prod.dot_pos == prod.depends.size()){
                os << "<font color=\"red\">";
                print_grammar(os, prod);
                os << "</font>";
            }else{
                print_grammar(os, prod);
            }
            os << "</td></tr>";
        }
        os << "</table>>];" << std::endl;
        // edge
        for(auto edge : state.edges){
            os << "S" << state_id << " -> S" << edge.second;
            os << " [label=\"" << term_map[edge.first].value_or("") << "\"];" << std::endl;
        }
        state_id += 1;
    }
    os << "}" << std::endl;
    return os;
}
