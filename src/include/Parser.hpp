#ifndef Luison_pxml_Parser_DEF
#define Luison_pxml_Parser_DEF

#include <filesystem>
#include <Pxml.hpp>

namespace PXML {

struct Parser {

    void parse(std::filesystem::path pxml_file);
    Pxml pxml;
};

} // namespace PXML

#endif