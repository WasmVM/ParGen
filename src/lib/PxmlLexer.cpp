/** generated by ParGen **/
#include "PxmlLexer.hpp"


namespace ParsePxml {

using namespace Tokens;

PxmlLexer::PxmlLexer(std::filesystem::path path, std::istream& stream) :
  stream(stream), state(54)
{
    current = fetch();
    pos.path = path;
}

PxmlLexer::Chars::Chars(std::initializer_list<Chars::char_t> init) : min(init.begin()[0]){
    if(init.size() == 1){
        max = init.begin()[0];
    }else{
        max = init.begin()[1];
    }
}

bool PxmlLexer::Chars::operator<(const Chars& rhs) const {
    return (min < rhs.min) && (max < rhs.min);
}

PxmlLexer::Chars::char_t PxmlLexer::fetch(){
    std::string line_end = "";
    Chars::char_t res = stream.get();
    if(res != std::istream::traits_type::eof()){
        line_end += res;
        text += res;
        if(line_end.size() > 2){
            line_end = line_end.substr(line_end.size() - 2);
        }
        if(text.ends_with("\n")){
            cur.line += 1;
            cur.column = 0;
        }else{
            cur.column += 1;
        }
    }
    return res;
}

std::vector<PxmlLexer::State> PxmlLexer::states = {
    {{{0},1}, {{37},2}, {{92},3}, {{123},4}, }, // S0
    {}, // S1
    {{{125},5}, }, // S2
    {{{0},6}, }, // S3
    {{{37},7}, }, // S4
    {}, // S5
    {}, // S6
    {}, // S7
    {{{9,13},9}, {{32},9}, {{62},10}, {{123},11}, }, // S8
    {{{9,13},9}, {{32},9}, }, // S9
    {}, // S10
    {{{37},12}, }, // S11
    {}, // S12
    {{{9,13},14}, {{32},14}, {{34},15}, {{43},16}, {{45},16}, {{47},17}, {{48,57},18}, {{61},19}, {{62},20}, {{65,90},21}, {{95},21}, {{97,101},21}, {{102},22}, {{103,115},21}, {{116},23}, {{117,122},21}, {{123},24}, }, // S13
    {{{9,13},14}, {{32},14}, }, // S14
    {}, // S15
    {{{48,57},18}, }, // S16
    {{{9,13},25}, {{32},25}, {{62},26}, }, // S17
    {{{46},27}, {{48,57},18}, {{69},28}, {{101},28}, }, // S18
    {}, // S19
    {}, // S20
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,122},29}, }, // S21
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97},30}, {{98,122},29}, }, // S22
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,113},29}, {{114},31}, {{115,122},29}, }, // S23
    {{{37},32}, }, // S24
    {{{9,13},25}, {{32},25}, {{62},26}, }, // S25
    {}, // S26
    {{{48,57},33}, {{69},28}, {{101},28}, }, // S27
    {{{43},34}, {{45},34}, {{48,57},35}, }, // S28
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,122},29}, }, // S29
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,107},29}, {{108},36}, {{109,122},29}, }, // S30
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,116},29}, {{117},37}, {{118,122},29}, }, // S31
    {}, // S32
    {{{48,57},33}, {{69},28}, {{101},28}, }, // S33
    {{{48,57},35}, }, // S34
    {{{48,57},35}, }, // S35
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,114},29}, {{115},38}, {{116,122},29}, }, // S36
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,100},29}, {{101},39}, {{102,122},29}, }, // S37
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,100},29}, {{101},40}, {{102,122},29}, }, // S38
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,122},29}, }, // S39
    {{{48,57},29}, {{65,90},29}, {{95},29}, {{97,122},29}, }, // S40
    {{{0},42}, {{34},43}, {{92},44}, }, // S41
    {}, // S42
    {}, // S43
    {{{0},45}, }, // S44
    {}, // S45
    {{{0},47}, {{60},48}, {{92},49}, {{123},50}, }, // S46
    {}, // S47
    {}, // S48
    {{{0},51}, {{60},52}, }, // S49
    {{{37},53}, }, // S50
    {}, // S51
    {}, // S52
    {}, // S53
    {{{-1},55}, {{0},56}, {{9,13},57}, {{32},57}, {{38},58}, {{60},59}, {{92},60}, {{123},61}, }, // S54
    {}, // S55
    {}, // S56
    {{{9,13},57}, {{32},57}, }, // S57
    {{{97},62}, {{103},63}, {{108},64}, {{113},65}, }, // S58
    {{{33},66}, {{47},67}, {{65,90},68}, {{97,122},68}, }, // S59
    {{{0},69}, {{60},70}, }, // S60
    {{{37},71}, }, // S61
    {{{109},72}, {{112},73}, }, // S62
    {{{116},74}, }, // S63
    {{{116},75}, }, // S64
    {{{117},76}, }, // S65
    {{{68},77}, }, // S66
    {{{65,90},78}, {{97,122},78}, }, // S67
    {{{48,57},79}, {{65,90},79}, {{97,122},79}, }, // S68
    {}, // S69
    {}, // S70
    {}, // S71
    {{{112},80}, }, // S72
    {{{111},81}, }, // S73
    {{{59},82}, }, // S74
    {{{59},82}, }, // S75
    {{{111},83}, }, // S76
    {{{79},84}, }, // S77
    {{{48,57},85}, {{65,90},85}, {{97,122},85}, }, // S78
    {{{48,57},79}, {{65,90},79}, {{97,122},79}, }, // S79
    {{{59},82}, }, // S80
    {{{115},86}, }, // S81
    {}, // S82
    {{{116},87}, }, // S83
    {{{67},88}, }, // S84
    {{{48,57},85}, {{65,90},85}, {{97,122},85}, }, // S85
    {{{59},82}, }, // S86
    {{{59},82}, }, // S87
    {{{84},89}, }, // S88
    {{{89},90}, }, // S89
    {{{80},91}, }, // S90
    {{{69},92}, }, // S91
    {{{32},93}, }, // S92
    {{{112},94}, }, // S93
    {{{120},95}, }, // S94
    {{{109},96}, }, // S95
    {{{108},97}, }, // S96
    {{{62},98}, }, // S97
    {}, // S98
};

Token PxmlLexer::get(){
    if(current == std::istream::traits_type::eof()){
        return Token(std::monostate(), pos);
    }
    while(true){
        if(states[state].contains(current)){
            state = states[state][current];
            current = fetch();
        }else if(states[state].contains('\0')){
            state = states[state]['\0'];
            current = fetch();
        }else{
            Position _pos = pos;
            pos = cur;
            std::string _text = text;
            if(current != std::istream::traits_type::eof()){
                _text.pop_back();
            }
            switch(state){
                // Action 0
                case 98:
                    state = 54;
                    text = current;
                {
                    return Token(Doctype(), _pos);
                }break;
                // Action 1
                case 71:
                    stack.emplace_back(54, text);
                    state = 0;
                    text = current;
                break;
                // Action 2
                case 7:
                    stack.emplace_back(0, text);
                    state = 0;
                    text = current;
                break;
                // Action 3
                case 5:
                    state = stack.back().first;
                    text = current;
                    stack.pop_back();
                break;
                // Action 4
                case 6:
                    state = 0;
                    text = current;
                break;
                // Action 5
                case 1:
                    state = 0;
                    text = current;
                break;
                // Action 6
                case 78:
                case 85:
                    stack.emplace_back(54, text);
                    state = 8;
                break;
                // Action 7
                case 12:
                    stack.emplace_back(8, text);
                    state = 0;
                    text = current;
                break;
                // Action 8
                case 10:
                    state = stack.back().first;
                    text = current;
                    stack.pop_back();
                {
                    return Token(Tail(_text.substr(2, _text.size() - 3)), _pos);
                }break;
                // Action 9
                case 9:
                    state = 8;
                    text = current;
                break;
                // Action 10
                case 68:
                case 79:
                    stack.emplace_back(54, text);
                    state = 13;
                    text = current;
                {
                    return Token(Tag(_text.substr(1)), _pos);
                }break;
                // Action 11
                case 32:
                    stack.emplace_back(13, text);
                    state = 0;
                    text = current;
                break;
                // Action 12
                case 26:
                    state = stack.back().first;
                    text = current;
                    stack.pop_back();
                {
                    return Token(Inline(), _pos);
                }break;
                // Action 13
                case 20:
                    state = stack.back().first;
                    text = current;
                    stack.pop_back();
                {
                    return Token(Close(), _pos);
                }break;
                // Action 14
                case 15:
                    stack.emplace_back(13, text);
                    state = 41;
                    text = current;
                break;
                // Action 15
                case 19:
                    state = 13;
                    text = current;
                {
                    return Token(Equal(), _pos);
                }break;
                // Action 16
                case 39:
                case 40:
                    state = 13;
                    text = current;
                {
                    return Token(Bool(_text == "true"), _pos);
                }break;
                // Action 17
                case 21:
                case 22:
                case 23:
                case 29:
                case 30:
                case 31:
                case 36:
                case 37:
                case 38:
                    state = 13;
                    text = current;
                {
                    return Token(ID(_text), _pos);
                }break;
                // Action 18
                case 18:
                case 27:
                case 33:
                case 35:
                    state = 13;
                    text = current;
                {
                    return Token(Number(std::stod(_text)), _pos);
                }break;
                // Action 19
                case 14:
                    state = 13;
                    text = current;
                break;
                // Action 20
                case 42:
                case 45:
                    state = 41;
                break;
                // Action 21
                case 43:
                    state = stack.back().first;
                    text = current;
                    stack.pop_back();
                {
                    return Token(String(_text.substr(0, _text.size() - 1)), _pos);
                }break;
                // Action 22
                case 82:
                    state = 54;
                    text = current;
                {
                    return Token(Entity(_text), _pos);
                }break;
                // Action 23
                case 57:
                    state = 54;
                    text = current;
                {
                    return Token(Space(_text), _pos);
                }break;
                // Action 24
                case 70:
                    stack.emplace_back(54, text);
                    state = 46;
                {
                    text.erase(text.end() - 3);
                }break;
                // Action 25
                case 56:
                case 61:
                case 69:
                    stack.emplace_back(54, text);
                    state = 46;
                break;
                // Action 26
                case 53:
                    stack.emplace_back(46, text);
                    state = 0;
                    text = current;
                break;
                // Action 27
                case 52:
                    state = 46;
                {
                    text.erase(text.end() - 3);
                }break;
                // Action 28
                case 47:
                case 50:
                case 51:
                    state = 46;
                break;
                // Action 29
                case 48:
                    state = stack.back().first;
                    text = current;
                    stack.pop_back();
                {
                    text = "<" + text;
                    state = states[state]['<'];
                    return Token(Text(_text.substr(0, _text.size() - 1)), _pos);
                }break;
                // Action 30
                case 55:
                    state = 54;
                    text = current;
                {
                }break;
                default:
                    throw UnknownToken(_pos, text);
            }
        }
    }
}

const char* UnknownToken::what(){
    return msg.c_str();
}

} // namespace ParsePxml


