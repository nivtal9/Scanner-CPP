//
// Created by nivtal9 on 19/04/2021.
//

#include <sstream>
#include "symtab.h"
using namespace std;
void SymbolTable::insertToken(string text, shared_ptr<Token> tokenp) {
    this->symMap[text]=tokenp;
}

shared_ptr<Token> SymbolTable::lookupToken(string text) {
    shared_ptr<Token> ptr=symMap[text];
    return ptr;
}

void SymbolTable::initReserved() {
    auto create_shared_ptr=[](int type,string str){
        shared_ptr<Token> t(new Token(static_cast<tokenType>(type), std::move(str)));
        return t;
    };
    ifstream ReservedMap("reserved.txt");
    string line,str; int type;
    try{
        shared_ptr<Token> t;
        while(getline(ReservedMap,line)){
            istringstream string_stream(line);
            string_stream>>str>>type;
            t= create_shared_ptr(type,str);
            insertToken(str,t);
        }
    }
    catch (exception &e){
        cout<<"reserved.txt not found"<<endl;
    }
}

void SymbolTable::xref() {
    auto ite=symMap.begin(); string str;
    while(ite!=symMap.end()){
        auto sec=ite->second.get();
        auto *Var=dynamic_cast<varToken*>(sec);
        if(Var!= nullptr){
            str=Var->getText()+"\t";
            for(auto line : *Var->getLines()){
                str+=to_string(line)+" ";
            }
            cout<<str<<endl;
        }
        ite++;
    }
}
