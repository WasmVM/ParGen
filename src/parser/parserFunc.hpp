#ifndef PARSERFUNC_HPP
#define PARSERFUNC_HPP
#include <ruleFunc.hpp>
using namespace std;
void shift(ParserParam &param, Token *tok, int state);
bool funcID(ParserParam &param, Token *tok);
bool funcSEMI(ParserParam &param, Token *tok);
bool funcBRAC_SL(ParserParam &param, Token *tok);
bool funcBRAC_SR(ParserParam &param, Token *tok);
bool funcCOMMA(ParserParam &param, Token *tok);
bool funcBRAC_ML(ParserParam &param, Token *tok);
bool funcNUM(ParserParam &param, Token *tok);
bool funcBRAC_MR(ParserParam &param, Token *tok);
bool funcBRAC_LL(ParserParam &param, Token *tok);
bool funcBRAC_LR(ParserParam &param, Token *tok);
bool funcINT(ParserParam &param, Token *tok);
bool funcCHAR(ParserParam &param, Token *tok);
bool funcRET(ParserParam &param, Token *tok);
bool funcBREAK(ParserParam &param, Token *tok);
bool funcIF(ParserParam &param, Token *tok);
bool funcELSE(ParserParam &param, Token *tok);
bool funcWHILE(ParserParam &param, Token *tok);
bool funcPRINT(ParserParam &param, Token *tok);
bool funcREAD(ParserParam &param, Token *tok);
bool funcMINUS(ParserParam &param, Token *tok);
bool funcPLUS(ParserParam &param, Token *tok);
bool funcOOPS(ParserParam &param, Token *tok);
bool funcMULT(ParserParam &param, Token *tok);
bool funcDIVI(ParserParam &param, Token *tok);
bool funcEQUA(ParserParam &param, Token *tok);
bool funcNEQU(ParserParam &param, Token *tok);
bool funcGREA(ParserParam &param, Token *tok);
bool funcGREQ(ParserParam &param, Token *tok);
bool funcLSTH(ParserParam &param, Token *tok);
bool funcLSEQ(ParserParam &param, Token *tok);
bool funcAND(ParserParam &param, Token *tok);
bool funcOR(ParserParam &param, Token *tok);
bool funcASSI(ParserParam &param, Token *tok);
bool funcEND(ParserParam &param, Token *tok);
#endif
