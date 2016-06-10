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
            symbolEnd = param.symbols->back();
		}
	}
	Token *newTok = new Token;
	newTok->type = target;
	param.symbols->push_back(newTok);
	delete [] parts;
	if(parserGoto(param)){
		return true;
	}else{
		return false;
	}
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
			parts = new TokenType[2]; parts[0] = DL_; parts[1] = DL;
			reduce(param, DL, parts,2);
		break;
		case 8:
			parts = new TokenType[1]; parts[0] = VD_;
			reduce(param, D, parts,1);
		break;
		case 9:
			parts = new TokenType[1]; parts[0] = SEMI;
			reduce(param, VD_, parts,1);
		break;
		case 11:
			parts = new TokenType[3]; parts[0] = T; parts[1] = ID; parts[2] = D;
			reduce(param, DL_, parts,3);
		break;
		case 12:
			shift(param,tok,6);
		break;
		case 16:
			parts = new TokenType[3]; parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR;
			reduce(param, VD_, parts,3);
		break;
		case 20:
			shift(param,tok,6);
		break;
		case 22:
			shift(param,tok,6);
		break;
		case 24:
			parts = new TokenType[1]; parts[0] = VD;
			reduce(param, VDL, parts,1);
		break;
		case 26:
			parts = new TokenType[2]; parts[0] = VD; parts[1] = VDL;
			reduce(param, VDL, parts,2);
		break;
		case 27:
			parts = new TokenType[3]; parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR;
			reduce(param, B, parts,3);
		break;
		case 28:
			parts = new TokenType[4]; parts[0] = BRAC_SL; parts[1] = PDLT; parts[2] = BRAC_SR; parts[3] = B;
			reduce(param, D, parts,4);
		break;
		case 31:
			parts = new TokenType[3]; parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = B;
			reduce(param, D, parts,3);
		break;
		case 47:
			parts = new TokenType[4]; parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR;
			reduce(param, B, parts,4);
		break;
		case 98:
			parts = new TokenType[3]; parts[0] = T; parts[1] = ID; parts[2] = D;
			reduce(param, VD, parts,3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcCHAR(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 0:
			shift(param,tok,6);
		break;
		case 1:
			shift(param,tok,6);
		break;
		case 3:
			parts = new TokenType[2]; parts[0] = DL_; parts[1] = DL;
			reduce(param, DL, parts,2);
		break;
		case 8:
			parts = new TokenType[1]; parts[0] = VD_;
			reduce(param, D, parts,1);
		break;
		case 9:
			parts = new TokenType[1]; parts[0] = SEMI;
			reduce(param, VD_, parts,1);
		break;
		case 11:
			parts = new TokenType[3]; parts[0] = T; parts[1] = ID; parts[2] = D;
			reduce(param, DL_, parts,3);
		break;
		case 12:
			shift(param,tok,6);
		break;
		case 16:
			parts = new TokenType[3]; parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR;
			reduce(param, VD_, parts,3);
		break;
		case 20:
			shift(param,tok,6);
		break;
		case 22:
			shift(param,tok,6);
		break;
		case 24:
			parts = new TokenType[1]; parts[0] = VD;
			reduce(param, VDL, parts,1);
		break;
		case 26:
			parts = new TokenType[2]; parts[0] = VD; parts[1] = VDL;
			reduce(param, VDL, parts,2);
		break;
		case 27:
			parts = new TokenType[3]; parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR;
			reduce(param, B, parts,3);
		break;
		case 28:
			parts = new TokenType[4]; parts[0] = BRAC_SL; parts[1] = PDLT; parts[2] = BRAC_SR; parts[3] = B;
			reduce(param, D, parts,4);
		break;
		case 31:
			parts = new TokenType[3]; parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = B;
			reduce(param, D, parts,3);
		break;
		case 47:
			parts = new TokenType[4]; parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR;
			reduce(param, B, parts,4);
		break;
		case 98:
			parts = new TokenType[3]; parts[0] = T; parts[1] = ID; parts[2] = D;
			reduce(param, VD, parts,3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcID(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 4:
			shift(param,tok,7);
		break;
		case 5:
			parts = new TokenType[1];parts[0] = CHAR; reduce(param, T, parts, 1);
		break;
		case 6:
			parts = new TokenType[1];parts[0] = INT; reduce(param, T, parts, 1);
		break;
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,73);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 32:
			parts = new TokenType[1];parts[0] = PRINT; reduce(param, PR, parts, 1);
		break;
		case 33:
			parts = new TokenType[1];parts[0] = READ; reduce(param, PR, parts, 1);
		break;
		case 35:
			shift(param,tok,73);
		break;
		case 37:
			shift(param,tok,73);
		break;
		case 39:
			shift(param,tok,73);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 42:
			shift(param,tok,73);
		break;
		case 44:
			shift(param,tok,73);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 57:
			shift(param,tok,58);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 61:
			shift(param,tok,73);
		break;
		case 62:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, UO, parts, 1);
		break;
		case 63:
			parts = new TokenType[1];parts[0] = OOPS; reduce(param, UO, parts, 1);
		break;
		case 64:
			shift(param,tok,73);
		break;
		case 68:
			shift(param,tok,73);
		break;
		case 74:
			shift(param,tok,73);
		break;
		case 76:
			shift(param,tok,73);
		break;
		case 77:
			shift(param,tok,73);
		break;
		case 79:
			shift(param,tok,73);
		break;
		case 82:
			shift(param,tok,73);
		break;
		case 85:
			shift(param,tok,73);
		break;
		case 92:
			shift(param,tok,73);
		break;
		case 93:
			shift(param,tok,73);
		break;
		case 96:
			shift(param,tok,97);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		case 99:
			parts = new TokenType[1];parts[0] = PLUS; reduce(param, BO, parts, 1);
		break;
		case 100:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, BO, parts, 1);
		break;
		case 101:
			parts = new TokenType[1];parts[0] = MULT; reduce(param, BO, parts, 1);
		break;
		case 102:
			parts = new TokenType[1];parts[0] = DIVI; reduce(param, BO, parts, 1);
		break;
		case 103:
			parts = new TokenType[1];parts[0] = EQUA; reduce(param, BO, parts, 1);
		break;
		case 104:
			parts = new TokenType[1];parts[0] = NEQU; reduce(param, BO, parts, 1);
		break;
		case 105:
			parts = new TokenType[1];parts[0] = GREA; reduce(param, BO, parts, 1);
		break;
		case 106:
			parts = new TokenType[1];parts[0] = GREQ; reduce(param, BO, parts, 1);
		break;
		case 107:
			parts = new TokenType[1];parts[0] = LSTH; reduce(param, BO, parts, 1);
		break;
		case 108:
			parts = new TokenType[1];parts[0] = LSEQ; reduce(param, BO, parts, 1);
		break;
		case 109:
			parts = new TokenType[1];parts[0] = AND; reduce(param, BO, parts, 1);
		break;
		case 110:
			parts = new TokenType[1];parts[0] = OR; reduce(param, BO, parts, 1);
		break;
		case 111:
			shift(param,tok,112);
		break;
		default:
			return false;
	}
	return true;
}
bool funcSEMI(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 7:
			shift(param,tok,9);
		break;
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 15:
			shift(param,tok,16);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,60);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,60);
		break;
		case 39:
			shift(param,tok,60);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,60);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 50:
			shift(param,tok,51);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 53:
			shift(param,tok,54);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 55:
			shift(param,tok,56);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 58:
			shift(param,tok,59);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 65:
			parts = new TokenType[1];parts[0] = NUM; reduce(param, E, parts, 1);
		break;
		case 66:
			parts = new TokenType[2];parts[0] = NUM; parts[1] = E_; reduce(param, E, parts, 2);
		break;
		case 67:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, E_, parts, 2);
		break;
		case 70:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; reduce(param, E, parts, 3);
		break;
		case 71:
			parts = new TokenType[2];parts[0] = UO; parts[1] = E; reduce(param, E, parts, 2);
		break;
		case 72:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; parts[3] = E_; reduce(param, E, parts, 4);
		break;
		case 73:
			parts = new TokenType[1];parts[0] = ID; reduce(param, E, parts, 1);
		break;
		case 75:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 78:
			parts = new TokenType[3];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; reduce(param, EIT, parts, 3);
		break;
		case 81:
			parts = new TokenType[2];parts[0] = BRAC_SL; parts[1] = BRAC_SR; reduce(param, EIT, parts, 2);
		break;
		case 83:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = BO; parts[3] = E; reduce(param, EIT, parts, 4);
		break;
		case 84:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; reduce(param, EIT, parts, 3);
		break;
		case 86:
			parts = new TokenType[5];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; parts[3] = BO; parts[4] = E; reduce(param, EIT, parts, 5);
		break;
		case 89:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 90:
			parts = new TokenType[2];parts[0] = ID; parts[1] = EIT; reduce(param, E, parts, 2);
		break;
		case 91:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; parts[3] = EAT; reduce(param, EIT, parts, 4);
		break;
		case 94:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 95:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 97:
			shift(param,tok,9);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBRAC_ML(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 7:
			shift(param,tok,10);
		break;
		case 73:
			shift(param,tok,76);
		break;
		case 97:
			shift(param,tok,10);
		break;
		case 112:
			shift(param,tok,113);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBRAC_SL(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 7:
			shift(param,tok,12);
		break;
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,61);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 34:
			shift(param,tok,35);
		break;
		case 35:
			shift(param,tok,61);
		break;
		case 36:
			shift(param,tok,37);
		break;
		case 37:
			shift(param,tok,61);
		break;
		case 39:
			shift(param,tok,61);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 41:
			shift(param,tok,42);
		break;
		case 42:
			shift(param,tok,61);
		break;
		case 44:
			shift(param,tok,61);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 61:
			shift(param,tok,61);
		break;
		case 62:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, UO, parts, 1);
		break;
		case 63:
			parts = new TokenType[1];parts[0] = OOPS; reduce(param, UO, parts, 1);
		break;
		case 64:
			shift(param,tok,61);
		break;
		case 68:
			shift(param,tok,61);
		break;
		case 73:
			shift(param,tok,77);
		break;
		case 74:
			shift(param,tok,61);
		break;
		case 76:
			shift(param,tok,61);
		break;
		case 77:
			shift(param,tok,61);
		break;
		case 79:
			shift(param,tok,61);
		break;
		case 82:
			shift(param,tok,61);
		break;
		case 85:
			shift(param,tok,61);
		break;
		case 92:
			shift(param,tok,61);
		break;
		case 93:
			shift(param,tok,61);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		case 99:
			parts = new TokenType[1];parts[0] = PLUS; reduce(param, BO, parts, 1);
		break;
		case 100:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, BO, parts, 1);
		break;
		case 101:
			parts = new TokenType[1];parts[0] = MULT; reduce(param, BO, parts, 1);
		break;
		case 102:
			parts = new TokenType[1];parts[0] = DIVI; reduce(param, BO, parts, 1);
		break;
		case 103:
			parts = new TokenType[1];parts[0] = EQUA; reduce(param, BO, parts, 1);
		break;
		case 104:
			parts = new TokenType[1];parts[0] = NEQU; reduce(param, BO, parts, 1);
		break;
		case 105:
			parts = new TokenType[1];parts[0] = GREA; reduce(param, BO, parts, 1);
		break;
		case 106:
			parts = new TokenType[1];parts[0] = GREQ; reduce(param, BO, parts, 1);
		break;
		case 107:
			parts = new TokenType[1];parts[0] = LSTH; reduce(param, BO, parts, 1);
		break;
		case 108:
			parts = new TokenType[1];parts[0] = LSEQ; reduce(param, BO, parts, 1);
		break;
		case 109:
			parts = new TokenType[1];parts[0] = AND; reduce(param, BO, parts, 1);
		break;
		case 110:
			parts = new TokenType[1];parts[0] = OR; reduce(param, BO, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcCOMMA(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 18:
			shift(param,tok,20);
		break;
		case 65:
			parts = new TokenType[1];parts[0] = NUM; reduce(param, E, parts, 1);
		break;
		case 66:
			parts = new TokenType[2];parts[0] = NUM; parts[1] = E_; reduce(param, E, parts, 2);
		break;
		case 67:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, E_, parts, 2);
		break;
		case 70:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; reduce(param, E, parts, 3);
		break;
		case 71:
			parts = new TokenType[2];parts[0] = UO; parts[1] = E; reduce(param, E, parts, 2);
		break;
		case 72:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; parts[3] = E_; reduce(param, E, parts, 4);
		break;
		case 73:
			parts = new TokenType[1];parts[0] = ID; reduce(param, E, parts, 1);
		break;
		case 75:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 78:
			parts = new TokenType[3];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; reduce(param, EIT, parts, 3);
		break;
		case 81:
			parts = new TokenType[2];parts[0] = BRAC_SL; parts[1] = BRAC_SR; reduce(param, EIT, parts, 2);
		break;
		case 83:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = BO; parts[3] = E; reduce(param, EIT, parts, 4);
		break;
		case 84:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; reduce(param, EIT, parts, 3);
		break;
		case 86:
			parts = new TokenType[5];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; parts[3] = BO; parts[4] = E; reduce(param, EIT, parts, 5);
		break;
		case 87:
			shift(param,tok,115);
		break;
		case 89:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 90:
			parts = new TokenType[2];parts[0] = ID; parts[1] = EIT; reduce(param, E, parts, 2);
		break;
		case 91:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; parts[3] = EAT; reduce(param, EIT, parts, 4);
		break;
		case 94:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 95:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 112:
			parts = new TokenType[2];parts[0] = T; parts[1] = ID; reduce(param, PD, parts, 2);
		break;
		case 114:
			parts = new TokenType[4];parts[0] = T; parts[1] = ID; parts[2] = BRAC_ML; parts[3] = BRAC_MR; reduce(param, PD, parts, 4);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBRAC_LL(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 17:
			shift(param,tok,22);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,22);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,22);
		break;
		case 39:
			shift(param,tok,22);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,22);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcMINUS(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,62);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 35:
			shift(param,tok,62);
		break;
		case 37:
			shift(param,tok,62);
		break;
		case 39:
			shift(param,tok,62);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 42:
			shift(param,tok,62);
		break;
		case 44:
			shift(param,tok,62);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 61:
			shift(param,tok,62);
		break;
		case 62:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, UO, parts, 1);
		break;
		case 63:
			parts = new TokenType[1];parts[0] = OOPS; reduce(param, UO, parts, 1);
		break;
		case 64:
			shift(param,tok,62);
		break;
		case 68:
			shift(param,tok,62);
		break;
		case 70:
			shift(param,tok,100);
		break;
		case 73:
			shift(param,tok,100);
		break;
		case 74:
			shift(param,tok,62);
		break;
		case 76:
			shift(param,tok,62);
		break;
		case 77:
			shift(param,tok,62);
		break;
		case 78:
			shift(param,tok,100);
		break;
		case 79:
			shift(param,tok,62);
		break;
		case 81:
			shift(param,tok,100);
		break;
		case 82:
			shift(param,tok,62);
		break;
		case 84:
			shift(param,tok,100);
		break;
		case 85:
			shift(param,tok,62);
		break;
		case 92:
			shift(param,tok,62);
		break;
		case 93:
			shift(param,tok,62);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		case 99:
			parts = new TokenType[1];parts[0] = PLUS; reduce(param, BO, parts, 1);
		break;
		case 100:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, BO, parts, 1);
		break;
		case 101:
			parts = new TokenType[1];parts[0] = MULT; reduce(param, BO, parts, 1);
		break;
		case 102:
			parts = new TokenType[1];parts[0] = DIVI; reduce(param, BO, parts, 1);
		break;
		case 103:
			parts = new TokenType[1];parts[0] = EQUA; reduce(param, BO, parts, 1);
		break;
		case 104:
			parts = new TokenType[1];parts[0] = NEQU; reduce(param, BO, parts, 1);
		break;
		case 105:
			parts = new TokenType[1];parts[0] = GREA; reduce(param, BO, parts, 1);
		break;
		case 106:
			parts = new TokenType[1];parts[0] = GREQ; reduce(param, BO, parts, 1);
		break;
		case 107:
			parts = new TokenType[1];parts[0] = LSTH; reduce(param, BO, parts, 1);
		break;
		case 108:
			parts = new TokenType[1];parts[0] = LSEQ; reduce(param, BO, parts, 1);
		break;
		case 109:
			parts = new TokenType[1];parts[0] = AND; reduce(param, BO, parts, 1);
		break;
		case 110:
			parts = new TokenType[1];parts[0] = OR; reduce(param, BO, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcOOPS(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,63);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 35:
			shift(param,tok,63);
		break;
		case 37:
			shift(param,tok,63);
		break;
		case 39:
			shift(param,tok,63);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 42:
			shift(param,tok,63);
		break;
		case 44:
			shift(param,tok,63);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 61:
			shift(param,tok,63);
		break;
		case 62:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, UO, parts, 1);
		break;
		case 63:
			parts = new TokenType[1];parts[0] = OOPS; reduce(param, UO, parts, 1);
		break;
		case 64:
			shift(param,tok,63);
		break;
		case 68:
			shift(param,tok,63);
		break;
		case 74:
			shift(param,tok,63);
		break;
		case 76:
			shift(param,tok,63);
		break;
		case 77:
			shift(param,tok,63);
		break;
		case 79:
			shift(param,tok,63);
		break;
		case 82:
			shift(param,tok,63);
		break;
		case 85:
			shift(param,tok,63);
		break;
		case 92:
			shift(param,tok,63);
		break;
		case 93:
			shift(param,tok,63);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		case 99:
			parts = new TokenType[1];parts[0] = PLUS; reduce(param, BO, parts, 1);
		break;
		case 100:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, BO, parts, 1);
		break;
		case 101:
			parts = new TokenType[1];parts[0] = MULT; reduce(param, BO, parts, 1);
		break;
		case 102:
			parts = new TokenType[1];parts[0] = DIVI; reduce(param, BO, parts, 1);
		break;
		case 103:
			parts = new TokenType[1];parts[0] = EQUA; reduce(param, BO, parts, 1);
		break;
		case 104:
			parts = new TokenType[1];parts[0] = NEQU; reduce(param, BO, parts, 1);
		break;
		case 105:
			parts = new TokenType[1];parts[0] = GREA; reduce(param, BO, parts, 1);
		break;
		case 106:
			parts = new TokenType[1];parts[0] = GREQ; reduce(param, BO, parts, 1);
		break;
		case 107:
			parts = new TokenType[1];parts[0] = LSTH; reduce(param, BO, parts, 1);
		break;
		case 108:
			parts = new TokenType[1];parts[0] = LSEQ; reduce(param, BO, parts, 1);
		break;
		case 109:
			parts = new TokenType[1];parts[0] = AND; reduce(param, BO, parts, 1);
		break;
		case 110:
			parts = new TokenType[1];parts[0] = OR; reduce(param, BO, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcNUM(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 10:
			shift(param,tok,14);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,65);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 35:
			shift(param,tok,65);
		break;
		case 37:
			shift(param,tok,65);
		break;
		case 39:
			shift(param,tok,65);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 42:
			shift(param,tok,65);
		break;
		case 44:
			shift(param,tok,65);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 61:
			shift(param,tok,65);
		break;
		case 62:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, UO, parts, 1);
		break;
		case 63:
			parts = new TokenType[1];parts[0] = OOPS; reduce(param, UO, parts, 1);
		break;
		case 64:
			shift(param,tok,65);
		break;
		case 65:
			shift(param,tok,65);
		break;
		case 68:
			shift(param,tok,65);
		break;
		case 74:
			shift(param,tok,65);
		break;
		case 76:
			shift(param,tok,65);
		break;
		case 77:
			shift(param,tok,65);
		break;
		case 79:
			shift(param,tok,65);
		break;
		case 82:
			shift(param,tok,65);
		break;
		case 85:
			shift(param,tok,65);
		break;
		case 92:
			shift(param,tok,65);
		break;
		case 93:
			shift(param,tok,65);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		case 99:
			parts = new TokenType[1];parts[0] = PLUS; reduce(param, BO, parts, 1);
		break;
		case 100:
			parts = new TokenType[1];parts[0] = MINUS; reduce(param, BO, parts, 1);
		break;
		case 101:
			parts = new TokenType[1];parts[0] = MULT; reduce(param, BO, parts, 1);
		break;
		case 102:
			parts = new TokenType[1];parts[0] = DIVI; reduce(param, BO, parts, 1);
		break;
		case 103:
			parts = new TokenType[1];parts[0] = EQUA; reduce(param, BO, parts, 1);
		break;
		case 104:
			parts = new TokenType[1];parts[0] = NEQU; reduce(param, BO, parts, 1);
		break;
		case 105:
			parts = new TokenType[1];parts[0] = GREA; reduce(param, BO, parts, 1);
		break;
		case 106:
			parts = new TokenType[1];parts[0] = GREQ; reduce(param, BO, parts, 1);
		break;
		case 107:
			parts = new TokenType[1];parts[0] = LSTH; reduce(param, BO, parts, 1);
		break;
		case 108:
			parts = new TokenType[1];parts[0] = LSEQ; reduce(param, BO, parts, 1);
		break;
		case 109:
			parts = new TokenType[1];parts[0] = AND; reduce(param, BO, parts, 1);
		break;
		case 110:
			parts = new TokenType[1];parts[0] = OR; reduce(param, BO, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBREAK(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,55);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,55);
		break;
		case 39:
			shift(param,tok,55);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,55);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcIF(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,34);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,34);
		break;
		case 39:
			shift(param,tok,34);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,34);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcELSE(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 38:
			shift(param,tok,39);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcWHILE(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,41);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,41);
		break;
		case 39:
			shift(param,tok,41);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,41);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcPRINT(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,32);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,32);
		break;
		case 39:
			shift(param,tok,32);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,32);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcREAD(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,33);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,33);
		break;
		case 39:
			shift(param,tok,33);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,33);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcRET(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 24:
			parts = new TokenType[1];parts[0] = VD; reduce(param, VDL, parts, 1);
		break;
		case 26:
			parts = new TokenType[2];parts[0] = VD; parts[1] = VDL; reduce(param, VDL, parts, 2);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 29:
			shift(param,tok,52);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 37:
			shift(param,tok,52);
		break;
		case 39:
			shift(param,tok,52);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 44:
			shift(param,tok,52);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		case 98:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = VD_; reduce(param, VD, parts, 3);
		break;
		default:
			return false;
	}
	return true;
}
bool funcASSI(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 73:
			shift(param,tok,79);
		break;
		case 78:
			shift(param,tok,93);
		break;
		default:
			return false;
	}
	return true;
}
bool funcPLUS(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,99);
		break;
		case 73:
			shift(param,tok,99);
		break;
		case 78:
			shift(param,tok,99);
		break;
		case 81:
			shift(param,tok,99);
		break;
		case 84:
			shift(param,tok,99);
		break;
		default:
			return false;
	}
	return true;
}
bool funcMULT(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,101);
		break;
		case 73:
			shift(param,tok,101);
		break;
		case 78:
			shift(param,tok,101);
		break;
		case 81:
			shift(param,tok,101);
		break;
		case 84:
			shift(param,tok,101);
		break;
		default:
			return false;
	}
	return true;
}
bool funcDIVI(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,102);
		break;
		case 73:
			shift(param,tok,102);
		break;
		case 78:
			shift(param,tok,102);
		break;
		case 81:
			shift(param,tok,102);
		break;
		case 84:
			shift(param,tok,102);
		break;
		default:
			return false;
	}
	return true;
}
bool funcEQUA(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,103);
		break;
		case 73:
			shift(param,tok,103);
		break;
		case 78:
			shift(param,tok,103);
		break;
		case 81:
			shift(param,tok,103);
		break;
		case 84:
			shift(param,tok,103);
		break;
		default:
			return false;
	}
	return true;
}
bool funcNEQU(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,104);
		break;
		case 73:
			shift(param,tok,104);
		break;
		case 78:
			shift(param,tok,104);
		break;
		case 81:
			shift(param,tok,104);
		break;
		case 84:
			shift(param,tok,104);
		break;
		default:
			return false;
	}
	return true;
}
bool funcLSTH(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,105);
		break;
		case 73:
			shift(param,tok,105);
		break;
		case 78:
			shift(param,tok,105);
		break;
		case 81:
			shift(param,tok,105);
		break;
		case 84:
			shift(param,tok,105);
		break;
		default:
			return false;
	}
	return true;
}
bool funcLSEQ(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,106);
		break;
		case 73:
			shift(param,tok,106);
		break;
		case 78:
			shift(param,tok,106);
		break;
		case 81:
			shift(param,tok,106);
		break;
		case 84:
			shift(param,tok,106);
		break;
		default:
			return false;
	}
	return true;
}
bool funcGREA(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,107);
		break;
		case 73:
			shift(param,tok,107);
		break;
		case 78:
			shift(param,tok,107);
		break;
		case 81:
			shift(param,tok,107);
		break;
		case 84:
			shift(param,tok,107);
		break;
		default:
			return false;
	}
	return true;
}
bool funcGREQ(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,108);
		break;
		case 73:
			shift(param,tok,108);
		break;
		case 78:
			shift(param,tok,108);
		break;
		case 81:
			shift(param,tok,108);
		break;
		case 84:
			shift(param,tok,108);
		break;
		default:
			return false;
	}
	return true;
}
bool funcAND(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,109);
		break;
		case 73:
			shift(param,tok,109);
		break;
		case 78:
			shift(param,tok,109);
		break;
		case 81:
			shift(param,tok,109);
		break;
		case 84:
			shift(param,tok,109);
		break;
		default:
			return false;
	}
	return true;
}
bool funcOR(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 70:
			shift(param,tok,110);
		break;
		case 73:
			shift(param,tok,110);
		break;
		case 78:
			shift(param,tok,110);
		break;
		case 81:
			shift(param,tok,110);
		break;
		case 84:
			shift(param,tok,110);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBRAC_MR(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 65:
			parts = new TokenType[1];parts[0] = NUM; reduce(param, E, parts, 1);
		break;
		case 66:
			parts = new TokenType[2];parts[0] = NUM; parts[1] = E_; reduce(param, E, parts, 2);
		break;
		case 67:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, E_, parts, 2);
		break;
		case 70:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; reduce(param, E, parts, 3);
		break;
		case 71:
			parts = new TokenType[2];parts[0] = UO; parts[1] = E; reduce(param, E, parts, 2);
		break;
		case 72:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; parts[3] = E_; reduce(param, E, parts, 4);
		break;
		case 73:
			parts = new TokenType[1];parts[0] = ID; reduce(param, E, parts, 1);
		break;
		case 75:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 78:
			parts = new TokenType[3];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; reduce(param, EIT, parts, 3);
		break;
		case 81:
			parts = new TokenType[2];parts[0] = BRAC_SL; parts[1] = BRAC_SR; reduce(param, EIT, parts, 2);
		break;
		case 83:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = BO; parts[3] = E; reduce(param, EIT, parts, 4);
		break;
		case 84:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; reduce(param, EIT, parts, 3);
		break;
		case 86:
			parts = new TokenType[5];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; parts[3] = BO; parts[4] = E; reduce(param, EIT, parts, 5);
		break;
		case 89:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 90:
			parts = new TokenType[2];parts[0] = ID; parts[1] = EIT; reduce(param, E, parts, 2);
		break;
		case 91:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; parts[3] = EAT; reduce(param, EIT, parts, 4);
		break;
		case 94:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 95:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 113:
			shift(param,tok,114);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBRAC_SR(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 12:
			shift(param,tok,17);
		break;
		case 13:
			shift(param,tok,23);
		break;
		case 18:
			parts = new TokenType[1];parts[0] = PD; reduce(param, PDLT, parts, 1);
		break;
		case 19:
			parts = new TokenType[2];parts[0] = PD; parts[1] = PDLT_; reduce(param, PDLT, parts, 2);
		break;
		case 21:
			parts = new TokenType[2];parts[0] = COMMA; parts[1] = PDLT; reduce(param, PDLT_, parts, 2);
		break;
		case 43:
			shift(param,tok,44);
		break;
		case 65:
			parts = new TokenType[1];parts[0] = NUM; reduce(param, E, parts, 1);
		break;
		case 66:
			parts = new TokenType[2];parts[0] = NUM; parts[1] = E_; reduce(param, E, parts, 2);
		break;
		case 67:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, E_, parts, 2);
		break;
		case 69:
			shift(param,tok,70);
		break;
		case 70:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; reduce(param, E, parts, 3);
		break;
		case 71:
			parts = new TokenType[2];parts[0] = UO; parts[1] = E; reduce(param, E, parts, 2);
		break;
		case 72:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = E; parts[2] = BRAC_SR; parts[3] = E_; reduce(param, E, parts, 4);
		break;
		case 73:
			parts = new TokenType[1];parts[0] = ID; reduce(param, E, parts, 1);
		break;
		case 75:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 77:
			shift(param,tok,81);
		break;
		case 78:
			parts = new TokenType[3];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; reduce(param, EIT, parts, 3);
		break;
		case 80:
			shift(param,tok,84);
		break;
		case 81:
			parts = new TokenType[2];parts[0] = BRAC_SL; parts[1] = BRAC_SR; reduce(param, EIT, parts, 2);
		break;
		case 83:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = BO; parts[3] = E; reduce(param, EIT, parts, 4);
		break;
		case 84:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; reduce(param, EIT, parts, 3);
		break;
		case 86:
			parts = new TokenType[5];parts[0] = BRAC_SL; parts[1] = ELT; parts[2] = BRAC_SR; parts[3] = BO; parts[4] = E; reduce(param, EIT, parts, 5);
		break;
		case 87:
			parts = new TokenType[1];parts[0] = E; reduce(param, ELT, parts, 1);
		break;
		case 88:
			parts = new TokenType[2];parts[0] = E; parts[1] = ELT_; reduce(param, ELT, parts, 2);
		break;
		case 89:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EIT, parts, 2);
		break;
		case 90:
			parts = new TokenType[2];parts[0] = ID; parts[1] = EIT; reduce(param, E, parts, 2);
		break;
		case 91:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = E; parts[2] = BRAC_MR; parts[3] = EAT; reduce(param, EIT, parts, 4);
		break;
		case 94:
			parts = new TokenType[2];parts[0] = BO; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 95:
			parts = new TokenType[2];parts[0] = ASSI; parts[1] = E; reduce(param, EAT, parts, 2);
		break;
		case 112:
			parts = new TokenType[2];parts[0] = T; parts[1] = ID; reduce(param, PD, parts, 2);
		break;
		case 116:
			parts = new TokenType[2];parts[0] = COMMA; parts[1] = ELT; reduce(param, ELT_, parts, 2);
		break;
		default:
			return false;
	}
	return true;
}
bool funcBRAC_LR(ParserParam &param, Token *tok){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 14:
			shift(param,tok,15);
		break;
		case 25:
			shift(param,tok,27);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 30:
			parts = new TokenType[1];parts[0] = B; reduce(param, S, parts, 1);
		break;
		case 40:
			parts = new TokenType[7];parts[0] = IF; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; parts[5] = ELSE; parts[6] = S; reduce(param, S, parts, 7);
		break;
		case 45:
			parts = new TokenType[5];parts[0] = WHILE; parts[1] = BRAC_SL; parts[2] = E; parts[3] = BRAC_SR; parts[4] = S; reduce(param, S, parts, 5);
		break;
		case 46:
			shift(param,tok,47);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		case 48:
			parts = new TokenType[1];parts[0] = S; reduce(param, SL, parts, 1);
		break;
		case 49:
			parts = new TokenType[2];parts[0] = S; parts[1] = SL; reduce(param, SL, parts, 2);
		break;
		case 51:
			parts = new TokenType[2];parts[0] = E; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 54:
			parts = new TokenType[3];parts[0] = RET; parts[1] = E; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 56:
			parts = new TokenType[2];parts[0] = BREAK; parts[1] = SEMI; reduce(param, S, parts, 2);
		break;
		case 59:
			parts = new TokenType[3];parts[0] = PR; parts[1] = ID; parts[2] = SEMI; reduce(param, S, parts, 3);
		break;
		case 60:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, S, parts, 1);
		break;
		default:
			return false;
	}
	return true;
}
bool funcEND(ParserParam &param, Token *){
	TokenType *parts = NULL;
	switch(param.stack.back()){
		case 1:
			parts = new TokenType[1];parts[0] = DL_; reduce(param, DL, parts, 1);
		break;
		case 2:
			param.isAccept = true;
		break;
		case 3:
			parts = new TokenType[2];parts[0] = DL_; parts[1] = DL; reduce(param, DL, parts, 2);
		break;
		case 8:
			parts = new TokenType[1];parts[0] = VD_; reduce(param, D, parts, 1);
		break;
		case 9:
			parts = new TokenType[1];parts[0] = SEMI; reduce(param, VD_, parts, 1);
		break;
		case 11:
			parts = new TokenType[3];parts[0] = T; parts[1] = ID; parts[2] = D; reduce(param, DL_, parts, 3);
		break;
		case 16:
			parts = new TokenType[4];parts[0] = BRAC_ML; parts[1] = NUM; parts[2] = BRAC_MR; parts[3] = SEMI; reduce(param, VD_, parts, 4);
		break;
		case 27:
			parts = new TokenType[3];parts[0] = BRAC_LL; parts[1] = SL; parts[2] = BRAC_LR; reduce(param, B, parts, 3);
		break;
		case 28:
			parts = new TokenType[4];parts[0] = BRAC_SL; parts[1] = PDLT; parts[2] = BRAC_SR; parts[3] = B; reduce(param, D, parts, 4);
		break;
		case 31:
			parts = new TokenType[3];parts[0] = BRAC_SL; parts[1] = BRAC_SR; parts[2] = B; reduce(param, D, parts, 3);
		break;
		case 47:
			parts = new TokenType[4];parts[0] = BRAC_LL; parts[1] = VDL; parts[2] = SL; parts[3] = BRAC_LR; reduce(param, B, parts, 4);
		break;
		default:
			return false;
	}
	return true;
}

bool parserGoto(ParserParam &param){
	int state = param.stack.back(), nextState;
	switch(param.symbols->back()->type){
		case DL:
			switch(state){
				case 0:
					nextState = 2;
				break;
				case 1:
					nextState = 3;
				break;
				default:
					return false;
			}
		break;
		case DL_:
			switch(state){
				case 0:
				case 1:
					nextState = 1;
				break;
				default:
					return false;
			}
		break;
		case D:
			switch(state){
				case 7:
					nextState = 11;
				break;
				default:
					return false;
			}
		break;
		case VD:
			switch(state){
				case 22:
					nextState = 24;
				break;
				default:
					return false;
			}
		break;
		case VD_:
			switch(state){
				case 7:
					nextState = 8;
				break;
				case 97:
					nextState = 98;
				break;
				default:
					return false;
			}
		break;
		case VDL:
			switch(state){
				case 24:
					nextState = 26;
				break;
				default:
					return false;
			}
		break;
		case PDLT:
			switch(state){
				case 12:
					nextState = 13;
				break;
				case 20:
					nextState = 21;
				break;
				default:
					return false;
			}
		break;
		case PDLT_:
			switch(state){
				case 18:
					nextState = 19;
				break;
				default:
					return false;
			}
		break;
		case PD:
			switch(state){
				case 12:
				case 20:
					nextState = 18;
				break;
				default:
					return false;
			}
		break;
		case B:
			switch(state){
				case 17:
					nextState = 31;
				break;
				case 23:
					nextState = 28;
				break;
				case 29:
				case 37:
				case 39:
				case 44:
					nextState = 30;
				break;
				default:
					return false;
			}
		break;
		case T:
			switch(state){
				case 0:
				case 1:
					nextState = 4;
				break;
				case 12:
				case 20:
					nextState = 111;
				break;
				case 22:
					nextState = 96;
				break;
				default:
					return false;
			}
		break;
		case SL:
			switch(state){
				case 22:
				case 23:
					nextState = 25;
				break;
				case 29:
					nextState = 46;
				break;
				case 48:
					nextState = 49;
				break;
				default:
					return false;
			}
		break;
		case S:
			switch(state){
				case 29:
					nextState = 48;
				break;
				case 37:
					nextState = 38;
				break;
				case 39:
					nextState = 40;
				break;
				case 44:
					nextState = 45;
				break;
				default:
					return false;
			}
		break;
		case E:
			switch(state){
				case 29:
				case 37:
				case 39:
				case 44:
					nextState = 50;
				break;
				case 35:
					nextState = 36;
				break;
				case 42:
					nextState = 43;
				break;
				case 52:
					nextState = 53;
				break;
				case 61:
					nextState = 69;
				break;
				case 64:
					nextState = 71;
				break;
				case 68:
					nextState = 67;
				break;
				case 74:
					nextState = 75;
				break;
				case 76:
					nextState = 78;
				break;
				case 77:
					nextState = 87;
				break;
				case 79:
					nextState = 89;
				break;
				case 82:
					nextState = 83;
				break;
				case 85:
					nextState = 86;
				break;
				case 92:
					nextState = 94;
				break;
				case 93:
					nextState = 95;
				break;
				case 115:
					nextState = 87;
				break;
				default:
					return false;
			}
		break;
		case EIT:
			switch(state){
				case 73:
					nextState = 90;
				break;
				default:
					return false;
			}
		break;
		case EAT:
			switch(state){
				case 78:
					nextState = 91;
				break;
				default:
					return false;
			}
		break;
		case E_:
			switch(state){
				case 65:
					nextState = 66;
				break;
				case 70:
					nextState = 72;
				break;
				default:
					return false;
			}
		break;
		case ELT:
			switch(state){
				case 77:
					nextState = 80;
				break;
				case 115:
					nextState = 116;
				break;
				default:
					return false;
			}
		break;
		case ELT_:
			switch(state){
				case 87:
					nextState = 88;
				break;
				default:
					return false;
			}
		break;
		case UO:
			switch(state){
				case 29:
				case 35:
				case 37:
				case 39:
				case 42:
				case 44:
				case 61:
				case 64:
				case 68:
				case 74:
				case 76:
				case 77:
				case 79:
				case 82:
				case 85:
				case 92:
				case 93:
					nextState = 64;
				break;
				default:
					return false;
			}
		break;
		case BO:
			switch(state){
				case 65:
				case 70:
					nextState = 68;
				break;
				case 73:
					nextState = 74;
				break;
				case 78:
					nextState = 92;
				break;
				case 81:
					nextState = 82;
				break;
				case 84:
					nextState = 85;
				break;
				default:
					return false;
			}
		break;
		case PR:
			switch(state){
				case 29:
				case 37:
				case 39:
				case 44:
					nextState = 57;
				break;
				default:
					return false;
			}
		break;	
		default:
			return false;	
	}
	param.stack.push_back(nextState);
	return true;
}
