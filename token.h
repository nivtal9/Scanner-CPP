//
// Created by nivtal9 on 19/04/2021.
//

#ifndef SCANNER_TOKEN_H
#define SCANNER_TOKEN_H


#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <memory>
#include "tokentype.h"
using namespace std;

class Token {
    tokenType type;
    string text;
public:
    Token(tokenType tt, string t) : type(tt), text(t) {}
    tokenType getType();
    string getText();
    void printToken();
    virtual void add_line(int l) {}
    virtual shared_ptr<set<int>> getLines() {return nullptr;}
};

class varToken: public Token {
    shared_ptr<set<int>> lines = make_shared<set<int>>();
//    shared_ptr<set<int>> lines;
public:
    varToken(string t) : Token(IDENTIFIER, t) {}
    void add_line(int l);
    shared_ptr<set<int>> getLines();
};


#endif //SCANNER_TOKEN_H
