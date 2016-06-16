#include <parserFunc.hpp>
void shift(ParserParam &param, Token *tok, int state){
	param.symbols->push_back(tok);
	param.tokens->pop_front();
	param.stack.push_back(state);
}
bool funcID(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 5:
			shift(param,tok,6);
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			if(!rule67(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,92);
			break;
		case 28:
			shift(param,tok,92);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 35:
			if(!rule21(param)) return false;
			break;
		case 36:
			if(!rule22(param)) return false;
			break;
		case 37:
			shift(param,tok,92);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 42:
			shift(param,tok,92);
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 48:
			shift(param,tok,92);
			break;
		case 50:
			shift(param,tok,92);
			break;
		case 52:
			shift(param,tok,92);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 55:
			shift(param,tok,92);
			break;
		case 57:
			shift(param,tok,92);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 60:
			shift(param,tok,92);
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 63:
			shift(param,tok,92);
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		case 67:
			shift(param,tok,92);
			break;
		case 70:
			shift(param,tok,92);
			break;
		case 73:
			shift(param,tok,92);
			break;
		case 76:
			shift(param,tok,92);
			break;
		case 79:
			shift(param,tok,92);
			break;
		case 81:
			shift(param,tok,92);
			break;
		case 84:
			shift(param,tok,92);
			break;
		case 87:
			shift(param,tok,92);
			break;
		case 89:
			shift(param,tok,92);
			break;
		case 93:
			shift(param,tok,92);
			break;
		case 96:
			shift(param,tok,92);
			break;
		case 100:
			if(!rule54(param)) return false;
			break;
		case 101:
			if(!rule55(param)) return false;
			break;
		case 102:
			if(!rule56(param)) return false;
			break;
		case 103:
			if(!rule57(param)) return false;
			break;
		case 104:
			if(!rule58(param)) return false;
			break;
		case 105:
			if(!rule59(param)) return false;
			break;
		case 106:
			if(!rule60(param)) return false;
			break;
		case 107:
			if(!rule61(param)) return false;
			break;
		case 108:
			if(!rule62(param)) return false;
			break;
		case 109:
			if(!rule63(param)) return false;
			break;
		case 110:
			if(!rule64(param)) return false;
			break;
		case 111:
			if(!rule65(param)) return false;
			break;
		case 112:
			if(!rule66(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcSEMI(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 6:
			shift(param,tok,7);
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 24:
			shift(param,tok,25);
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,39);
			break;
		case 28:
			shift(param,tok,39);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,39);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 40:
			shift(param,tok,41);
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 43:
			shift(param,tok,44);
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 45:
			shift(param,tok,46);
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,39);
			break;
		case 52:
			shift(param,tok,39);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,39);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 61:
			shift(param,tok,62);
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 64:
			shift(param,tok,65);
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		case 66:
			if(!rule35(param)) return false;
			break;
		case 68:
			if(!rule34(param)) return false;
			break;
		case 69:
			if(!rule37(param)) return false;
			break;
		case 71:
			if(!rule36(param)) return false;
			break;
		case 72:
			if(!rule39(param)) return false;
			break;
		case 74:
			if(!rule38(param)) return false;
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBRAC_SL(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 6:
			shift(param,tok,9);
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			if(!rule67(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,89);
			break;
		case 28:
			shift(param,tok,89);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,89);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 42:
			shift(param,tok,89);
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 47:
			shift(param,tok,48);
			break;
		case 48:
			shift(param,tok,89);
			break;
		case 50:
			shift(param,tok,89);
			break;
		case 52:
			shift(param,tok,89);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 54:
			shift(param,tok,55);
			break;
		case 55:
			shift(param,tok,89);
			break;
		case 57:
			shift(param,tok,89);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		case 67:
			shift(param,tok,89);
			break;
		case 70:
			shift(param,tok,89);
			break;
		case 73:
			shift(param,tok,89);
			break;
		case 76:
			shift(param,tok,89);
			break;
		case 79:
			shift(param,tok,89);
			break;
		case 81:
			shift(param,tok,89);
			break;
		case 84:
			shift(param,tok,89);
			break;
		case 89:
			shift(param,tok,89);
			break;
		case 92:
			shift(param,tok,96);
			break;
		case 93:
			shift(param,tok,89);
			break;
		case 96:
			shift(param,tok,89);
			break;
		case 102:
			if(!rule56(param)) return false;
			break;
		case 103:
			if(!rule57(param)) return false;
			break;
		case 104:
			if(!rule58(param)) return false;
			break;
		case 105:
			if(!rule59(param)) return false;
			break;
		case 106:
			if(!rule60(param)) return false;
			break;
		case 107:
			if(!rule61(param)) return false;
			break;
		case 108:
			if(!rule62(param)) return false;
			break;
		case 109:
			if(!rule63(param)) return false;
			break;
		case 110:
			if(!rule64(param)) return false;
			break;
		case 111:
			if(!rule65(param)) return false;
			break;
		case 112:
			if(!rule66(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBRAC_SR(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 6:
			if(!rule13(param)) return false;
			break;
		case 9:
			shift(param,tok,13);
			break;
		case 10:
			shift(param,tok,11);
			break;
		case 16:
			if(!rule9(param)) return false;
			break;
		case 17:
			if(!rule11(param)) return false;
			break;
		case 18:
			if(!rule10(param)) return false;
			break;
		case 20:
			if(!rule12(param)) return false;
			break;
		case 21:
			if(!rule14(param)) return false;
			break;
		case 26:
			if(!rule16(param)) return false;
			break;
		case 49:
			shift(param,tok,50);
			break;
		case 56:
			shift(param,tok,57);
			break;
		case 66:
			if(!rule35(param)) return false;
			break;
		case 68:
			if(!rule34(param)) return false;
			break;
		case 69:
			if(!rule37(param)) return false;
			break;
		case 71:
			if(!rule36(param)) return false;
			break;
		case 72:
			if(!rule39(param)) return false;
			break;
		case 74:
			if(!rule38(param)) return false;
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 90:
			shift(param,tok,91);
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 97:
			shift(param,tok,98);
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcCOMMA(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 6:
			if(!rule13(param)) return false;
			break;
		case 17:
			shift(param,tok,19);
			break;
		case 21:
			if(!rule14(param)) return false;
			break;
		case 26:
			if(!rule16(param)) return false;
			break;
		case 66:
			shift(param,tok,19);
			break;
		case 69:
			if(!rule37(param)) return false;
			break;
		case 71:
			if(!rule36(param)) return false;
			break;
		case 72:
			if(!rule39(param)) return false;
			break;
		case 74:
			if(!rule38(param)) return false;
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBRAC_ML(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 6:
			shift(param,tok,22);
			break;
		case 92:
			shift(param,tok,93);
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcNUM(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			if(!rule67(param)) return false;
			break;
		case 22:
			shift(param,tok,23);
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,99);
			break;
		case 28:
			shift(param,tok,99);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,99);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 42:
			shift(param,tok,99);
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 48:
			shift(param,tok,99);
			break;
		case 50:
			shift(param,tok,99);
			break;
		case 52:
			shift(param,tok,99);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 55:
			shift(param,tok,99);
			break;
		case 57:
			shift(param,tok,99);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 60:
			shift(param,tok,99);
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 63:
			shift(param,tok,99);
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		case 67:
			shift(param,tok,99);
			break;
		case 70:
			shift(param,tok,99);
			break;
		case 73:
			shift(param,tok,99);
			break;
		case 76:
			shift(param,tok,99);
			break;
		case 79:
			shift(param,tok,99);
			break;
		case 81:
			shift(param,tok,99);
			break;
		case 84:
			shift(param,tok,99);
			break;
		case 87:
			shift(param,tok,99);
			break;
		case 89:
			shift(param,tok,99);
			break;
		case 93:
			shift(param,tok,99);
			break;
		case 96:
			shift(param,tok,99);
			break;
		case 100:
			if(!rule54(param)) return false;
			break;
		case 101:
			if(!rule55(param)) return false;
			break;
		case 102:
			if(!rule56(param)) return false;
			break;
		case 103:
			if(!rule57(param)) return false;
			break;
		case 104:
			if(!rule58(param)) return false;
			break;
		case 105:
			if(!rule59(param)) return false;
			break;
		case 106:
			if(!rule60(param)) return false;
			break;
		case 107:
			if(!rule61(param)) return false;
			break;
		case 108:
			if(!rule62(param)) return false;
			break;
		case 109:
			if(!rule63(param)) return false;
			break;
		case 110:
			if(!rule64(param)) return false;
			break;
		case 111:
			if(!rule65(param)) return false;
			break;
		case 112:
			if(!rule66(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBRAC_MR(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 22:
			shift(param,tok,26);
			break;
		case 23:
			shift(param,tok,24);
			break;
		case 66:
			if(!rule35(param)) return false;
			break;
		case 68:
			if(!rule34(param)) return false;
			break;
		case 69:
			if(!rule37(param)) return false;
			break;
		case 71:
			if(!rule36(param)) return false;
			break;
		case 72:
			if(!rule39(param)) return false;
			break;
		case 74:
			if(!rule38(param)) return false;
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 94:
			shift(param,tok,95);
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBRAC_LL(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 11:
			shift(param,tok,27);
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 13:
			shift(param,tok,27);
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,27);
			break;
		case 28:
			shift(param,tok,27);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,27);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,27);
			break;
		case 52:
			shift(param,tok,27);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,27);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBRAC_LR(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,31);
			break;
		case 28:
			shift(param,tok,34);
			break;
		case 29:
			shift(param,tok,30);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 32:
			shift(param,tok,33);
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			if(!rule24(param)) return false;
			break;
		case 38:
			if(!rule23(param)) return false;
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcINT(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 0:
			shift(param,tok,35);
			break;
		case 3:
			shift(param,tok,35);
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 9:
			shift(param,tok,35);
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			shift(param,tok,35);
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,35);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcCHAR(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 0:
			shift(param,tok,36);
			break;
		case 3:
			shift(param,tok,36);
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 9:
			shift(param,tok,36);
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			shift(param,tok,36);
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,36);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcRET(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,42);
			break;
		case 28:
			shift(param,tok,42);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,42);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,42);
			break;
		case 52:
			shift(param,tok,42);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,42);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcBREAK(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,45);
			break;
		case 28:
			shift(param,tok,45);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,45);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,45);
			break;
		case 52:
			shift(param,tok,45);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,45);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcIF(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,47);
			break;
		case 28:
			shift(param,tok,47);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,47);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,47);
			break;
		case 52:
			shift(param,tok,47);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,47);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcELSE(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 51:
			shift(param,tok,52);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcWHILE(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,54);
			break;
		case 28:
			shift(param,tok,54);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,54);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,54);
			break;
		case 52:
			shift(param,tok,54);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,54);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcPRINT(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,60);
			break;
		case 28:
			shift(param,tok,60);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,60);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,60);
			break;
		case 52:
			shift(param,tok,60);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,60);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcREAD(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,63);
			break;
		case 28:
			shift(param,tok,63);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,63);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 50:
			shift(param,tok,63);
			break;
		case 52:
			shift(param,tok,63);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 57:
			shift(param,tok,63);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcMINUS(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			if(!rule67(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,101);
			break;
		case 28:
			shift(param,tok,101);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,101);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 42:
			shift(param,tok,101);
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 48:
			shift(param,tok,101);
			break;
		case 50:
			shift(param,tok,101);
			break;
		case 52:
			shift(param,tok,101);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 55:
			shift(param,tok,101);
			break;
		case 57:
			shift(param,tok,101);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		case 67:
			shift(param,tok,101);
			break;
		case 70:
			shift(param,tok,101);
			break;
		case 73:
			shift(param,tok,101);
			break;
		case 76:
			shift(param,tok,101);
			break;
		case 78:
			shift(param,tok,79);
			break;
		case 79:
			shift(param,tok,101);
			break;
		case 81:
			shift(param,tok,101);
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 84:
			shift(param,tok,101);
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 89:
			shift(param,tok,101);
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 93:
			shift(param,tok,101);
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 96:
			shift(param,tok,101);
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		case 102:
			if(!rule56(param)) return false;
			break;
		case 103:
			if(!rule57(param)) return false;
			break;
		case 104:
			if(!rule58(param)) return false;
			break;
		case 105:
			if(!rule59(param)) return false;
			break;
		case 106:
			if(!rule60(param)) return false;
			break;
		case 107:
			if(!rule61(param)) return false;
			break;
		case 108:
			if(!rule62(param)) return false;
			break;
		case 109:
			if(!rule63(param)) return false;
			break;
		case 110:
			if(!rule64(param)) return false;
			break;
		case 111:
			if(!rule65(param)) return false;
			break;
		case 112:
			if(!rule66(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcPLUS(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 78:
			shift(param,tok,81);
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcOOPS(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 19:
			if(!rule67(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 27:
			shift(param,tok,100);
			break;
		case 28:
			shift(param,tok,100);
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		case 37:
			shift(param,tok,100);
			break;
		case 39:
			if(!rule25(param)) return false;
			break;
		case 41:
			if(!rule26(param)) return false;
			break;
		case 42:
			shift(param,tok,100);
			break;
		case 44:
			if(!rule27(param)) return false;
			break;
		case 46:
			if(!rule28(param)) return false;
			break;
		case 48:
			shift(param,tok,100);
			break;
		case 50:
			shift(param,tok,100);
			break;
		case 52:
			shift(param,tok,100);
			break;
		case 53:
			if(!rule29(param)) return false;
			break;
		case 55:
			shift(param,tok,100);
			break;
		case 57:
			shift(param,tok,100);
			break;
		case 58:
			if(!rule30(param)) return false;
			break;
		case 59:
			if(!rule31(param)) return false;
			break;
		case 62:
			if(!rule32(param)) return false;
			break;
		case 65:
			if(!rule33(param)) return false;
			break;
		case 67:
			shift(param,tok,100);
			break;
		case 70:
			shift(param,tok,100);
			break;
		case 73:
			shift(param,tok,100);
			break;
		case 76:
			shift(param,tok,100);
			break;
		case 79:
			shift(param,tok,100);
			break;
		case 81:
			shift(param,tok,100);
			break;
		case 84:
			shift(param,tok,100);
			break;
		case 89:
			shift(param,tok,100);
			break;
		case 93:
			shift(param,tok,100);
			break;
		case 96:
			shift(param,tok,100);
			break;
		case 102:
			if(!rule56(param)) return false;
			break;
		case 103:
			if(!rule57(param)) return false;
			break;
		case 104:
			if(!rule58(param)) return false;
			break;
		case 105:
			if(!rule59(param)) return false;
			break;
		case 106:
			if(!rule60(param)) return false;
			break;
		case 107:
			if(!rule61(param)) return false;
			break;
		case 108:
			if(!rule62(param)) return false;
			break;
		case 109:
			if(!rule63(param)) return false;
			break;
		case 110:
			if(!rule64(param)) return false;
			break;
		case 111:
			if(!rule65(param)) return false;
			break;
		case 112:
			if(!rule66(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcMULT(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 83:
			shift(param,tok,102);
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcDIVI(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 83:
			shift(param,tok,103);
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcEQUA(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 75:
			shift(param,tok,104);
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcNEQU(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 75:
			shift(param,tok,105);
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcGREA(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 75:
			shift(param,tok,106);
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcGREQ(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 75:
			shift(param,tok,107);
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcLSTH(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 75:
			shift(param,tok,108);
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcLSEQ(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 75:
			shift(param,tok,109);
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcAND(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 72:
			shift(param,tok,110);
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcOR(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 72:
			shift(param,tok,111);
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcASSI(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 69:
			shift(param,tok,112);
			break;
		case 72:
			if(!rule39(param)) return false;
			break;
		case 74:
			if(!rule38(param)) return false;
			break;
		case 75:
			if(!rule41(param)) return false;
			break;
		case 77:
			if(!rule40(param)) return false;
			break;
		case 78:
			if(!rule44(param)) return false;
			break;
		case 80:
			if(!rule42(param)) return false;
			break;
		case 82:
			if(!rule43(param)) return false;
			break;
		case 83:
			if(!rule46(param)) return false;
			break;
		case 85:
			if(!rule45(param)) return false;
			break;
		case 86:
			if(!rule47(param)) return false;
			break;
		case 88:
			if(!rule48(param)) return false;
			break;
		case 91:
			if(!rule49(param)) return false;
			break;
		case 92:
			if(!rule50(param)) return false;
			break;
		case 95:
			if(!rule51(param)) return false;
			break;
		case 98:
			if(!rule52(param)) return false;
			break;
		case 99:
			if(!rule53(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
bool funcEND(ParserParam &param, Token *tok){
	switch(param.stack.back()){
		case 1:
			shift(param,tok,2);
			break;
		case 2:
			param.isAccept = true;
			break;
		case 3:
			if(!rule2(param)) return false;
			break;
		case 4:
			if(!rule1(param)) return false;
			break;
		case 7:
			if(!rule3(param)) return false;
			break;
		case 8:
			if(!rule4(param)) return false;
			break;
		case 12:
			if(!rule5(param)) return false;
			break;
		case 14:
			if(!rule6(param)) return false;
			break;
		case 25:
			if(!rule15(param)) return false;
			break;
		case 30:
			if(!rule17(param)) return false;
			break;
		case 31:
			if(!rule18(param)) return false;
			break;
		case 33:
			if(!rule19(param)) return false;
			break;
		case 34:
			if(!rule20(param)) return false;
			break;
		default:
			return false;
		break;
	}
	return true;
}
