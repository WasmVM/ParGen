#include <parser.hpp>

Parser::Parser(list<Token *> *tokens)
{
	param.tokens = tokens;
	param.symbols = new list<Token *>;
	param.isAccept = false;
}

void Parser::parse(){
	// Add end token
	Token *tok = new Token;
	tok->type = END;
	tok->value = "$";
	param.tokens->push_back(tok);
	// Add 0 state
	param.stack.push_back(0);
	// Parse
	while((param.tokens->size() > 0) && (!param.isAccept)){
		Token *token = param.tokens->front();
		switch(token->type){
			case INT:
				if(!funcINT(param,token))
					return;
			break;
			case CHAR:
				if(!funcCHAR(param,token))
					return;
			break;
			case ID:
				if(!funcID(param,token))
					return;
			break;
			case SEMI:
				if(!funcSEMI(param,token))
					return;
			break;
			case BRAC_ML:
				if(!funcBRAC_ML(param,token))
					return;
			break;
			case BRAC_SL:
				if(!funcBRAC_SL(param,token))
					return;
			break;
			case COMMA:
				if(!funcCOMMA(param,token))
					return;
			break;
			case BRAC_LL:
				if(!funcBRAC_LL(param,token))
					return;
			break;
			case MINUS:
				if(!funcMINUS(param,token))
					return;
			break;
			case OOPS:
				if(!funcOOPS(param,token))
					return;
			break;
			case NUM:
				if(!funcNUM(param,token))
					return;
			break;
			case BREAK:
				if(!funcBREAK(param,token))
					return;
			break;
			case IF:
				if(!funcIF(param,token))
					return;
			break;
			case ELSE:
				if(!funcELSE(param,token))
					return;
			break;
			case WHILE:
				if(!funcWHILE(param,token))
					return;
			break;
			case PRINT:
				if(!funcPRINT(param,token))
					return;
			break;
			case READ:
				if(!funcREAD(param,token))
					return;
			break;
			case RET:
				if(!funcRET(param,token))
					return;
			break;
			case ASSI:
				if(!funcASSI(param,token))
					return;
			break;
			case PLUS:
				if(!funcPLUS(param,token))
					return;
			break;
			case MULT:
				if(!funcMULT(param,token))
					return;
			break;
			case DIVI:
				if(!funcDIVI(param,token))
					return;
			break;
			case EQUA:
				if(!funcEQUA(param,token))
					return;
			break;
			case NEQU:
				if(!funcNEQU(param,token))
					return;
			break;
			case LSTH:
				if(!funcLSTH(param,token))
					return;
			break;
			case LSEQ:
				if(!funcLSEQ(param,token))
					return;
			break;
			case GREA:
				if(!funcGREA(param,token))
					return;
			break;
			case GREQ:
				if(!funcGREQ(param,token))
					return;
			break;
			case AND:
				if(!funcAND(param,token))
					return;
			break;
			case OR:
				if(!funcOR(param,token))
					return;
			break;
			case BRAC_MR:
				if(!funcBRAC_MR(param,token))
					return;
			break;
			case BRAC_SR:
				if(!funcBRAC_SR(param,token))
					return;
			break;
			case BRAC_LR:
				if(!funcBRAC_LR(param,token))
					return;
			break;
			case END:
				if(!funcEND(param,token))
					return;
			break;
		}
	}
}
