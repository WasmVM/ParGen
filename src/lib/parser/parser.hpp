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
#include <list>
#include <algorithm>

struct GLRParser {

    struct Action {
        term_t result;
        std::vector<term_t> params;
        std::string body;
    };

    struct Grammar {
        term_t target;
        std::vector<term_t> depends;
        std::set<term_t> lookahead;
        size_t dot_pos = 0;
        size_t action = 0;
        std::vector<bool> param_toggle;

        inline bool operator==(const Grammar& rhs) const {
            return !(*this < rhs) && !(rhs < *this);
        }

        bool like(const Grammar& rhs) const;
    };

    struct State {

        State() = default;
        State(const State&) = default;
        State(std::set<Grammar> productions);

        std::set<Grammar> productions;
        std::map<term_t, size_t> edges;

        // bool merge(State&);
        bool operator==(const State& rhs) const {
            return !(*this < rhs) && !(rhs < *this);
        }
    };

    GLRParser(Pargen::Parser& parser);

    TermMap term_map;
    std::vector<Action> actions;
    std::map<term_t, std::string> type_map;
    std::list<State> states;

    std::ostream& dump_terms(std::ostream& os);
    std::ostream& dump_grammars(std::ostream& os);
    std::ostream& dump_states(std::ostream& os);

    friend bool operator<(const GLRParser::Grammar&, const GLRParser::Grammar&);
    friend bool operator<(const GLRParser::State&, const GLRParser::State&);

protected:

    Pargen::Parser& parser;
    std::list<Grammar> grammars;
    term_t start;

    void read_grammar();
    std::map<term_t, std::set<term_t>> create_first_sets();
    std::ostream& print_grammar(std::ostream&, const Grammar&);

};

bool operator<(const GLRParser::Grammar&, const GLRParser::Grammar&);
bool operator<(const GLRParser::State&, const GLRParser::State&);

#endif