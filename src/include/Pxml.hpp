#ifndef ParGen_pxml_Pxml_DEF
#define ParGen_pxml_Pxml_DEF

#include <string>
#include <utility>
#include <variant>
#include <list>
#include <unordered_map>
#include <filesystem>

namespace PXML {

struct Position {
    std::filesystem::path path = "";
    size_t line = 1;
    size_t column = 1;
};

using Value = std::pair<Position, std::variant<std::monostate, bool, std::string, double>>;

struct Pxml : std::unordered_map<std::string, Value>{
    using Child = std::pair<Position, std::variant<std::string, Pxml>>;
    std::string tag;
    std::list<Child> children;
    Position pos;
};

} // namespace PXML

#endif