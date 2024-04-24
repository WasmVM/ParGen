#ifndef Luison_pxml_Pxml_DEF
#define Luison_pxml_Pxml_DEF

#include <string>
#include <optional>
#include <variant>
#include <vector>
#include <unordered_map>

namespace PXML {

using Value = std::variant<std::monostate, bool, std::string, double>;

struct Pxml : std::unordered_map<std::string, Value>{
    using Child = std::variant<std::string, Pxml>;
    std::string tag;
    std::vector<Child> children;
};

} // namespace PXML

#endif