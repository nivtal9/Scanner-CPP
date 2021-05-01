//
// Created by nivtal9 on 19/04/2021.
//

#include "scanner.h"
#include <cctype>
#include <memory>
using namespace std;
shared_ptr<Token> Scanner:: nextToken(){
    regex zero(R"(0)");
    regex number(R"([0-9Ee+\-.])");
    regex numbers(R"([1-9](\d)*)");
    regex numbers_Or_E(R"((\d)+[Ee][+-]?(\d)+)");
    regex x_then_numbers(R"((\d)*\.(\d)+([Ee][+-]?(\d)+)?)");
    regex numbers_then_x(R"((\d)+\.(\d)*([Ee][+-]?(\d)+)?)");
    regex str_char(R"(\'[^\']\')");
    regex str_string(R"(\"[^\"]*\")");
    regex str_word(R"([\w\d])");
    regex str_word_and_num(R"(\w(\w|\d)*)");
    while(nextChar()){
        /**
         * scan for one note
         */
        switch (ch) {
            case '+':
                if(inputFile.peek()=='+'){
                    nextChar();
                    return std::make_shared<Token> (INC_OP, "++");
                }
                else goto character;
            case '-':
                if(inputFile.peek()=='-'){
                    nextChar();
                    return std::make_shared<Token> (DEC_OP, "--");
                }
                else if(inputFile.peek()=='>'){
                    nextChar();
                    return std::make_shared<Token> (PTR_OP, "->");
                }
                else goto character;
            case '=':
                if(inputFile.peek()=='='){
                    nextChar();
                    return std::make_shared<Token> (EQ_OP, "==");
                }
                else goto character;
            case '&':
                if(inputFile.peek()=='&'){
                    nextChar();
                    return std::make_shared<Token> (AND_OP, "&&");
                }
                else goto character;
            case '|':
                if(inputFile.peek()=='|'){
                    nextChar();
                    return std::make_shared<Token> (OR_OP, "||");
                }
                else goto character;
            case '>':
                if(inputFile.peek()=='='){
                    nextChar();
                    return std::make_shared<Token> (GE_OP, ">=");
                }
                else goto character;
            case '<':
                if(inputFile.peek()=='='){
                    nextChar();
                    return std::make_shared<Token> (LE_OP, "<=");
                }
                else goto character;
            case '!':
                if(inputFile.peek()=='='){
                    nextChar();
                    return std::make_shared<Token> (NE_OP, "!=");
                }
                else goto character;
            case '.':
                if(isdigit(inputFile.peek())){
                    break;
                }
                else goto character;
            case '/':
                if(inputFile.peek()=='/'){
                    while(nextChar()&&ch!='\n'){}
                }
                else if(inputFile.peek()=='*'){
                    char previous=0; char curr;
                    while (nextChar()){
                        curr=ch;
                        if(curr=='/'&&previous=='*'){
                            break;
                        }
                        previous=curr;
                    }
                }
                else goto character;
                case ' ': case '\r': case '\t': case '\n':
                    continue;
                //only one character by itself
            case ';': case '{': case '}': case ',': case ':':
            case '(': case ')': case '[': case ']': case '~':
            case '*': case '%': case '^': case '?':
                character:
                return std::make_shared<Token>(static_cast<tokenType>(ch), string(1, ch));
        }
        /**
         * scan for string
         */
        if(ch=='\"'){
            string str;
            while(nextChar()&&ch!='\"'){
                str+=ch;
            }
            if(regex_match("\""+str+"\"",str_string)){
                return std::make_shared<Token>(STRING_LITERAL, str);
            }
            else return std::make_shared<Token>(ERROR, str);

        }
        /**
         * scan for word
         */
        if(isalpha(ch)){
            string str;
            str=ch;
            while(nextChar()&& regex_match(string(1,ch),str_word)){
                str+=ch;
            }
            inputFile.unget();
            
            if(regex_match(str,str_word_and_num)){
                shared_ptr<Token> t = symTab.lookupToken(str);
                shared_ptr<Token> temp(new varToken(str));
                
                if(t== nullptr){
                    
                    temp->add_line(lineno);
                    
                    t=temp;
                    
                    symTab.insertToken(str,t);
                    
                    t->add_line(lineno);
                    
                }else if(t->getType()==IDENTIFIER){
                    
                    t->add_line(lineno);
                }
                
                return t;
            }
        }
        /**
         * scan for character
         */
        if(ch=='\''){
            string str;
            if(nextChar()){
                str=ch;
            }
            if(!(nextChar()&&ch=='\'')){
                str="";
            }
            if(regex_match('\''+str+'\'',str_char)){
                return std::make_shared<Token>(CONSTANT, str);
            }
            else return std::make_shared<Token>(ERROR, str);
        }
        /**
         * scan for number
         */
         if(isdigit(ch)||ch=='.'){
             string str;
             str=ch;
             while(nextChar()&& regex_match(string(1,ch),number)){
                 str+=ch;
             }
             inputFile.unget();
             if(regex_match(str,zero)||
                     regex_match(str,numbers)||
                     regex_match(str,numbers_Or_E)||
                     regex_match(str,x_then_numbers)||
                     regex_match(str,numbers_then_x)){
                 return std::make_shared<Token>(CONSTANT, str);
             }
             else return std::make_shared<Token>(ERROR, str);
         }
    }
    return nullptr;
}
