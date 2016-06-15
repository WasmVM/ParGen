#include <codegen.hpp>

GENTABLE
PROTABLE

CodeGen::CodeGen():isError(false)
{

}

void CodeGen::generate(ASTNode *tree, char *fileName)
{
    ofstream fout(fileName);
    // AST Travel
    travel(tree);
    // Write data segment
    {
        fout << "\t.data\n" << param.dataSeg << endl;
    }
    // Write text segment
    {
        // Prologue
        fout << "\t.text\n"
                "\t.globl main\n"
                "main:\n"
                "\tjal\tidMain\n"
                "\tb\texit"
             << endl;
        fout << param.textSeg << endl;
        // Epilogue
        fout << "exit:\n"
                "\tli\t$v0,\t10\n"
                "\tsyscall"
             << endl;
    }
    fout.close();
}

void CodeGen::travel(ASTNode *tree)
{
    if(!proTable[tree->ruleNo-1](tree, param)){
        isError = true;
    }
    for(list<ASTNode *>::iterator it=tree->derives.begin(); it!=tree->derives.end(); ++it){
        travel(*it);
    }
    if(!funcTable[tree->ruleNo-1](tree, param)){
        isError = true;
    }
    delete tree;
}
