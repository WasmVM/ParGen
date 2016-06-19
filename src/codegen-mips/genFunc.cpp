#include <genFunc.hpp>

static int spTop = 0, blockLevel = 0, regCount = 0, ifCount = 0, whileCount = 0;
static vector<int> ifStack, ifTogStack, whileStack, whileTogStack;

bool gen1(ASTNode *, GenParam &){
	return true;
}
bool pro1(ASTNode *, GenParam &){
	return true;
}
bool gen2(ASTNode *, GenParam &param){
    if(blockLevel > 1){
        stringstream ss;
        ss << (int)param.spLasts.back() - spTop;
        param.tmpText.back() += "\taddi\t$sp,\t$sp,\t" + ss.str() + "\n";
    }
    return true;
}
bool pro2(ASTNode *, GenParam &){
	return true;
}
bool gen3(ASTNode *node, GenParam &param){
    Variable &var = param.varStack.back();
    var.totalSize = var.unitSize;
    var.id = node->terms.at(1).value;
    if(blockLevel < 1){ // global
        if(var.unitSize == 4){
            param.dataSeg += var.id + ":\t.word\t0\n";
        }else{
            param.dataSeg += var.id + ":\t.byte\t0\n";
        }
        var.offset = 0;
        var.type = GLOBALVAR;
        param.gloStack.push_back(var);
        param.varStack.pop_back();
    }else{  // local
        spTop += var.unitSize;
        var.offset = spTop;
        var.type = LOCALVAR;
        param.varCounts.back() += 1;
    }
	return true;
}
bool pro3(ASTNode *, GenParam &){
	return true;
}
bool gen4(ASTNode *node, GenParam &param){
    Variable &var = param.varStack.back();
    var.id = node->terms.at(0).value;
    if(blockLevel < 1){ // global
        stringstream ss;
        ss << var.totalSize;
        param.dataSeg += var.id + ":\t.space\t" + ss.str() + "\n";
        var.offset = 0;
        var.type = GLOBALREF;
        param.gloStack.push_back(var);
        param.varStack.pop_back();
    }else{  // local
        spTop += var.totalSize;
        var.offset = spTop;
        var.type = LOCALREF;
        param.varCounts.back() += 1;
    }
	return true;
}
bool pro4(ASTNode *, GenParam &){
	return true;
}
bool gen5(ASTNode *, GenParam &param){
    Variable &fun = param.funList.back();
    param.textSeg += fun.id + ":\n";
    stringstream ss;
    ss << spTop;
    if(spTop > 0){
        param.textSeg += "\taddi\t$sp,\t$sp,\t" + ss.str() + "\n";
    }
    param.textSeg += "\tsw\t$ra,\t0($sp)\n";
    if(spTop > 0){
        param.textSeg += "\taddi\t$sp,\t$sp,\t-" + ss.str() + "\n";
    }
    param.textSeg += param.tmpText.back();
    param.tmpText.pop_back();
    spTop = param.spLasts.back();
    param.spLasts.clear();
    param.varStack.clear();
    param.varCounts.pop_back();
    regCount = 0;
	return true;
}
bool pro5(ASTNode *, GenParam &param){
    if(blockLevel > 0){
        return false;
    }
    param.varCounts.push_back(0);
    param.spLasts.push_back(spTop);
    spTop = 0;
    param.tmpText.push_back(string());
	return true;
}
bool gen6(ASTNode *, GenParam &param){
    Variable &fun = param.funList.back();
    param.textSeg += fun.id + ":\n";
    stringstream ss;
    ss << spTop;
    if(spTop > 0){
        param.textSeg += "\taddi\t$sp,\t$sp,\t" + ss.str() + "\n";
    }
    param.textSeg += "\tsw\t$ra,\t0($sp)\n";
    if(spTop > 0){
        param.textSeg += "\taddi\t$sp,\t$sp,\t-" + ss.str() + "\n";
    }
    param.textSeg += param.tmpText.back();
    param.tmpText.pop_back();
    spTop = 0;
    param.spLasts.clear();
    param.varStack.clear();
    param.varCounts.pop_back();
    regCount = 0;
	return true;
}
bool pro6(ASTNode *, GenParam &param){
    if(blockLevel > 0){
        return false;
    }
    param.varCounts.push_back(0);
    param.tmpText.push_back(string());
    return true;
}
bool gen7(ASTNode *, GenParam &){
	return true;
}
bool pro7(ASTNode *, GenParam &){
	return true;
}
bool gen8(ASTNode *, GenParam &){
	return true;
}
bool pro8(ASTNode *, GenParam &){
	return true;
}
bool gen9(ASTNode *, GenParam &){
	return true;
}
bool pro9(ASTNode *, GenParam &){
	return true;
}
bool gen10(ASTNode *, GenParam &){
	return true;
}
bool pro10(ASTNode *, GenParam &){
	return true;
}
bool gen11(ASTNode *, GenParam &){
	return true;
}
bool pro11(ASTNode *, GenParam &){
	return true;
}
bool gen12(ASTNode *, GenParam &){
	return true;
}
bool pro12(ASTNode *, GenParam &){
	return true;
}
bool gen13(ASTNode *node, GenParam &param){
    Variable &val = param.varStack.back();
    val.id = node->terms.at(0).value;
    val.totalSize = val.unitSize;
    val.type = LOCALVAR;
    spTop += 4;
    val.offset = spTop;
    param.varCounts.back() += 1;
    param.varStack.front().paramSize.push_back(val.totalSize);
	return true;
}
bool pro13(ASTNode *, GenParam &){
	return true;
}
bool gen14(ASTNode *node, GenParam &param){
    Variable &val = param.varStack.back();
    val.id = node->terms.at(0).value;
    val.totalSize = val.totalSize;
    val.type = LOCALREF;
    spTop += 4;
    val.offset = spTop;
    param.varCounts.back() += 1;
    param.varStack.front().paramSize.push_back(val.totalSize);
	return true;
}
bool pro14(ASTNode *, GenParam &){
	return true;
}
bool gen15(ASTNode *node, GenParam &param){
    Variable &val = param.varStack.back();
    stringstream ss(node->terms.at(2).value);
    ss >> val.totalSize;
    if(val.totalSize < 1){
        // TOTO error msg
        return false;
    }
    val.totalSize *= val.unitSize;
    return true;
}
bool pro15(ASTNode *, GenParam &){
	return true;
}
bool gen16(ASTNode *, GenParam &){
	return true;
}
bool pro16(ASTNode *, GenParam &){
	return true;
}
bool gen17(ASTNode *, GenParam &param){
    --blockLevel;
    if(blockLevel > 0){
        int spDiff = spTop - param.spLasts.back();
        stringstream ss;
        ss << spDiff;
        param.tmpText.back() += "\taddi\t$sp,\t$sp,\t" + ss.str() + "\n";
        spTop = param.spLasts.back();
        param.spLasts.pop_back();
        while(spDiff > 0){
            spDiff -= param.varStack.back().totalSize;
            param.varStack.pop_back();
        }
    }
	return true;
}
bool pro17(ASTNode *node, GenParam &param){
    if(blockLevel < 1){ //Function block
        Variable &val = param.varStack.front();
        val.id = node->parent->terms.at(2).value;
        param.funList.push_back(val);
        param.varStack.erase(param.varStack.begin());
    }else{
        param.spLasts.push_back(spTop);
    }
    ++blockLevel;
    return true;
}
bool gen18(ASTNode *, GenParam &){
    return true;
}
bool pro18(ASTNode *node, GenParam &param){
    if(blockLevel < 1){ //Function block
        Variable &val = param.varStack.front();
        val.id = node->parent->terms.at(2).value;
        param.funList.push_back(val);
        param.varStack.erase(param.varStack.begin());
    }
	return true;
}
bool gen19(ASTNode *, GenParam &){
    --blockLevel;
	return true;
}
bool pro19(ASTNode *node, GenParam &param){
    if(blockLevel < 1){ //Function block
        Variable &val = param.varStack.front();
        val.id = node->parent->terms.at(2).value;
        param.funList.push_back(val);
        param.varStack.erase(param.varStack.begin());
    }
    ++blockLevel;
	return true;
}
bool gen20(ASTNode *, GenParam &param){
    --blockLevel;
    if(blockLevel > 0){
        int spDiff = spTop - param.spLasts.back();
        stringstream ss;
        ss << spDiff;
        param.tmpText.back() += "\taddi\t$sp,\t$sp,\t" + ss.str() + "\n";
        spTop = param.spLasts.back();
        param.spLasts.pop_back();
        while(spDiff > 0){
            spDiff -= param.varStack.back().totalSize;
            param.varStack.pop_back();
        }
    }
	return true;
}
bool pro20(ASTNode *node, GenParam &param){
    if(blockLevel < 1){ //Function block
        Variable &val = param.varStack.front();
        val.id = node->parent->terms.at(2).value;
        param.funList.push_back(val);
        param.varStack.erase(param.varStack.begin());
    }else{
        param.spLasts.push_back(spTop);
    }
    ++blockLevel;
	return true;
}
bool gen21(ASTNode *, GenParam &param){
    Variable newVar;
    newVar.unitSize = 4;
    newVar.totalSize = 0;
    param.varStack.push_back(newVar);
	return true;
}
bool pro21(ASTNode *, GenParam &){
	return true;
}
bool gen22(ASTNode *, GenParam &param){
    Variable newVar;
    newVar.unitSize = 1;
    newVar.totalSize = 0;
    param.varStack.push_back(newVar);
	return true;
}
bool pro22(ASTNode *, GenParam &){
	return true;
}
bool gen23(ASTNode *, GenParam &){
	return true;
}
bool pro23(ASTNode *, GenParam &){
	return true;
}
bool gen24(ASTNode *, GenParam &){
	return true;
}
bool pro24(ASTNode *, GenParam &){
	return true;
}
bool gen25(ASTNode *, GenParam &){
	return true;
}
bool pro25(ASTNode *, GenParam &){
	return true;
}
bool gen26(ASTNode *, GenParam &){
    regCount = 0;
	return true;
}
bool pro26(ASTNode *, GenParam &){
	return true;
}
bool gen27(ASTNode *, GenParam &param){
    Variable &data = param.dataStack.back();
    switch (data.type) {
        case GLOBALVAR:
        case GLOBALREF:
        case LOCALVAR:
        case LOCALREF:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t$v0,\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t$v0,\t" + data.id + "\n";
            }
            break;
        case REGISTER:
            param.tmpText.back() += "\tmove\t$v0,\t" + data.id + "\n";
            break;
        default:
            return false;
            break;
    }
    stringstream ss;
    ss << spTop;
    if(spTop > 0){
        param.tmpText.back() += "\taddi\t$sp,\t$sp,\t" + ss.str() + "\n";
    }
    param.tmpText.back() += "\tlw\t$ra,\t0($sp)\n"
                            "\taddi\t$sp,\t$sp,\t4\n"
                            "\tjr\t$ra\n";
	return true;
}
bool pro27(ASTNode *, GenParam &){
	return true;
}
bool gen28(ASTNode *, GenParam &param){
    // Clean
    param.dataStack.clear();
    regCount = 0;
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            ifTogStack.pop_back();
            stringstream ss;
            ss << ifStack.back();
            if(ifTogStack.back() == 1){
                param.tmpText.back() += "\tb\tIf" + ss.str() + "_end\n";
                param.tmpText.back() += "If" + ss.str() + "_else:\n";
            }else if(ifTogStack.back() == 2){
                param.tmpText.back() += "If" + ss.str() + "_end:\n";
            }
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
    // Break;
    stringstream ss;
    ss << whileStack.back();
    param.tmpText.back() += "\tb\tWhile" + ss.str() + "_end\n";
	return true;
}
bool pro28(ASTNode *, GenParam &){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() >= 1){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
	return true;
}
bool gen29(ASTNode *, GenParam &param){
    ifTogStack.pop_back();
    ifStack.pop_back();
    // Clean
    param.dataStack.clear();
    regCount = 0;
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            ifTogStack.pop_back();
            stringstream ss;
            ss << ifStack.back();
            if(ifTogStack.back() == 1){
                param.tmpText.back() += "\tb\tIf" + ss.str() + "_end\n";
                param.tmpText.back() += "If" + ss.str() + "_else:\n";
            }else if(ifTogStack.back() == 2){
                param.tmpText.back() += "If" + ss.str() + "_end:\n";
            }
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
	return true;
}
bool pro29(ASTNode *, GenParam &){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() >= 1){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
    ifTogStack.push_back(0);
    ifStack.push_back(ifCount++);
	return true;
}
bool gen30(ASTNode *, GenParam &param){
    // Clean
    param.dataStack.clear();
    regCount = 0;
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            ifTogStack.pop_back();
            stringstream ss;
            ss << ifStack.back();
            if(ifTogStack.back() == 1){
                param.tmpText.back() += "\tb\tIf" + ss.str() + "_end\n";
                param.tmpText.back() += "If" + ss.str() + "_else:\n";
            }else if(ifTogStack.back() == 2){
                param.tmpText.back() += "If" + ss.str() + "_end:\n";
            }
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
    // While
    stringstream ss;
    ss << whileStack.back();
    param.tmpText.back() += "\tb\tWhile" + ss.str() + "_begin\n";
    param.tmpText.back() += "While" + ss.str() + "_end:\n";
    whileTogStack.pop_back();
    whileStack.pop_back();
	return true;
}
bool pro30(ASTNode *, GenParam &param){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() >= 1){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
    // While
    stringstream ss;
    ss << whileCount;
    param.tmpText.back() += "While" + ss.str() + "_begin:\n";
    whileTogStack.push_back(0);
    whileStack.push_back(whileCount++);
	return true;
}
bool gen31(ASTNode *, GenParam &param){
    // Clean
    param.dataStack.clear();
    regCount = 0;
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            ifTogStack.pop_back();
            stringstream ss;
            ss << ifStack.back();
            if(ifTogStack.back() == 1){
                param.tmpText.back() += "\tb\tIf" + ss.str() + "_end\n";
                param.tmpText.back() += "If" + ss.str() + "_else:\n";
            }else if(ifTogStack.back() == 2){
                param.tmpText.back() += "If" + ss.str() + "_end:\n";
            }
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
	return true;
}
bool pro31(ASTNode *, GenParam &param){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() >= 1){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
    // Clean
    param.dataStack.clear();
    regCount = 0;
	return true;
}
bool gen32(ASTNode *, GenParam &param){
    Variable &data = param.dataStack.back();
    stringstream ss;
    switch (data.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data.id + "\n";
            }
            ++regCount;
            data.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data.id + ",\t0(" + data.id + ")\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data.id + ",\t0(" + data.id + ")\n";
            }
            break;
        default:
            return false;
            break;
    }
    // print
    param.tmpText.back() += "\tmove\t$a0,\t" + data.id + "\n";
    param.tmpText.back() += "\tli\t$v0,\t1\n";
    param.tmpText.back() += "\tsyscall\n";
    // Clean
    param.dataStack.clear();
    regCount = 0;
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            ifTogStack.pop_back();
            stringstream ss;
            ss << ifStack.back();
            if(ifTogStack.back() == 1){
                param.tmpText.back() += "\tb\tIf" + ss.str() + "_end\n";
                param.tmpText.back() += "If" + ss.str() + "_else:\n";
            }else if(ifTogStack.back() == 2){
                param.tmpText.back() += "If" + ss.str() + "_end:\n";
            }
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
	return true;
}
bool pro32(ASTNode *, GenParam &){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() >= 1){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
	return true;
}
bool gen33(ASTNode *, GenParam &param){
    Variable data1 = param.dataStack.back();
    // Load data1
    switch (data1.type) {
        case GLOBALVAR:
        case GLOBALREF:
            break;
        case LOCALVAR:
        case LOCALREF:
            data1.id = "0(" + data1.id + ")";
            break;
        case REGISTER:
        default:
            return false;
            break;
    }
    // Read;
    param.tmpText.back() += "\tli\t$v0,\t5\n";
    param.tmpText.back() += "\tsyscall\n";
    // Store
    if(data1.unitSize == 4){
        param.tmpText.back() += "\tsw\t$v0,\t" + data1.id + "\n";
    }else{
        param.tmpText.back() += "\tsb\t$v0,\t" + data1.id + "\n";
    }
    // Clean
    param.dataStack.clear();
    regCount = 0;
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            ifTogStack.pop_back();
            stringstream ss;
            ss << ifStack.back();
            if(ifTogStack.back() == 1){
                param.tmpText.back() += "\tb\tIf" + ss.str() + "_end\n";
                param.tmpText.back() += "If" + ss.str() + "_else:\n";
            }else if(ifTogStack.back() == 2){
                param.tmpText.back() += "If" + ss.str() + "_end:\n";
            }
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
	return true;
}
bool pro33(ASTNode *, GenParam &){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() >= 1){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
	return true;
}
bool gen34(ASTNode *, GenParam &param){
    Variable data = param.dataStack.back();
    // Load data
    switch (data.type) {
        case LOCALVAR:
            data.id = "0(" + data.id + ")";
        case GLOBALVAR:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t$t8,\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t$t8,\t" + data.id + "\n";
            }
            break;
        case LOCALREF:
            data.id = "0(" + data.id + ")";
        case GLOBALREF:
            param.tmpText.back() += "\tla\t$t8,\t" + data.id + "\n";
            break;
        case REGISTER:
            param.tmpText.back() += "\tmove\t$t8,\t" + data.id + "\n";
            break;
        default:
            return false;
            break;
    }
    param.tmpText.back() += "\taddi\t$sp,\t$sp,\t-4\n";
    param.tmpText.back() += "\tsw\t$t8,\t0($sp)\n";
	return true;
}
bool pro34(ASTNode *, GenParam &){
	return true;
}
bool gen35(ASTNode *, GenParam &param){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == -1){
            stringstream ss;
            ss << ifStack.back();
            param.tmpText.back() += "\tbeqz\t" + param.dataStack.back().id +",\tIf" + ss.str() + "_else\n";
            ifTogStack.pop_back();
            ++ifTogStack.back();
        }else if(ifTogStack.back() < -1){
            ++ifTogStack.back();
        }
    }
    // While
    if(whileTogStack.size() > 0){
        if(whileTogStack.back() == -1){
            stringstream ss;
            ss << whileStack.back();
            param.tmpText.back() += "\tbeqz\t" + param.dataStack.back().id +",\tWhile" + ss.str() + "_end\n";
            whileTogStack.pop_back();
            ++whileTogStack.back();
        }else if(whileTogStack.back() < -1){
            ++whileTogStack.back();
        }
    }
	return true;
}
bool pro35(ASTNode *, GenParam &){
    // If
    if(ifTogStack.size() > 0){
        if(ifTogStack.back() == 0){
            ifTogStack.push_back(-1);
        }else if(ifTogStack.back() < 0){
            --ifTogStack.back();
        }
    }
    // While
    if(whileTogStack.size() > 0){
        if(whileTogStack.back() == 0){
            whileTogStack.push_back(-1);
        }else if(whileTogStack.back() < 0){
            --whileTogStack.back();
        }
    }
	return true;
}
bool gen36(ASTNode *, GenParam &param){
    Variable &data2 = param.dataStack.back();
    param.dataStack.pop_back();
    Variable data1 = param.dataStack.back();
    param.dataStack.pop_back();
    param.dataStack.push_back(data2);
    // Load data1
    stringstream ss;
    switch (data1.type) {
        case GLOBALVAR:
        case GLOBALREF:
            break;
        case LOCALVAR:
        case LOCALREF:
            data1.id = "0(" + data1.id + ")";
            break;
        case REGISTER:
        default:
            return false;
            break;
    }
    // Load data2
    ss.str(string());
    switch (data2.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data2.id + "\n";
            }
            ++regCount;
            data2.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data2.id + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data2.id + ",\t" + data2.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data2.type = REGISTER;
    // Store
    if(data1.unitSize == 4){
        param.tmpText.back() += "\tsw\t" + data2.id + ",\t" + data1.id + "\n";
    }else{
        param.tmpText.back() += "\tsb\t" + data2.id + ",\t" + data1.id + "\n";
    }

    return true;
}
bool pro36(ASTNode *, GenParam &){
	return true;
}
bool gen37(ASTNode *, GenParam &){
	return true;
}
bool pro37(ASTNode *, GenParam &){
	return true;
}
bool gen38(ASTNode *node, GenParam &param){
    Variable &data2 = param.dataStack.back();
    param.dataStack.pop_back();
    Variable &data1 = param.dataStack.back();
    // Load data1
    stringstream ss;
    switch (data1.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data1.id + "\n";
            }
            ++regCount;
            data1.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data1.id + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data1.id + ",\t" + data1.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data1.type = REGISTER;
    // Load data2
    ss.str(string());
    switch (data2.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data2.id + "\n";
            }
            ++regCount;
            data2.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data2.id + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data2.id + ",\t" + data2.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data2.type = REGISTER;
    // Compute
    switch(node->terms.at(0).type) {
    case AND:
        param.tmpText.back() += "\tand\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    case OR:
        param.tmpText.back() += "\tor\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    default:
        return false;
    }
	return true;
}
bool pro38(ASTNode *, GenParam &){
	return true;
}
bool gen39(ASTNode *, GenParam &){
	return true;
}
bool pro39(ASTNode *, GenParam &){
	return true;
}
bool gen40(ASTNode *node, GenParam &param){
    Variable &data2 = param.dataStack.back();
    param.dataStack.pop_back();
    Variable &data1 = param.dataStack.back();
    // Load data1
    stringstream ss;
    switch (data1.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data1.id + "\n";
            }
            ++regCount;
            data1.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data1.id + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data1.id + ",\t" + data1.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data1.type = REGISTER;
    // Load data2
    ss.str(string());
    switch (data2.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data2.id + "\n";
            }
            ++regCount;
            data2.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data2.id + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data2.id + ",\t" + data2.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data2.type = REGISTER;
    // Compute
    switch (node->terms.at(0).type) {
    case EQUA:
        param.tmpText.back() += "\tseq\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    case NEQU:
        param.tmpText.back() += "\tsne\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    case GREA:
        param.tmpText.back() += "\tsgt\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    case GREQ:
        param.tmpText.back() += "\tsge\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    case LSTH:
        param.tmpText.back() += "\tslt\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    case LSEQ:
        param.tmpText.back() += "\tsle\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
        break;
    default:
        return false;
        break;
    }
	return true;
}
bool pro40(ASTNode *, GenParam &){
	return true;
}
bool gen41(ASTNode *, GenParam &){
	return true;
}
bool pro41(ASTNode *, GenParam &){
	return true;
}
bool gen42(ASTNode *, GenParam &param){
    Variable &data2 = param.dataStack.back();
    param.dataStack.pop_back();
    Variable &data1 = param.dataStack.back();
    // Load data1
    stringstream ss;
    switch (data1.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data1.id + "\n";
            }
            ++regCount;
            data1.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data1.id + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data1.id + ",\t" + data1.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data1.type = REGISTER;
    // Load data2
    ss.str(string());
    switch (data2.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data2.id + "\n";
            }
            ++regCount;
            data2.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data2.id + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data2.id + ",\t" + data2.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data2.type = REGISTER;
    // Compute
    param.tmpText.back() += "\tsub\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
    return true;
}
bool pro42(ASTNode *, GenParam &){
	return true;
}
bool gen43(ASTNode *, GenParam &param){
    Variable &data2 = param.dataStack.back();
    param.dataStack.pop_back();
    Variable &data1 = param.dataStack.back();
    // Load data1
    stringstream ss;
    switch (data1.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data1.id + "\n";
            }
            ++regCount;
            data1.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data1.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data1.id + ",\t" + data1.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data1.id + ",\t" + data1.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data1.type = REGISTER;
    // Load data2
    ss.str(string());
    switch (data2.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data2.id + "\n";
            }
            ++regCount;
            data2.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data2.id + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data2.id + ",\t" + data2.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data2.type = REGISTER;
    // Compute
    param.tmpText.back() += "\tadd\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
    return true;
}
bool pro43(ASTNode *, GenParam &){
	return true;
}
bool gen44(ASTNode *, GenParam &){
	return true;
}
bool pro44(ASTNode *, GenParam &){
	return true;
}
bool gen45(ASTNode *node, GenParam &param){
    Variable &data2 = param.dataStack.back();
    param.dataStack.pop_back();
    Variable &data1 = param.dataStack.back();
    // Load data2
    stringstream ss;
    switch (data2.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data2.id + "\n";
            }
            ++regCount;
            data2.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data2.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data2.id + ",\t" + data2.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data2.id + ",\t" + data2.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data2.type = REGISTER;
    // Compute
    if(node->terms.at(0).type == MULT){
        param.tmpText.back() += "\tmul\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
    }else{
        param.tmpText.back() += "\tdiv\t" + data1.id + ",\t" + data1.id + ",\t" + data2.id + "\n";
    }
    return true;
}
bool pro45(ASTNode *, GenParam &){
	return true;
}
bool gen46(ASTNode *, GenParam &){
	return true;
}
bool pro46(ASTNode *, GenParam &){
	return true;
}
bool gen47(ASTNode *, GenParam &){
	return true;
}
bool pro47(ASTNode *, GenParam &){
	return true;
}
bool gen48(ASTNode *node, GenParam &param){
    Variable &data = param.dataStack.back();
    stringstream ss;
    switch (data.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data.id + "\n";
            }
            ++regCount;
            data.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data.id + ",\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data.id + ",\t" + data.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data.type = REGISTER;
    if(node->terms.at(0).type == OOPS){
        param.tmpText.back() += "\tnot\t" + data.id + ",\t" + data.id + "\n";
    }else{
        param.tmpText.back() += "\tsub\t" + data.id + ",\t$zero,\t" + data.id + "\n";
    }
	return true;
}
bool pro48(ASTNode *, GenParam &){
	return true;
}
bool gen49(ASTNode *, GenParam &){
	return true;
}
bool pro49(ASTNode *, GenParam &){
	return true;
}
bool gen50(ASTNode *node, GenParam &param){
    Variable var;
    bool exist = false;
    // Global
    for(vector<Variable>::iterator it=param.gloStack.begin(); it!=param.gloStack.end(); ++it){
        if(it->id == node->terms.at(0).value){
            exist = true;
            var = *it;
            break;
        }
    }
    // Local
    if(!exist){
        for(unsigned int i = param.varCounts.at(param.varCounts.size()-1); i>0; --i){
            vector<Variable>::iterator it = param.varStack.end()-i;
            if(it->id == node->terms.at(0).value){
                exist = true;
                var = *it;
                stringstream ss;
                ss << "\taddi\t$t" << regCount << ",\t$sp,\t" << spTop - var.offset << "\n";
                param.tmpText.back() += ss.str();
                ss.str(string());
                ss << "$t" << regCount;
                var.id = ss.str();
                ++regCount;
                break;
            }
        }
    }
    if(!exist){
        return false;
    }else{
        param.dataStack.push_back(var);
    }
	return true;
}
bool pro50(ASTNode *, GenParam &){
	return true;
}
bool gen51(ASTNode *node, GenParam &param){
    Variable var, &varE = param.dataStack.back();
    bool exist = false;
    // Global
    for(vector<Variable>::iterator it=param.gloStack.begin(); it!=param.gloStack.end(); ++it){
        if(it->id == node->terms.at(2).value){
            exist = true;
            var = *it;
            param.tmpText.back() += "\tla\t$t8,\t" + var.id + "\n";
            stringstream ss;
            ss << var.unitSize;
            param.tmpText.back() += "\tmul\t" + varE.id +",\t"+ varE.id +",\t"+ ss.str() +"\n";
            param.tmpText.back() += "\tadd\t"+ varE.id +",\t$t8,\t" + varE.id + "\n";
            varE.id = "0(" + varE.id + ")";
            varE.type = GLOBALREF;
            break;
        }
    }
    // Local
    if(!exist){
        for(unsigned int i = param.varCounts.back(); i>0; --i){
            vector<Variable>::iterator it = param.varStack.end()-i;
            if(it->id == node->terms.at(0).value){
                exist = true;
                var = *it;
                stringstream ss;
                ss << "\tmul\t" << varE.id << ",\t" << varE.id << ",\t" << var.unitSize ;
                ss << "\taddi\t" << varE.id << ",\t$sp,\t" << varE.id << "\n";
                ss << "\taddi\t$t" << varE.id << ",\t$sp,\t" << spTop - var.offset << "\n";
                param.tmpText.back() += ss.str();
                varE.type = LOCALREF;
                break;
            }
        }
    }
    if(!exist){
        return false;
    }
    return true;
}
bool pro51(ASTNode *, GenParam &){
	return true;
}
bool gen52(ASTNode *node, GenParam &param){
    Variable data = param.dataStack.back();
    // Load data
    switch (data.type) {
        case LOCALVAR:
            data.id = "0(" + data.id + ")";
        case GLOBALVAR:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t$t8,\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t$t8,\t" + data.id + "\n";
            }
            break;
        case LOCALREF:
            data.id = "0(" + data.id + ")";
        case GLOBALREF:
            param.tmpText.back() += "\tla\t$t8,\t" + data.id + "\n";
            break;
        case REGISTER:
            param.tmpText.back() += "\tmove\t$t8,\t" + data.id + "\n";
            break;
        default:
            return false;
            break;
    }
    param.tmpText.back() += "\taddi\t$sp,\t$sp,\t-4\n";
    param.tmpText.back() += "\tsw\t$t8,\t0($sp)\n";
    Variable fun;
    // FunList
    bool exist = false;
    for(vector<Variable>::iterator it=param.funList.begin(); it!=param.funList.end(); ++it){
        if(it->id == node->terms.at(2).value){
            exist = true;
            fun = *it;
            break;
        }
    }
    if(!exist){
        return false;
    }
    param.tmpText.back() += "\tjal\t" + node->terms.at(2).value + "\n";
    stringstream ss;
    ss << "$t" <<regCount;
    ++regCount;
    param.tmpText.back() += "\tmove\t" + ss.str() + ",\t$v0\n";
    Variable var;
    var.id = ss.str();
    var.type = REGISTER;
    var.unitSize = fun.unitSize;
    param.dataStack.push_back(var);
    return true;
}
bool pro52(ASTNode *, GenParam &param){
    param.tmpText.back() += "\taddi\t$sp,\t$sp,\t-4\n";
    param.spLasts.push_back(spTop);
    spTop = 0;
	return true;
}
bool gen53(ASTNode *node, GenParam &param){
    string &codeSeg = param.tmpText.back();
    stringstream ss;
    ss << "$t" <<regCount;
    codeSeg += "\tli\t" + ss.str() + ",\t" + node->terms.at(0).value + "\n";
    ++regCount;
    Variable newReg;
    newReg.id = ss.str();
    newReg.unitSize = 4;
    newReg.type = REGISTER;
    param.dataStack.push_back(newReg);
	return true;
}
bool pro53(ASTNode *, GenParam &){
	return true;
}
bool gen54(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro54(ASTNode *, GenParam &){
	return true;
}
bool gen55(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro55(ASTNode *, GenParam &){
	return true;
}
bool gen56(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro56(ASTNode *, GenParam &param){
    Variable &data = param.dataStack.back();
    stringstream ss;
    switch (data.type) {
        case GLOBALVAR:
        case GLOBALREF:
            ss << "$t" << regCount;
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + ss.str() + ",\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + ss.str() + ",\t" + data.id + "\n";
            }
            ++regCount;
            data.id = ss.str();
        case REGISTER:
            break;
        case LOCALVAR:
        case LOCALREF:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t" + data.id + ",\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t" + data.id + ",\t" + data.id + "\n";
            }
            break;
        default:
            return false;
            break;
    }
    data.type = REGISTER;
	return true;
}
bool gen57(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro57(ASTNode *, GenParam &){
	return true;
}
bool gen58(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro58(ASTNode *, GenParam &){
	return true;
}
bool gen59(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro59(ASTNode *, GenParam &){
	return true;
}
bool gen60(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro60(ASTNode *, GenParam &){
	return true;
}
bool gen61(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro61(ASTNode *, GenParam &){
	return true;
}
bool gen62(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro62(ASTNode *, GenParam &){
	return true;
}
bool gen63(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro63(ASTNode *, GenParam &){
	return true;
}
bool gen64(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro64(ASTNode *, GenParam &){
	return true;
}
bool gen65(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro65(ASTNode *, GenParam &){
	return true;
}
bool gen66(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro66(ASTNode *, GenParam &){
	return true;
}
bool gen67(ASTNode *node, GenParam &){
    node->parent->terms.push_back(node->terms.at(0));
	return true;
}
bool pro67(ASTNode *, GenParam &param){
    Variable data = param.dataStack.back();
    // Load data
    switch (data.type) {
        case LOCALVAR:
            data.id = "0(" + data.id + ")";
        case GLOBALVAR:
            if(data.unitSize == 4){
                param.tmpText.back() += "\tlw\t$t8,\t" + data.id + "\n";
            }else{
                param.tmpText.back() += "\tlb\t$t8,\t" + data.id + "\n";
            }
            break;
        case LOCALREF:
            data.id = "0(" + data.id + ")";
        case GLOBALREF:
            param.tmpText.back() += "\tla\t$t8,\t" + data.id + "\n";
            break;
        case REGISTER:
            param.tmpText.back() += "\tmove\t$t8,\t" + data.id + "\n";
            break;
        default:
            return false;
            break;
    }
    param.tmpText.back() += "\taddi\t$sp,\t$sp,\t-4\n";
    param.tmpText.back() += "\tsw\t$t8,\t0($sp)\n";
	return true;
}
bool gen68(ASTNode *node, GenParam &param){
    Variable fun;
    // FunList
    bool exist = false;
    for(vector<Variable>::iterator it=param.funList.begin(); it!=param.funList.end(); ++it){
        if(it->id == node->terms.at(2).value){
            exist = true;
            fun = *it;
            break;
        }
    }
    if(!exist){
        return false;
    }
    param.tmpText.back() += "\tjal\t" + node->terms.at(2).value + "\n";
    stringstream ss;
    ss << "$t" <<regCount;
    ++regCount;
    param.tmpText.back() += "\tmove\t" + ss.str() + ",\t$v0\n";
    Variable var;
    var.id = ss.str();
    var.type = REGISTER;
    var.unitSize = fun.unitSize;
    param.dataStack.push_back(var);
    return true;
}
bool pro68(ASTNode *, GenParam &){
    return true;
}
