#ifndef ParGen_parser_TermMap_DEF
#define ParGen_parser_TermMap_DEF

#include <string>
#include <set>
#include <vector>
#include <optional>
#include <unordered_map>

using term_t = size_t;

struct TermMap {
    static constexpr term_t none = (term_t)-1;
    static constexpr term_t eof = 1;
    static constexpr term_t start = 0;

    TermMap(const TermMap& terms) : num_term(terms.num_term), items(terms.items){}
    TermMap(std::vector<std::string> terms, std::set<std::string> nterms){
        num_term = items.size() + terms.size();
        for(std::string term : terms){
            items.emplace(term, items.size());
        }
        for(std::string nterm : nterms){
            items.emplace(nterm, items.size());
        }
    }
    TermMap(Pargen::Parser& parser);

    term_t operator[](std::string key){
        if(items.contains(key)){
            return items[key];
        }else{
            return none;
        }
    }
    std::optional<std::string> operator[](term_t value){
        for(auto item : items){
            if(item.second == value){
                return item.first;
            }
        }
        return std::nullopt;
    }
    size_t size(){
        return items.size();
    }
    std::unordered_map<std::string, term_t>::iterator begin() {
        return items.begin();
    }
    std::unordered_map<std::string, term_t>::iterator end() {
        return items.end();
    }

    bool is_term(term_t term){
        return term < num_term;
    }
private:
    size_t num_term;
    std::unordered_map<std::string, term_t> items = {{"", 0}, {"EOF", 1}};
};


#endif