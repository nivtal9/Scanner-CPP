//
// Created by nivtal9 on 19/04/2021.
//

#include "token.h"
#include "tokenstrings.h"
using namespace std;
shared_ptr<set<int>> varToken::getLines() {
    shared_ptr<set<int>> ptr=this->lines;
    return ptr;
}

void varToken::add_line(int l) {
    this->lines->insert(l);
}

void Token::printToken() {
    bool b=false;string str;
    if(this->type>=258){
        b=true;
        str=tokenStrings[type-258];
    }
    if(b){
        cout<< str << '\t' << this->text <<endl;
    }
    else{
        cout<< this->text << '\t' << this->text <<endl;
    }
}

tokenType Token::getType() {
    tokenType t=this->type;
    return t;
}

string Token::getText() {
    string t=this->text;
    return t;
}
