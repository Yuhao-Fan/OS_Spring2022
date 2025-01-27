//
// Created by Yuhao Fan on 2/4/22.
//


#ifndef OS_HW1_TOKEN_H
#define OS_HW1_TOKEN_H


#include<string>
#include <iostream>

using namespace std;

class Token {
public:

    Token(int lineNum,int lineOffset){
        this->lineNum = lineNum;
        this->lineOffset=lineOffset;
    }

    void parseError(int errorCode) const;
private:
    int lineNum;
    int lineOffset;

};


#endif //OS_HW1_TOKEN_H
