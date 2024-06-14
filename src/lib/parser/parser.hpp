#ifndef ParGen_parser_parser_DEF
#define ParGen_parser_parser_DEF

#include <ParGen.hpp>
#include "TermMap.hpp"

#include <string>
#include <vector>
#include <list>
#include <optional>
#include <map>
#include <set>
#include <algorithm>

namespace Parser {

struct Grammar {
    id_t target;
    std::vector<id_t> depends;
    std::set<id_t> lookahead;
    size_t dot_pos = 0;
    std::optional<id_t> action;

    bool operator==(const Grammar& rhs) const {
        return (rhs.target == target) && (rhs.dot_pos == dot_pos) && (rhs.depends == depends);
    }
};

struct ParserBase {
    ParserBase(Pargen::Parser& parser);
    ParserBase(const ParserBase& base) : 
        term_map(base.term_map), actions(base.actions), grammars(base.grammars), parser(base.parser){}
    TermMap term_map;
    std::vector<std::string> actions;
protected:
    std::list<Grammar> grammars;
    Pargen::Parser& parser;
};

struct LALR : public ParserBase {
    LALR(ParserBase&& base);
    LALR(Pargen::Parser& parser) : LALR(ParserBase(parser)) {}
};

} // namespace Parser

#endif