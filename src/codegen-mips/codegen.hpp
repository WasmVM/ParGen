#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include <general.hpp>
#include <genFunc.hpp>

class CodeGen{
public:
    CodeGen();
    void generate(ASTNode *tree, char *fileName);
    bool isError;
private:
    void travel(ASTNode *tree);
    GenParam param;
};
#endif
