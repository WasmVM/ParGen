#ifndef ParGen_parser_TermMap_DEF
#define ParGen_parser_TermMap_DEF

#include <string>
#include <set>
#include <vector>
#include <unordered_map>

using id_t = size_t;

struct TermMap {
    static constexpr id_t none = (id_t)-1;

    TermMap() = default;
    TermMap(const TermMap& terms) : num_term(terms.num_term), items(terms.items), term_count(terms.term_count){}

    id_t operator[](std::string key){
        if(items.contains(key)){
            return items[key];
        }else{
            return none;
        }
    }
    std::string operator[](id_t value){
        for(auto item : items){
            if(item.second == value){
                return item.first;
            }
        }
        return "";
    }
    size_t size(){
        return items.size();
    }
    std::unordered_map<std::string, id_t>::iterator begin() {
        return items.begin();
    }
    std::unordered_map<std::string, id_t>::iterator end() {
        return items.end();
    }

    void assign(std::vector<std::string> terms, std::set<std::string> nterms){
        num_term = terms.size();
        for(std::string term : terms){
            items.emplace(term, items.size());
        }
        for(std::string nterm : nterms){
            items.emplace(nterm, items.size());
        }
    }
    size_t num_term;
private:
    std::unordered_map<std::string, id_t> items;
    size_t term_count;
};


#endif