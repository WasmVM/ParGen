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
                "\t.globl\tmain\n"
                "main:\n"
                "\taddi\t$sp,\t$sp,\t-4\n"
                "\tsw\t$ra,\t0($sp)\n"
                "\tjal\tidMain\n"
                "\tlw\t$ra,\t0($sp)\n"
                "\taddi\t$sp,\t$sp,\t4\n"
                "\tjr\t$ra"
             << endl;
        fout << param.textSeg << endl;
        // Epilogue
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
