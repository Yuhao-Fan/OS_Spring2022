//
// Created by Yuhao Fan on 2/4/22.
//

#ifndef OS_HW1_SYMBOL_H
#define OS_HW1_SYMBOL_H

#include <string>
using namespace std;

class Symbol {
public:
    ////symbol name, position, module number, visited, error message, number of memory in previous module
    Symbol(string name,int position,int moduleNum,bool visited,string errorMess,int prevProgNum){

        this->name = name;
        this->position = position;
        this->moduleNum = moduleNum;
        this->visited = visited;
        this->errorMess = errorMess;
        this->prevProgNum = prevProgNum;
    }
    Symbol(Symbol* sym){
        this->name = sym->name;
        this->position = sym->position;
        this->moduleNum = sym->moduleNum;
        this->visited = sym->visited;
        this->errorMess = sym->errorMess;
        this->prevProgNum = sym->prevProgNum;
    };

    string name;
    int position;
    int moduleNum;
    bool visited;
    string errorMess;
    int prevProgNum;
private:

};


#endif //OS_HW1_SYMBOL_H
