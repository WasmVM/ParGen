#include <luison.hpp>

vector<Rule> rules;
vector<string> terms,nonTerms;
vector<State> states;
vector<FirstPair> firsts, follows;
vector<TableItem> *gotoTable = NULL, *actionTable = NULL;

void putTok(string str, vector<string> &tokens){
	bool exist = false;
	for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it){
		if(*it == str){
			exist = true;
			break;
		}
	}
	if(!exist){
		tokens.push_back(str);
	}
}
int checkState(RulePair pair){
	for(vector<State>::iterator i = states.begin(); i != states.end(); ++i){
		for(vector<RulePair>::iterator j = i->rules.begin(); j != i->rules.end(); ++j){
			if((j->rule == pair.rule) && (j->offset == pair.offset)){
				return i - states.begin();
			}
		}
	}
	return -1;
}
void putDerive(Rule rule, vector<RulePair> &derives){
    bool exist = false;
    for(vector<RulePair>::iterator it = derives.begin(); it != derives.end(); ++it){
        if(it->rule == rule){
            exist = true;
            break;
        }
    }
    if(!exist){
        RulePair newDerive;
        newDerive.rule = rule;
        newDerive.offset = 0;
        derives.push_back(newDerive);
        for(vector<Rule>::iterator rl = rules.begin(); rl!=rules.end(); ++rl){
            if(rl->target == rule.parts.at(0)){
                putDerive(*rl,derives);
            }
        }
    }
}
bool isTerm(string str){
    for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
        if(*it == str){
            return true;
        }
    }
    return false;
}
void putFirst(Rule rule, int iTarget){
    if(isTerm(rule.parts.at(0))){
        bool exists = false;
        for(vector<string>::iterator it=firsts.at(iTarget).items.begin(); it!=firsts.at(iTarget).items.end(); ++it){
            if(*it == rule.parts.at(0)){
                exists = true;
                break;
            }
        }
        if(!exists){
            firsts.at(iTarget).items.push_back(rule.parts.at(0));
        }
    }else{
        for(vector<Rule>::iterator it = rules.begin(); it != rules.end(); ++it){
            if(it->target == rule.parts.at(0)){
                putFirst(*it, iTarget);
            }
        }
    }
}
vector<string> *getFirst(string target){
    for(vector<FirstPair>::iterator it=firsts.begin(); it!=firsts.end(); ++it){
        if(it->target == target){
            return &(it->items);
        }
    }
    return NULL;
}
vector<string> *getFollow(string target){
    for(vector<FirstPair>::iterator it=follows.begin(); it!=follows.end(); ++it){
        if(it->target == target){
            return &(it->items);
        }
    }
    return NULL;
}
unsigned int getIndex(string target, vector<string> &list){
    unsigned int i = 0;
    for(vector<string>::iterator it=list.begin(); it!=list.end(); ++it, ++i){
        if(*it == target){
            break;
        }
    }
    return i;
}
void insertItem(string target, TableItem item){
    unsigned int index;
    if(isTerm(target)){
        index = getIndex(target,terms);
        for(vector<TableItem>::iterator it=actionTable[index].begin(); it!=actionTable[index].end(); ++it){
            if(*it == item){
                return;
            }
            if((it->state == item.state) && (it->val != item.val)){
                cout << "Term " << target << " conflict at state " << item.state << endl;
            }
        }
        actionTable[index].push_back(item);
    }else{
        index = getIndex(target,nonTerms);
        for(vector<TableItem>::iterator it=gotoTable[index].begin(); it!=gotoTable[index].end(); ++it){
            if(*it == item){
                return;
            }
            if(it->state == item.state){
                cout << "Nonterm " << target << " conflict at state " << item.state << endl;
            }
        }
        gotoTable[index].push_back(item);
    }

}
void reduceRule(string target, TableItem item){
    vector<string> *followList = getFollow(target);
    if(!followList){
        return;
    }
    for(vector<string>::iterator it=followList->begin(); it!=followList->end(); ++it){
        insertItem(*it,item);
    }
}

int main(int argc, char *argv[]){
	// Check file
	argc--;
	if(argc < 1){
		cout << "沒有輸入檔案" << endl;
		return 1;
	}
	// Read rules
	ifstream fin(argv[1]);
	while(!fin.eof()){
		string line;
		getline(fin,line);
		stringstream ss(line);
		Rule newRule;
		string arrow;
		ss >> newRule.target;
		putTok(newRule.target,terms);
		ss >> arrow;
		while(!ss.eof()){
			string part;
			ss >> part;
			newRule.parts.push_back(part);
			putTok(part,terms);
		}
		rules.push_back(newRule);
	}	
	fin.close();
	// Remove non-terminals
	for(vector<Rule>::iterator it = rules.begin(); it != rules.end(); ++it){
		for(vector<string>::iterator it1 = terms.begin(); it1 != terms.end(); ++it1){
			if(it->target == *it1){
                nonTerms.push_back(*it1);
				terms.erase(it1);
				break;
			}
		}
	}
    // Add super rule, end term
	{
		Rule suRule;
		suRule.target = "SUPER";
		suRule.parts.push_back(rules.at(0).target);
		suRule.parts.push_back("END");
		rules.insert(rules.begin(),suRule);
		terms.push_back("END");
		rules.erase(rules.end());
	}
    // Expand states
	for(vector<Rule>::iterator it = rules.begin(); it != rules.end(); ++it){
        for(unsigned int i=1; i<=it->parts.size(); ++i){
            RulePair newPair;
            newPair.rule = *it;
            newPair.offset = i;
            if((newPair.rule.parts.back() == "END")&&(i==it->parts.size())){
                newPair.action = ACCEPT;
            }
            State newState;
            newState.rules.push_back(newPair);
            states.push_back(newState);
		}
	}
    // Add super state
    {
        State suState;
        RulePair suPair;
        suPair.rule = rules.front();
        suPair.offset = 0;
        suState.rules.push_back(suPair);
        states.insert(states.begin(),suState);
    }
    // Merge states
    for(vector<State>::iterator it = states.begin(); it != states.end(); ++it){
        for(vector<State>::iterator cur = it+1; cur != states.end();){
            if(cur->rules.at(0).offset != it->rules.at(0).offset){
                ++cur;
                continue;
            }
            unsigned int offset = cur->rules.at(0).offset;
            vector<string> &curPart = cur->rules.at(0).rule.parts;
            vector<string> &itPart = it->rules.at(0).rule.parts;
            bool canMerge = true;// (it->rules.at(0).rule.target == cur->rules.at(0).rule.target);
            for(unsigned int i=0; i<offset; ++i){
                if(curPart.at(i) != itPart.at(i)){
                    canMerge = false;
                    break;
                }
            }
            if(canMerge && (offset != 0)){
                for(vector<RulePair>::iterator ru = cur->rules.begin(); ru!=cur->rules.end(); ++ru){
                    it->rules.push_back(*ru);
                }
                states.erase(cur);
            }else{
                ++cur;
            }
        }
    }
    // Pick derives
    for(vector<State>::iterator it = states.begin(); it != states.end(); ++it){
        unsigned int offset = it->rules.at(0).offset;
        for(vector<RulePair>::iterator ru = it->rules.begin(); ru!=it->rules.end(); ++ru){
            if(offset >= ru->rule.parts.size()){
                continue;
            }
            // Put rule derive
            string part = ru->rule.parts.at(offset);
            for(vector<Rule>::iterator rl = rules.begin(); rl!=rules.end(); ++rl){
                if(rl->target == part){
                    putDerive(*rl,it->derives);
                }
            }
        }
    }
    // Link and reduce
    for(unsigned int i=0; i<states.size(); ++i){
        // Rule
        unsigned int offset = states.at(i).rules.at(0).offset;
        for(vector<RulePair>::iterator ru = states.at(i).rules.begin(); ru!=states.at(i).rules.end(); ++ru){
            if((offset >= ru->rule.parts.size())&&(ru->action == NONE)){
                for(unsigned int j=0; j<rules.size(); ++j){
                    if(rules.at(j) == ru->rule){
                        ru->action = REDUCE;
                        ru->actVal = j;
                        break;
                    }
                }
                continue;
            }
            for(unsigned int j=0; j<states.size(); ++j){
                if(i == j)continue;
                bool exists = false;
                for(vector<RulePair>::iterator rl = states.at(j).rules.begin(); rl!=states.at(j).rules.end(); ++rl){
                    RulePair cmpRul = *ru;
                    ++cmpRul.offset;
                    if(*rl == cmpRul){
                        ru->action = SHIFT;
                        ru->actVal = j;
                        exists = true;
                        break;
                    }
                }
                if(exists){
                    break;
                }
            }
        }
        // Derive
        for(vector<RulePair>::iterator ru = states.at(i).derives.begin(); ru!=states.at(i).derives.end(); ++ru){
            if(ru->offset >= ru->rule.parts.size()){
                continue;
            }
            for(unsigned int j=0; j<states.size(); ++j){
                bool exists = false;
                for(vector<RulePair>::iterator rl = states.at(j).rules.begin(); rl!=states.at(j).rules.end(); ++rl){
                    RulePair cmpRul = *ru;
                    ++cmpRul.offset;
                    if(*rl == cmpRul){
                        ru->action = SHIFT;
                        ru->actVal = j;
                        exists = true;
                        break;
                    }
                }
                if(exists){
                    break;
                }
            }
        }
    }
    // Create first
    for(vector<Rule>::iterator it = rules.begin(); it != rules.end(); ++it){
        unsigned int iTarget = 0;
        bool exists = false;
        for(; iTarget < firsts.size(); ++iTarget){
            if(firsts.at(iTarget).target == it->target){
                exists = true;
                break;
            }
        }
        if(!exists){
            FirstPair newTarget;
            newTarget.target = it->target;
            firsts.push_back(newTarget);
        }
        putFirst(*it, iTarget);
    }
    firsts.erase(firsts.begin());
    // Create follow
    for(vector<FirstPair>::iterator it = firsts.begin(); it != firsts.end(); ++it){
        string target = it->target;
        follows.push_back(FirstPair());
        follows.back().target = target;
        for(vector<Rule>::iterator it1 = rules.begin(); it1 != rules.end(); ++it1){
            for(unsigned int i=0; i < it1->parts.size(); ++i){
                if((it1->parts.at(i) == target) && (i < it1->parts.size()-1)){
                    string insertTar = it1->parts.at(i+1);
                    if(isTerm(insertTar)){
                        bool exists = false;
                        for(vector<string>::iterator it2=follows.back().items.begin(); it2!=follows.back().items.end(); ++it2){
                            if(*it2 == insertTar){
                                exists = true;
                                break;
                            }
                        }
                        if(!exists){
                            follows.back().items.push_back(insertTar);
                        }
                    }else{
                        vector<string> *myfirst = getFirst(insertTar);
                        if(myfirst){
                            for(unsigned int j=0; j<myfirst->size(); ++j){
                                bool exists = false;
                                for(vector<string>::iterator it2=follows.back().items.begin(); it2!=follows.back().items.end(); ++it2){
                                    if(*it2 == myfirst->at(j)){
                                        exists = true;
                                        break;
                                    }
                                }
                                if(!exists){
                                    follows.back().items.push_back(myfirst->at(j));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Merge follow
    bool stable = false;
    while(!stable){
        stable = true;
        for(vector<FirstPair>::iterator it = follows.begin(); it != follows.end(); ++it){
            string target = it->target;
            for(vector<Rule>::iterator it1 = rules.begin(); it1 != rules.end(); ++it1){
                if(it1->parts.back() == target){
                    vector<string> *myfollow = getFollow(it1->target);
                    if(myfollow){
                        for(unsigned int j=0; j<myfollow->size(); ++j){
                            bool exists = false;
                            for(vector<string>::iterator it2=it->items.begin(); it2!=it->items.end(); ++it2){
                                if(*it2 == myfollow->at(j)){
                                    exists = true;
                                    break;
                                }
                            }
                            if(!exists){
                                it->items.push_back(myfollow->at(j));
                                stable = false;
                            }
                        }
                    }
                }
            }
        }
    }
    // Init tables
    gotoTable = new vector<TableItem>[nonTerms.size()];
    actionTable = new vector<TableItem>[terms.size()];
    // Generate parsing table
    {
        unsigned int i=0;
        for(vector<State>::iterator it = states.begin(); it != states.end(); ++it, ++i){
            // Rule
            for(vector<RulePair>::iterator ri = it->rules.begin(); ri!=it->rules.end(); ++ri){
                TableItem newItem;
                newItem.state = i;
                newItem.action = ri->action;
                newItem.val = ri->actVal;
                string target;
                switch(ri->action){
                    case SHIFT:
                        target = ri->rule.parts.at(ri->offset);
                        insertItem(target, newItem);
                    break;
                    case ACCEPT:
                        insertItem("END", newItem);
                    break;
                    case REDUCE:
                        reduceRule(ri->rule.target,newItem);
                    break;
                    default:
                    break;
                }
            }
            // Derive
            for(vector<RulePair>::iterator di = it->derives.begin(); di!=it->derives.end(); ++di){
                TableItem newItem;
                newItem.state = i;
                newItem.action = di->action;
                newItem.val = di->actVal;
                switch(di->action){
                    case SHIFT:
                        insertItem(di->rule.parts.at(0), newItem);
                    break;
                    default:
                    break;
                }
            }
        }
    }
    // Generate parser
    {
        ofstream fout("parserFunc.cpp");
        ofstream hout("parserFunc.hpp");
        // Prologue
        fout << "#include <parserFunc.hpp>\n"
                "void shift(ParserParam &param, Token *tok, int state){\n"
                "\tparam.symbols->push_back(tok);\n"
                "\tparam.tokens->pop_front();\n"
                "\tparam.stack.push_back(state);\n"
                "}"
             << endl;
        hout << "#ifndef PARSERFUNC_HPP\n#define PARSERFUNC_HPP\n"
                "#include <ruleFunc.hpp>\n"
                "using namespace std;\n"
                "void shift(ParserParam &param, Token *tok, int state);"
             << endl;
        // Content
        for(unsigned int i=0; i<terms.size(); ++i){
            fout << "bool func" << terms.at(i) << "(ParserParam &param, Token *tok){\n"
                    "\tswitch(param.stack.back()){"<<endl;
            hout << "bool func" << terms.at(i) << "(ParserParam &param, Token *tok);" << endl;
            for(vector<TableItem>::iterator it=actionTable[i].begin(); it!=actionTable[i].end(); ++it){
                fout << "\t\tcase " << it->state << ":\n";
                switch(it->action){
                case SHIFT:
                    fout << "\t\t\tshift(param,tok," << it->val << ");\n";
                    fout << "\t\t\tbreak;" << endl;
                    break;
                case REDUCE:
                    fout << "\t\t\tif(!rule" << it->val << "(param)) return false;\n";
                    fout << "\t\t\tbreak;" << endl;
                    break;
                case ACCEPT:
                    fout << "\t\t\tparam.isAccept = true;\n";
                    fout << "\t\t\tbreak;" << endl;
                default:
                    break;
                }
            }
            fout << "\t\tdefault:\n\t\t\treturn false;\n\t\tbreak;\n\t}\n\treturn true;\n}"<<endl;
        }
        // Epilogue
        hout << "#endif" << endl;
        fout.close();
        hout.close();
    }
    // Generate rule
    {
        ofstream fout("ruleFunc.cpp");
        ofstream hout("ruleFunc.hpp");
        // Prologue
        fout << "#include <ruleFunc.hpp>\n"
                "bool reduce(ParserParam &param, TokenType target, TokenType *parts, int partSize, int ruleNo){\n"
                "\tASTNode *newNode = new ASTNode;\n"
                "\tnewNode->ruleNo = ruleNo;\n"
                "\tToken *symbolEnd = param.symbols->back();\n"
                "\tnewNode->type = target;\n"
                "\tfor(int i=partSize-1; i>=0; --i){\n"
                "\t\tif(symbolEnd->type != parts[i]){\n"
                "\t\t\treturn false;\n"
                "\t\t}else{\n"
                "\t\t\tif(isTerm(symbolEnd->type)){\n"
                "\t\t\t\tnewNode->terms.push_back(*symbolEnd);\n"
                "\t\t\t}else{\n"
                "\t\t\t\tnewNode->derives.push_front(param.astStack.back());\n"
                "\t\t\t\tparam.astStack.pop_back();\n"
                "\t\t\t}\n"
                "\t\t\tdelete symbolEnd;\n"
                "\t\t\tparam.symbols->pop_back();\n"
                "\t\t\tparam.stack.pop_back();\n"
                "\t\t\tsymbolEnd = param.symbols->back();\n"
                "\t\t}\n\t}\n"
                "\tparam.astStack.push_back(newNode);\n"
                "\tToken *newTok = new Token;\n"
                "\tnewTok->type = target;\n"
                "\tparam.symbols->push_back(newTok);\n"
                "\tdelete [] parts;\n"
                "\tif(parserGoto(param)){\n"
                "\t\treturn true;\n"
                "\t}else{\n"
                "\t\treturn false;\n"
                "\t}\n}"
             << endl;
        hout << "#ifndef RULEFUNC_HPP\n"
                "#define RULEFUNC_HPP\n"
                "#include <iostream>\n"
                "#include <lex.hpp>\n"
                "bool isTerm(TokenType tok);\n"
                "bool reduce(ParserParam &param, TokenType target, TokenType *parts, int partSize, int ruleNo);\n"
                "bool parserGoto(ParserParam &param);"
             << endl;
        // Term
        {
            fout << "bool isTerm(TokenType tok){\n"
                    "\tswitch(tok){"
                 << endl;
            for(vector<string>::iterator it=terms.begin(); it!=terms.end(); ++it){
                fout << "\t\tcase "<< *it << ":" << endl;
            }
            fout << "\t\t\treturn true;\n"
                    "\t\tbreak;\n"
                    "\t\tdefault:\n"
                    "\t\t\treturn false;\n"
                    "\t\tbreak;\n\t}\n}"
                 << endl;
        }
        // Goto
        {
            // Prologue
            fout << "bool parserGoto(ParserParam &param){\n"
                    "\tint state = param.stack.back(), nextState;\n"
                    "\tswitch(param.symbols->back()->type){"
                 << endl;
            for(unsigned int i=0; i<nonTerms.size()-1; ++i){
                fout << "\t\tcase " << nonTerms.at(i) << ":\n"
                        "\t\t\tswitch(state){"
                     << endl;
                for(vector<TableItem>::iterator it=gotoTable[i].begin(); it!=gotoTable[i].end(); ++it){
                    fout << "\t\t\t\tcase " << it->state << ":" << endl;
                    fout << "\t\t\t\t\tnextState = " << it->val << ";" <<endl;
                    fout << "\t\t\t\tbreak;"<< endl;
                }
                fout << "\t\t\t\tdefault:\n"
                        "\t\t\t\t\treturn false;\n"
                        "\t\t\t}\n"
                        "\t\tbreak;"
                     << endl;
            }
            // Epilogue
            fout << "\t\tdefault:\n"
                    "\t\t\treturn false;\n"
                    "\t}\n"
                    "\tparam.stack.push_back(nextState);\n"
                    "\treturn true;\n"
                    "}"
                 << endl;
        }
        // Rule
        {
            for(unsigned int i=1; i<rules.size(); ++i){
                fout << "bool rule"<< i << "(ParserParam &param){" << endl;
                hout << "bool rule"<< i << "(ParserParam &param);" << endl;
                fout << "\tTokenType *parts = new TokenType[" << rules.at(i).parts.size() << "];" << endl;
                for(unsigned int j=0; j<rules.at(i).parts.size(); ++j){
                    fout << "\tparts[" << j << "] = " << rules.at(i).parts.at(j) << ";" << endl;
                }
                fout << "\treturn reduce(param, " << rules.at(i).target << ", parts, " << rules.at(i).parts.size() << ", "<< i << ");\n}" << endl;
            }
        }
        // Epilogue
        hout << "#endif" << endl;
        fout.close();
        hout.close();
    }
    // Generate codegen file
    {
        ofstream fout("genFunc.cpp");
        ofstream hout("genFunc.hpp");
        // Prologue
        fout << "#include <genFunc.hpp>" << endl;
        hout << "#ifndef GENFUNC_HPP\n"
                "#define GENFUNC_HPP\n"
                "#include <general.hpp>"
             << endl;
        // Function
        for(unsigned int i=1; i<rules.size(); ++i){
            fout << "bool gen" << i << "(ASTNode *, GenParam &){\n}" << endl;
            fout << "bool pro" << i << "(ASTNode *, GenParam &){\n}" << endl;
            hout << "bool gen" << i << "(ASTNode *, GenParam &);" << endl;
            hout << "bool pro" << i << "(ASTNode *, GenParam &);" << endl;
        }
        // Function table
        hout << "#define GENTABLE bool (*funcTable[" << rules.size()-1 << "])(ASTNode *, GenParam &)={";
        for(unsigned int i=1; i<rules.size(); ++i){
            hout << "gen" << i;
            if(i < rules.size()-1){
                hout << ",";
            }
        }
        hout <<"};" << endl;
        hout << "#define PROTABLE bool (*proTable[" << rules.size()-1 << "])(ASTNode *, GenParam &)={";
        for(unsigned int i=1; i<rules.size(); ++i){
            hout << "pro" << i;
            if(i < rules.size()-1){
                hout << ",";
            }
        }

        // Epilogue
        hout << "};\n"
             << "#endif"
             << endl;
        fout.close();
        hout.close();
    }
    // Print states
    {
        ofstream fout("States.txt");
        int i=0;
        for(vector<State>::iterator it = states.begin(); it != states.end(); ++it, ++i){
            fout << i << ":" << endl;
            for(vector<RulePair>::iterator ru = it->rules.begin(); ru != it->rules.end(); ++ru){
                fout << "\t" << ru->rule.target << " -> ";
                unsigned int j=0;
                for(;j<ru->rule.parts.size() ; ++j){
                    if(j==ru->offset){
                        fout << "@ ";
                    }
                    fout<< ru->rule.parts.at(j) <<" ";
                }
                if(j==ru->offset){
                    fout << "@ ";
                }
                fout << "--- Action: ";
                switch (ru->action) {
                case SHIFT:
                    fout << "SHIFT Value: " << ru->actVal;
                    break;
                case REDUCE:
                    fout << "REDUCE " << ru->actVal;
                    break;
                case NONE:
                    fout << "NONE ";
                    break;
                case ACCEPT:
                    fout << "ACCEPT ";
                    break;
                }
                fout << endl;
            }
            if(it->derives.size() > 0){
                fout << "\t*** derives ***" <<endl;
            }
            for(vector<RulePair>::iterator ru = it->derives.begin(); ru != it->derives.end(); ++ru){
                fout << "\t" << ru->rule.target << " -> ";
                unsigned int j=0;
                for(;j<ru->rule.parts.size() ; ++j){
                    if(j==ru->offset){
                        fout << "@ ";
                    }
                    fout<< ru->rule.parts.at(j) <<" ";
                }
                if(j==ru->offset){
                    fout << "@ ";
                }
                fout << "--- Action: ";
                switch (ru->action) {
                case SHIFT:
                    fout << "SHIFT Value: " << ru->actVal;
                    break;
                case REDUCE:
                    fout << "REDUCE " << ru->actVal;
                    break;
                case NONE:
                    fout << "NONE ";
                    break;
                case ACCEPT:
                    fout << "ACCEPT ";
                    break;
                }
                fout << endl;
            }
        }
        fout.close();
    }
    // Print follows
    {
        ofstream fout("Follows.txt");
        for(vector<FirstPair>::iterator it = follows.begin(); it != follows.end(); ++it){
            fout << it->target << ":" << endl;
            fout << "\t";
            for(vector<string>::iterator fi = it->items.begin(); fi != it->items.end(); ++fi){
                fout << *fi << " ";
            }
            fout << endl;
        }
        fout.close();
    }
    return 0;
}
