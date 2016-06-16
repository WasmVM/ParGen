#include <ruleFunc.hpp>
bool reduce(ParserParam &param, TokenType target, TokenType *parts, int partSize, int ruleNo){
	ASTNode *newNode = new ASTNode;
	newNode->ruleNo = ruleNo;
	Token *symbolEnd = param.symbols->back();
	newNode->type = target;
	for(int i=partSize-1; i>=0; --i){
		if(symbolEnd->type != parts[i]){
			return false;
		}else{
			if(isTerm(symbolEnd->type)){
				newNode->terms.push_back(*symbolEnd);
			}else{
				param.astStack.back()->parent = newNode;
				newNode->derives.push_front(param.astStack.back());
				param.astStack.pop_back();
			}
			delete symbolEnd;
			param.symbols->pop_back();
			param.stack.pop_back();
			symbolEnd = param.symbols->back();
		}
	}
	param.astStack.push_back(newNode);
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
bool isTerm(TokenType tok){
	switch(tok){
		case ID:
		case SEMI:
		case BRAC_SL:
		case BRAC_SR:
		case COMMA:
		case BRAC_ML:
		case NUM:
		case BRAC_MR:
		case BRAC_LL:
		case BRAC_LR:
		case INT:
		case CHAR:
		case RET:
		case BREAK:
		case IF:
		case ELSE:
		case WHILE:
		case PRINT:
		case READ:
		case MINUS:
		case PLUS:
		case OOPS:
		case MULT:
		case DIVI:
		case EQUA:
		case NEQU:
		case GREA:
		case GREQ:
		case LSTH:
		case LSEQ:
		case AND:
		case OR:
		case ASSI:
		case END:
			return true;
		break;
		default:
			return false;
		break;
	}
}
bool parserGoto(ParserParam &param){
	int state = param.stack.back(), nextState;
	switch(param.symbols->back()->type){
		case DL:
			switch(state){
				case 0:
					nextState = 1;
				break;
				case 3:
					nextState = 4;
				break;
				case 27:
					nextState = 28;
				break;
				default:
					return false;
			}
		break;
		case VD:
			switch(state){
				case 0:
					nextState = 3;
				break;
				case 3:
					nextState = 3;
				break;
				case 27:
					nextState = 3;
				break;
				default:
					return false;
			}
		break;
		case VDL:
			switch(state){
				case 3:
					nextState = 15;
				break;
				default:
					return false;
			}
		break;
		case PDL:
			switch(state){
				case 9:
					nextState = 10;
				break;
				default:
					return false;
			}
		break;
		case PDLT:
			switch(state){
				case 9:
					nextState = 16;
				break;
				case 19:
					nextState = 20;
				break;
				default:
					return false;
			}
		break;
		case PDLT_:
			switch(state){
				case 17:
					nextState = 18;
				break;
				default:
					return false;
			}
		break;
		case PD:
			switch(state){
				case 9:
					nextState = 17;
				break;
				case 19:
					nextState = 17;
				break;
				default:
					return false;
			}
		break;
		case BR:
			switch(state){
				case 6:
					nextState = 8;
				break;
				default:
					return false;
			}
		break;
		case BR_:
			switch(state){
				case 6:
					nextState = 21;
				break;
				default:
					return false;
			}
		break;
		case B:
			switch(state){
				case 11:
					nextState = 12;
				break;
				case 13:
					nextState = 14;
				break;
				case 27:
					nextState = 59;
				break;
				case 28:
					nextState = 59;
				break;
				case 37:
					nextState = 59;
				break;
				case 50:
					nextState = 59;
				break;
				case 52:
					nextState = 59;
				break;
				case 57:
					nextState = 59;
				break;
				default:
					return false;
			}
		break;
		case T:
			switch(state){
				case 0:
					nextState = 5;
				break;
				case 3:
					nextState = 5;
				break;
				case 9:
					nextState = 5;
				break;
				case 19:
					nextState = 5;
				break;
				case 27:
					nextState = 5;
				break;
				default:
					return false;
			}
		break;
		case SL:
			switch(state){
				case 27:
					nextState = 32;
				break;
				case 28:
					nextState = 29;
				break;
				case 37:
					nextState = 38;
				break;
				default:
					return false;
			}
		break;
		case S:
			switch(state){
				case 27:
					nextState = 37;
				break;
				case 28:
					nextState = 37;
				break;
				case 37:
					nextState = 37;
				break;
				case 50:
					nextState = 51;
				break;
				case 52:
					nextState = 53;
				break;
				case 57:
					nextState = 58;
				break;
				default:
					return false;
			}
		break;
		case E:
			switch(state){
				case 27:
					nextState = 40;
				break;
				case 28:
					nextState = 40;
				break;
				case 37:
					nextState = 40;
				break;
				case 42:
					nextState = 43;
				break;
				case 48:
					nextState = 49;
				break;
				case 50:
					nextState = 40;
				break;
				case 52:
					nextState = 40;
				break;
				case 55:
					nextState = 56;
				break;
				case 57:
					nextState = 40;
				break;
				case 67:
					nextState = 68;
				break;
				case 89:
					nextState = 90;
				break;
				case 93:
					nextState = 94;
				break;
				case 96:
					nextState = 97;
				break;
				default:
					return false;
			}
		break;
		case EE:
			switch(state){
				case 27:
					nextState = 66;
				break;
				case 28:
					nextState = 66;
				break;
				case 37:
					nextState = 66;
				break;
				case 42:
					nextState = 66;
				break;
				case 48:
					nextState = 66;
				break;
				case 50:
					nextState = 66;
				break;
				case 52:
					nextState = 66;
				break;
				case 55:
					nextState = 66;
				break;
				case 57:
					nextState = 66;
				break;
				case 67:
					nextState = 66;
				break;
				case 70:
					nextState = 71;
				break;
				case 89:
					nextState = 66;
				break;
				case 93:
					nextState = 66;
				break;
				case 96:
					nextState = 66;
				break;
				default:
					return false;
			}
		break;
		case ED:
			switch(state){
				case 27:
					nextState = 69;
				break;
				case 28:
					nextState = 69;
				break;
				case 37:
					nextState = 69;
				break;
				case 42:
					nextState = 69;
				break;
				case 48:
					nextState = 69;
				break;
				case 50:
					nextState = 69;
				break;
				case 52:
					nextState = 69;
				break;
				case 55:
					nextState = 69;
				break;
				case 57:
					nextState = 69;
				break;
				case 67:
					nextState = 69;
				break;
				case 70:
					nextState = 69;
				break;
				case 73:
					nextState = 74;
				break;
				case 89:
					nextState = 69;
				break;
				case 93:
					nextState = 69;
				break;
				case 96:
					nextState = 69;
				break;
				default:
					return false;
			}
		break;
		case EC:
			switch(state){
				case 27:
					nextState = 72;
				break;
				case 28:
					nextState = 72;
				break;
				case 37:
					nextState = 72;
				break;
				case 42:
					nextState = 72;
				break;
				case 48:
					nextState = 72;
				break;
				case 50:
					nextState = 72;
				break;
				case 52:
					nextState = 72;
				break;
				case 55:
					nextState = 72;
				break;
				case 57:
					nextState = 72;
				break;
				case 67:
					nextState = 72;
				break;
				case 70:
					nextState = 72;
				break;
				case 73:
					nextState = 72;
				break;
				case 76:
					nextState = 77;
				break;
				case 89:
					nextState = 72;
				break;
				case 93:
					nextState = 72;
				break;
				case 96:
					nextState = 72;
				break;
				default:
					return false;
			}
		break;
		case EB:
			switch(state){
				case 27:
					nextState = 75;
				break;
				case 28:
					nextState = 75;
				break;
				case 37:
					nextState = 75;
				break;
				case 42:
					nextState = 75;
				break;
				case 48:
					nextState = 75;
				break;
				case 50:
					nextState = 75;
				break;
				case 52:
					nextState = 75;
				break;
				case 55:
					nextState = 75;
				break;
				case 57:
					nextState = 75;
				break;
				case 67:
					nextState = 75;
				break;
				case 70:
					nextState = 75;
				break;
				case 73:
					nextState = 75;
				break;
				case 76:
					nextState = 75;
				break;
				case 79:
					nextState = 80;
				break;
				case 81:
					nextState = 82;
				break;
				case 89:
					nextState = 75;
				break;
				case 93:
					nextState = 75;
				break;
				case 96:
					nextState = 75;
				break;
				default:
					return false;
			}
		break;
		case EA:
			switch(state){
				case 27:
					nextState = 78;
				break;
				case 28:
					nextState = 78;
				break;
				case 37:
					nextState = 78;
				break;
				case 42:
					nextState = 78;
				break;
				case 48:
					nextState = 78;
				break;
				case 50:
					nextState = 78;
				break;
				case 52:
					nextState = 78;
				break;
				case 55:
					nextState = 78;
				break;
				case 57:
					nextState = 78;
				break;
				case 67:
					nextState = 78;
				break;
				case 70:
					nextState = 78;
				break;
				case 73:
					nextState = 78;
				break;
				case 76:
					nextState = 78;
				break;
				case 79:
					nextState = 78;
				break;
				case 81:
					nextState = 78;
				break;
				case 84:
					nextState = 85;
				break;
				case 89:
					nextState = 78;
				break;
				case 93:
					nextState = 78;
				break;
				case 96:
					nextState = 78;
				break;
				default:
					return false;
			}
		break;
		case EU:
			switch(state){
				case 27:
					nextState = 83;
				break;
				case 28:
					nextState = 83;
				break;
				case 37:
					nextState = 83;
				break;
				case 42:
					nextState = 83;
				break;
				case 48:
					nextState = 83;
				break;
				case 50:
					nextState = 83;
				break;
				case 52:
					nextState = 83;
				break;
				case 55:
					nextState = 83;
				break;
				case 57:
					nextState = 83;
				break;
				case 67:
					nextState = 83;
				break;
				case 70:
					nextState = 83;
				break;
				case 73:
					nextState = 83;
				break;
				case 76:
					nextState = 83;
				break;
				case 79:
					nextState = 83;
				break;
				case 81:
					nextState = 83;
				break;
				case 84:
					nextState = 83;
				break;
				case 89:
					nextState = 83;
				break;
				case 93:
					nextState = 83;
				break;
				case 96:
					nextState = 83;
				break;
				default:
					return false;
			}
		break;
		case DA:
			switch(state){
				case 27:
					nextState = 86;
				break;
				case 28:
					nextState = 86;
				break;
				case 37:
					nextState = 86;
				break;
				case 42:
					nextState = 86;
				break;
				case 48:
					nextState = 86;
				break;
				case 50:
					nextState = 86;
				break;
				case 52:
					nextState = 86;
				break;
				case 55:
					nextState = 86;
				break;
				case 57:
					nextState = 86;
				break;
				case 60:
					nextState = 61;
				break;
				case 63:
					nextState = 64;
				break;
				case 67:
					nextState = 86;
				break;
				case 70:
					nextState = 86;
				break;
				case 73:
					nextState = 86;
				break;
				case 76:
					nextState = 86;
				break;
				case 79:
					nextState = 86;
				break;
				case 81:
					nextState = 86;
				break;
				case 84:
					nextState = 86;
				break;
				case 87:
					nextState = 88;
				break;
				case 89:
					nextState = 86;
				break;
				case 93:
					nextState = 86;
				break;
				case 96:
					nextState = 86;
				break;
				default:
					return false;
			}
		break;
		case UO:
			switch(state){
				case 27:
					nextState = 87;
				break;
				case 28:
					nextState = 87;
				break;
				case 37:
					nextState = 87;
				break;
				case 42:
					nextState = 87;
				break;
				case 48:
					nextState = 87;
				break;
				case 50:
					nextState = 87;
				break;
				case 52:
					nextState = 87;
				break;
				case 55:
					nextState = 87;
				break;
				case 57:
					nextState = 87;
				break;
				case 67:
					nextState = 87;
				break;
				case 70:
					nextState = 87;
				break;
				case 73:
					nextState = 87;
				break;
				case 76:
					nextState = 87;
				break;
				case 79:
					nextState = 87;
				break;
				case 81:
					nextState = 87;
				break;
				case 84:
					nextState = 87;
				break;
				case 89:
					nextState = 87;
				break;
				case 93:
					nextState = 87;
				break;
				case 96:
					nextState = 87;
				break;
				default:
					return false;
			}
		break;
		case BOA:
			switch(state){
				case 83:
					nextState = 84;
				break;
				default:
					return false;
			}
		break;
		case BOB:
			switch(state){
				case 75:
					nextState = 76;
				break;
				default:
					return false;
			}
		break;
		case BOC:
			switch(state){
				case 72:
					nextState = 73;
				break;
				default:
					return false;
			}
		break;
		case BOD:
			switch(state){
				case 69:
					nextState = 70;
				break;
				default:
					return false;
			}
		break;
		case BOE:
			switch(state){
				case 66:
					nextState = 67;
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
bool rule1(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = VD;
	parts[1] = DL;
	return reduce(param, DL, parts, 2, 1);
}
bool rule2(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = VD;
	return reduce(param, DL, parts, 1, 2);
}
bool rule3(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = T;
	parts[1] = ID;
	parts[2] = SEMI;
	return reduce(param, VD, parts, 3, 3);
}
bool rule4(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = T;
	parts[1] = ID;
	parts[2] = BR;
	return reduce(param, VD, parts, 3, 4);
}
bool rule5(ParserParam &param){
	TokenType *parts = new TokenType[6];
	parts[0] = T;
	parts[1] = ID;
	parts[2] = BRAC_SL;
	parts[3] = PDL;
	parts[4] = BRAC_SR;
	parts[5] = B;
	return reduce(param, VD, parts, 6, 5);
}
bool rule6(ParserParam &param){
	TokenType *parts = new TokenType[5];
	parts[0] = T;
	parts[1] = ID;
	parts[2] = BRAC_SL;
	parts[3] = BRAC_SR;
	parts[4] = B;
	return reduce(param, VD, parts, 5, 6);
}
bool rule7(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = VD;
	parts[1] = VDL;
	return reduce(param, VDL, parts, 2, 7);
}
bool rule8(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = VD;
	return reduce(param, VDL, parts, 1, 8);
}
bool rule9(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = PDLT;
	return reduce(param, PDL, parts, 1, 9);
}
bool rule10(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = PD;
	parts[1] = PDLT_;
	return reduce(param, PDLT, parts, 2, 10);
}
bool rule11(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = PD;
	return reduce(param, PDLT, parts, 1, 11);
}
bool rule12(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = COMMA;
	parts[1] = PDLT;
	return reduce(param, PDLT_, parts, 2, 12);
}
bool rule13(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = T;
	parts[1] = ID;
	return reduce(param, PD, parts, 2, 13);
}
bool rule14(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = T;
	parts[1] = ID;
	parts[2] = BR_;
	return reduce(param, PD, parts, 3, 14);
}
bool rule15(ParserParam &param){
	TokenType *parts = new TokenType[4];
	parts[0] = BRAC_ML;
	parts[1] = NUM;
	parts[2] = BRAC_MR;
	parts[3] = SEMI;
	return reduce(param, BR, parts, 4, 15);
}
bool rule16(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = BRAC_ML;
	parts[1] = BRAC_MR;
	return reduce(param, BR_, parts, 2, 16);
}
bool rule17(ParserParam &param){
	TokenType *parts = new TokenType[4];
	parts[0] = BRAC_LL;
	parts[1] = DL;
	parts[2] = SL;
	parts[3] = BRAC_LR;
	return reduce(param, B, parts, 4, 17);
}
bool rule18(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = BRAC_LL;
	parts[1] = BRAC_LR;
	return reduce(param, B, parts, 2, 18);
}
bool rule19(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = BRAC_LL;
	parts[1] = SL;
	parts[2] = BRAC_LR;
	return reduce(param, B, parts, 3, 19);
}
bool rule20(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = BRAC_LL;
	parts[1] = DL;
	parts[2] = BRAC_LR;
	return reduce(param, B, parts, 3, 20);
}
bool rule21(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = INT;
	return reduce(param, T, parts, 1, 21);
}
bool rule22(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = CHAR;
	return reduce(param, T, parts, 1, 22);
}
bool rule23(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = S;
	parts[1] = SL;
	return reduce(param, SL, parts, 2, 23);
}
bool rule24(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = S;
	return reduce(param, SL, parts, 1, 24);
}
bool rule25(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = SEMI;
	return reduce(param, S, parts, 1, 25);
}
bool rule26(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = E;
	parts[1] = SEMI;
	return reduce(param, S, parts, 2, 26);
}
bool rule27(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = RET;
	parts[1] = E;
	parts[2] = SEMI;
	return reduce(param, S, parts, 3, 27);
}
bool rule28(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = BREAK;
	parts[1] = SEMI;
	return reduce(param, S, parts, 2, 28);
}
bool rule29(ParserParam &param){
	TokenType *parts = new TokenType[7];
	parts[0] = IF;
	parts[1] = BRAC_SL;
	parts[2] = E;
	parts[3] = BRAC_SR;
	parts[4] = S;
	parts[5] = ELSE;
	parts[6] = S;
	return reduce(param, S, parts, 7, 29);
}
bool rule30(ParserParam &param){
	TokenType *parts = new TokenType[5];
	parts[0] = WHILE;
	parts[1] = BRAC_SL;
	parts[2] = E;
	parts[3] = BRAC_SR;
	parts[4] = S;
	return reduce(param, S, parts, 5, 30);
}
bool rule31(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = B;
	return reduce(param, S, parts, 1, 31);
}
bool rule32(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = PRINT;
	parts[1] = DA;
	parts[2] = SEMI;
	return reduce(param, S, parts, 3, 32);
}
bool rule33(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = READ;
	parts[1] = DA;
	parts[2] = SEMI;
	return reduce(param, S, parts, 3, 33);
}
bool rule34(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = EE;
	parts[1] = BOE;
	parts[2] = E;
	return reduce(param, E, parts, 3, 34);
}
bool rule35(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = EE;
	return reduce(param, E, parts, 1, 35);
}
bool rule36(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = ED;
	parts[1] = BOD;
	parts[2] = EE;
	return reduce(param, EE, parts, 3, 36);
}
bool rule37(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = ED;
	return reduce(param, EE, parts, 1, 37);
}
bool rule38(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = EC;
	parts[1] = BOC;
	parts[2] = ED;
	return reduce(param, ED, parts, 3, 38);
}
bool rule39(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = EC;
	return reduce(param, ED, parts, 1, 39);
}
bool rule40(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = EB;
	parts[1] = BOB;
	parts[2] = EC;
	return reduce(param, EC, parts, 3, 40);
}
bool rule41(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = EB;
	return reduce(param, EC, parts, 1, 41);
}
bool rule42(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = EA;
	parts[1] = MINUS;
	parts[2] = EB;
	return reduce(param, EB, parts, 3, 42);
}
bool rule43(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = EA;
	parts[1] = PLUS;
	parts[2] = EB;
	return reduce(param, EB, parts, 3, 43);
}
bool rule44(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = EA;
	return reduce(param, EB, parts, 1, 44);
}
bool rule45(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = EU;
	parts[1] = BOA;
	parts[2] = EA;
	return reduce(param, EA, parts, 3, 45);
}
bool rule46(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = EU;
	return reduce(param, EA, parts, 1, 46);
}
bool rule47(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = DA;
	return reduce(param, EU, parts, 1, 47);
}
bool rule48(ParserParam &param){
	TokenType *parts = new TokenType[2];
	parts[0] = UO;
	parts[1] = DA;
	return reduce(param, EU, parts, 2, 48);
}
bool rule49(ParserParam &param){
	TokenType *parts = new TokenType[3];
	parts[0] = BRAC_SL;
	parts[1] = E;
	parts[2] = BRAC_SR;
	return reduce(param, EU, parts, 3, 49);
}
bool rule50(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = ID;
	return reduce(param, DA, parts, 1, 50);
}
bool rule51(ParserParam &param){
	TokenType *parts = new TokenType[4];
	parts[0] = ID;
	parts[1] = BRAC_ML;
	parts[2] = E;
	parts[3] = BRAC_MR;
	return reduce(param, DA, parts, 4, 51);
}
bool rule52(ParserParam &param){
	TokenType *parts = new TokenType[4];
	parts[0] = ID;
	parts[1] = BRAC_SL;
	parts[2] = E;
	parts[3] = BRAC_SR;
	return reduce(param, DA, parts, 4, 52);
}
bool rule53(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = NUM;
	return reduce(param, DA, parts, 1, 53);
}
bool rule54(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = OOPS;
	return reduce(param, UO, parts, 1, 54);
}
bool rule55(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = MINUS;
	return reduce(param, UO, parts, 1, 55);
}
bool rule56(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = MULT;
	return reduce(param, BOA, parts, 1, 56);
}
bool rule57(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = DIVI;
	return reduce(param, BOA, parts, 1, 57);
}
bool rule58(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = EQUA;
	return reduce(param, BOB, parts, 1, 58);
}
bool rule59(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = NEQU;
	return reduce(param, BOB, parts, 1, 59);
}
bool rule60(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = GREA;
	return reduce(param, BOB, parts, 1, 60);
}
bool rule61(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = GREQ;
	return reduce(param, BOB, parts, 1, 61);
}
bool rule62(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = LSTH;
	return reduce(param, BOB, parts, 1, 62);
}
bool rule63(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = LSEQ;
	return reduce(param, BOB, parts, 1, 63);
}
bool rule64(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = AND;
	return reduce(param, BOC, parts, 1, 64);
}
bool rule65(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = OR;
	return reduce(param, BOC, parts, 1, 65);
}
bool rule66(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = ASSI;
	return reduce(param, BOD, parts, 1, 66);
}
bool rule67(ParserParam &param){
	TokenType *parts = new TokenType[1];
	parts[0] = COMMA;
	return reduce(param, BOE, parts, 1, 67);
}
