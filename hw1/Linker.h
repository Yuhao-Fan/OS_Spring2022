//
// Created by Yuhao Fan on 2/4/22.
//


#ifndef OS_HW1_LINKER_H
#define OS_HW1_LINKER_H

#define MAX_MACHINE_SIZE 512
#define MAX_DEF_COUNT 16
#define MAX_USE_COUNT 16
#define MAX_SYMBOL_LENGTH 16

#include <vector>
#include "Memory.h"
#include "Symbol.h"
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <cstring>
#include <iomanip>
#include<fstream>


using namespace std;
class Linker {
public:
    Linker(){
        lineNum=0;
        eof=false;
        prevProgNum=0;
        part=nullptr;
        TOL=nullptr;
        lastEnd=1;
    };//initialize
    void pass1(ifstream& input);//get SymbolTable
    void pass2(ifstream& input);//get MemoryMap

    ifstream openFile(string filename);//and initializer;
    void tokenizer(string &filename);//two pass
    void printSymTable();
    void printMemory();

private:
    vector<Symbol> SymbolTable;//
    map<string,int> SymbolMap;//name of symbol -> seat in SymbolTable

    map<int,Memory> MemoryMap;

    char * TOL; //a pointer top of line
    char* part;//strtok position
    int lastEnd;//last line End position
    int lineNum;    //current line number
    int prevProgNum;//program number of current module
    bool eof;//end of file;

    void memoryAdd(int progNum,int newVal,string errorMess);//with errorMess
    void memoryAdd(int progNum,int newVal);//without errorMess, is ""

    int readInt(ifstream& input);
    string readSymbol(ifstream& input);
    bool readNewLine(ifstream& input);    //Passing char array by reference
    char readIEAR(ifstream &input);

    map<int,vector<string> > WARNINGS;//line number -> warning message

    void neverUsed();// last warning
};


#endif //OS_HW1_LINKER_H


