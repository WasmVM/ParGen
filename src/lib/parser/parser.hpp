#ifndef ParGen_parser_parser_DEF
#define ParGen_parser_parser_DEF

#include <ParGen.hpp>
#include <exception.hpp>
#include "TermMap.hpp"

#include <string>
#include <vector>
#include <optional>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

struct GLRParser {
    GLRParser(Pargen::Parser& parser);
    TermMap term_map;
    std::vector<std::string> actions;

    std::ostream& dump_terms(std::ostream& os);
    std::ostream& dump_grammars(std::ostream& os);

protected:

    struct Grammar {
        term_t target;
        std::vector<term_t> depends;
        std::set<term_t> lookahead;
        size_t dot_pos = 0;
        std::optional<size_t> action;

        bool operator==(const Grammar& rhs) const {
            return !(*this < rhs) && !(rhs < *this);
        }
        std::ostream& operator<<(std::ostream&);
    };

    struct State {
        std::vector<Grammar> produtions;
        std::map<term_t, size_t> edges;
    };

    Pargen::Parser& parser;
    std::vector<State> states;
    std::set<Grammar> grammars;

    void read_grammar();

public:
    friend bool operator<(const Grammar&, const Grammar&);    
};

bool operator<(const GLRParser::Grammar&, const GLRParser::Grammar&);

#endif