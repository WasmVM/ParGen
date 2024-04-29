#ifndef ParGen_ParGen_DEF
#define ParGen_ParGen_DEF

#include <string>
#include <list>
#include <filesystem>
#include <Pxml.hpp>

namespace Pargen {

struct ParGen {
    void init(std::filesystem::path pxml_path);
    std::string name_space;
    std::list<std::filesystem::path> includes;
};

} // namespace Pargen

#endif