#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Rule{
public:
	string target;
	vector<string> parts;
    friend bool operator==(const Rule &a, const Rule &b){
        if(a.target != b.target){
            return false;
        }
        if(a.parts.size() != b.parts.size()){
            return false;
        }
        for(unsigned int i=0; i<a.parts.size(); ++i){
            if(a.parts.at(i) != b.parts.at(i)){
                return false;
            }
        }
        return true;
    }
    friend bool operator!=(const Rule &a, const Rule &b){ return !(a == b); }
};

typedef enum{SHIFT,REDUCE,NONE,ACCEPT} Action;

class RulePair{
public:
    RulePair():offset(0),action(NONE){}
	Rule rule;
    unsigned int offset;
    Action action;
    unsigned int actVal;
    friend bool operator==(const RulePair &a, const RulePair &b){
        return (a.rule == b.rule) && (a.offset == b.offset);
    }
    friend bool operator!=(const RulePair &a, const RulePair &b){ return !(a == b); }
};

class State{
public:
	vector<RulePair> rules;
	vector<RulePair> derives;
};

class FirstPair{
public:
    string target;
    vector<string> items;
};

class TableItem{
public:
    TableItem():action(NONE){}
    unsigned int state;
    Action action;
    unsigned int val;
    friend bool operator==(const TableItem &a, const TableItem &b){
        return (a.state == b.state) && (a.action == b.action) && (a.val == b.val);
    }
    friend bool operator!=(const TableItem &a, const TableItem &b){ return !(a == b); }
};
