#ifndef ParGen_ParGen_DEF
#define ParGen_ParGen_DEF

#include <string>
#include <filesystem>
#include <Pxml.hpp>

namespace Pargen {

struct ParGen {
    ParGen(std::filesystem::path pxml_path);
    std::string name_space;
};

} // namespace Pargen

#endif