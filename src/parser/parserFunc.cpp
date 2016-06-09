#include <parserFunc.hpp>

void shift(ParserParam &param, Token *tok, int state){
	param.symbols->push_back(tok);
	param.tokens->pop_front();
	param.stack.push_back(state);
}

bool reduce(ParserParam &param, TokenType target, TokenType *parts, int partSize){
	Token *symbolEnd = param.symbols->back();
	for(int i=partSize-1; i>=0; --i){
		if(symbolEnd->type != parts[i]){
			return false;
		}else{
			delete symbolEnd;
			param.symbols->pop_back();
			param.stack.pop_back();
		}
	}
	Token *newTok = new Token;
	newTok->type = target;
	param.symbols->push_back(newTok);
	parserGoto(param);
	delete [] parts;
	return true;
}

bool funcINT(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 0:
			shift(param,tok,6);
		break;
		case 1:
			shift(param,tok,6);
		break;
		case 3:
			parts = new TokenType[3]; parts[0] = T; parts[1] = ID; parts[2] = D;
			reduce(param, DL_, parts,3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcCHAR(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcID(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 6:
			parts = new TokenType[1]; parts[0] = INT;
			reduce(param, T, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcSEMI(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBRAC_ML(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBRAC_SL(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcCOMMA(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBRAC_LL(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcMINUS(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcOOPS(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcNUM(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBREAK(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcIF(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcELSE(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcWHILE(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcPRINT(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcREAD(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcRET(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcASSI(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcPLUS(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcMULT(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcDIVI(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcEQUA(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcNEQU(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcLSTH(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcLSEQ(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcGREA(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcGREQ(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcAND(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcOR(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBRAC_MR(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBRAC_SR(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcBRAC_LR(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}
bool funcEND(ParserParam &param, Token *tok){
	param.tokens->pop_front();
	return true;
}

void parserGoto(ParserParam &param){
	
}
