//
// Created by Yuhao Fan on 2/4/22.
//


#include "Linker.h"
#include "Token.h"
#include "Memory.h"
#include "Symbol.h"

void Linker::tokenizer(string &filename) {
    ifstream firstPass = openFile(filename);
    pass1(firstPass);
    firstPass.close();

    printSymTable();

    ifstream secondPass = openFile(filename);
    pass2(secondPass);
    secondPass.close();

    printMemory();

    neverUsed();


}
void Linker::pass1(ifstream& input) {
    int moduleNum=0;

    while (!eof) {

        moduleNum++;
//        createModule();

        //defination List
        int defCount = readInt(input);
        if(defCount > MAX_DEF_COUNT){
            Token token(lineNum,part-TOL+1);
            token.parseError(4);
        }
        vector<Symbol> moduleSymbols;



        for (int i = 0; i < defCount; i++) {
            string readName = readSymbol(input);
            if(readName==""){
                //input-18
                Token token(lineNum,part-TOL+1);
                token.parseError(1);
            }
            int readPos = readInt(input);
            if(SymbolMap.find(readName)!=SymbolMap.end()){//contains

                int symbolNum=SymbolMap[readName];
                Symbol prevSym=SymbolTable[symbolNum];
                string multiDef =" Error: This variable is multiple times defined; first value used";
                if(prevSym.moduleNum==moduleNum||prevSym.position==prevSym.prevProgNum){//if in the same module or previous warning
                    Symbol sym1 = Symbol(prevSym);//deep copy
                    sym1.moduleNum=moduleNum;
                    sym1.position=prevSym.prevProgNum;//rule 2
                    sym1.errorMess=multiDef;
                    moduleSymbols.push_back(sym1);//input-21

                }
                //else do not need more modifications
                SymbolTable[symbolNum].errorMess=multiDef;

            }
            else{

                Symbol sym = Symbol(readName,readPos + prevProgNum,moduleNum,false,"",prevProgNum);

                SymbolTable.push_back(sym);
                SymbolMap.emplace(readName,SymbolTable.size()-1);
                moduleSymbols.push_back(sym);//temp

            }

        }

        //Use List
        int useCount = readInt(input);
        if(useCount > MAX_USE_COUNT){
            Token token(lineNum,part-TOL+1);
            token.parseError(5);
        }

        for (int i = 0; i < useCount; i++) {
            string readString = readSymbol(input);
            //Do not need to store useList in pass1
        }

        //Program text
        int progCount = readInt(input);

        if(prevProgNum+progCount>MAX_MACHINE_SIZE){

            Token token(lineNum,part-TOL+1);
            token.parseError(6);
        }
        for(auto& symbol:moduleSymbols){
            Symbol currSym=symbol;
            int posAtTOL = currSym.position-prevProgNum;
            if(posAtTOL>progCount-1){
                cout<<"Warning: Module "<<currSym.moduleNum<<": "<<currSym.name<<" too big "<<posAtTOL<<" (max="<<progCount-1<<") assume zero relative"<<endl;
                SymbolTable[SymbolMap[symbol.name]].position=prevProgNum;

            }
        }

        for (int i = 0; i < progCount; i++) {
            char addressMode = readIEAR(input);

            //input-12
            if(addressMode==-1){//can't read'
                Token token(lineNum,lastEnd+1);
                token.parseError(2);
            }
            readInt(input);

//            }
        }

        prevProgNum+=progCount;
//        cout<<"eof:"<<eof<<endl;
    }


}

void Linker::pass2(ifstream& input) {
    int moduleNum=0;
    while (!eof) {
        moduleNum++;
        //defination List
        int defCount = readInt(input);
        if(defCount<0)return;
//        cout<<"defCount"<<defCount<<endl;
        for (int i = 0; i < defCount; i++) {
            string readName = readSymbol(input);

            readInt(input);
        }

        //Use List
        int useCount = readInt(input);
        if(useCount<0)return;
        string useList[useCount];
        bool useVisited[useCount];

        for (int i = 0; i < useCount; i++) {
            string readString = readSymbol(input);

            useList[i] = readString;
            useVisited[i]=false;
        }

        //Program text
        int progCount = readInt(input);
        if(progCount<0)return;
        int progNum=prevProgNum;

        for (int i = 0; i < progCount; i++,progNum++) {

            char addressMode = readIEAR(input);

            int operand = readInt(input);
            int zero = operand - operand % 1000;
            if(operand/1000>=10&&addressMode!='I'){//opcode
                memoryAdd(progNum,9999," Error: Illegal opcode; treated as 9999");
            }else {
                switch (addressMode) {
                    case 'R':
                        //Relative
                        if (operand % 1000 >= progCount) {
                            memoryAdd(progNum, zero + prevProgNum,
                                      " Error: Relative address exceeds module size; zero used");
                        } else {
                            memoryAdd(progNum, prevProgNum + operand);
                        }


                        break;
                    case 'E':
                        //External
                    {
                        if (operand % 1000 >= useCount) {
                            memoryAdd(progNum, operand,
                                      " Error: External address exceeds length of uselist; treated as immediate");

                            //input-7
                        } else {
                            string targetSym = useList[operand % 1000];

                            if (SymbolMap.find(targetSym) ==SymbolMap.end()) {//not contains

                                memoryAdd(progNum, zero, " Error: "+targetSym+" is not defined; zero used");
                                useVisited[operand % 1000]=true;//input-5

                            } else {
                                int symbolNum=SymbolMap[targetSym];
                                SymbolTable[symbolNum].visited = true;
                                useVisited[operand % 1000]=true;
                                int newVal = zero + SymbolTable[symbolNum].position;
//                            cout<<zero+sym.position;
                                memoryAdd(progNum, newVal);
                            }

                        }


                    }

                        break;
                    case 'I':
                        //Immediate

//                    cout<<operand+0;
                        if (operand >= 10000) {
                            memoryAdd(progNum, 9999, " Error: Illegal immediate value; treated as 9999");
                        } else {
                            memoryAdd(progNum, operand + 0);
                        }

                        break;
                    case 'A':
                        //Absolute
                        if (operand % 1000 >= MAX_MACHINE_SIZE) {

                            memoryAdd(progNum, zero, " Error: Absolute address exceeds machine size; zero used");
                        } else {
                            memoryAdd(progNum, operand);
                        }

                        break;
                    default:
                        //error
                        Token token(lineNum, part - TOL + 1);
                        token.parseError(2);

                        // code block
                }
            }




        }
        for(int i=0;i<useCount;i++){
            if(!useVisited[i]){
                int moduleFirst = prevProgNum+progCount;
                WARNINGS[moduleFirst].push_back("Warning: Module "
                                               +to_string(moduleNum)+": "+useList[i]+" appeared in the uselist but was not actually used");
            }
        }

        prevProgNum+=progCount;
//        cout<<"eof:"<<eof<<endl;

    }


}

int Linker::readInt(ifstream& input) {
    char* newpart = strtok(NULL," \t\n");
    if(newpart == nullptr) {

        if(!readNewLine(input)){
            eof=true;
            return -1;
        }
    }else{
        part=newpart;
    }


    int partInt=atoi(part);
    if (partInt==0&&part[0]!='0'){//if part is not a number, atoi will return 0
        Token token(lineNum,part-TOL+1);
        token.parseError(0);
    }
//    cout<<"readInt():"<<part<<endl;
    string partS = string(part);
    lastEnd = part+partS.size()-TOL;

    return partInt;

}
char Linker::readIEAR(ifstream &input) {

    char* newpart =strtok(NULL," \t\n");//multiple delimiters

    if(newpart == nullptr) {
        if(!readNewLine(input)){

            eof=true;
            return -1;
        }
    }else{
        part=newpart;
    }

    string partS = string(part);
    if(partS!="I"&&partS!="R"&&partS!="E"&&partS!="A"){
        Token token(lineNum,part-TOL+1);
        token.parseError(2);
    }


    char IEAR = part[0];


    lastEnd = part+1-TOL;
    return IEAR;
}





string Linker::readSymbol(ifstream &input) {
    char* newpart =strtok(NULL," \t\n");//multiple delimiters

    if(newpart == nullptr) {
        if(!readNewLine(input)){
            eof=true;
            return "";
        }
    }else{
        part=newpart;
    }

    if (atoi(part)){//if part is a number, atoi will return an integer other than 0
        Token token(lineNum,part-TOL+1);
        token.parseError(1);
    }

    string partString = string(part);
    if(partString.size()>MAX_SYMBOL_LENGTH){
        Token token(lineNum,part-TOL+1);
        token.parseError(3);
    }

    lastEnd = part+partString.size()-TOL;

    return partString;
}

bool Linker::readNewLine(ifstream &input) {
    part=part+1;
    char* newpart=nullptr;

    do{
        string newline = "";
        if(!getline(input,newline)){
//            cout<<"EOF"<<endl;
            return false;
        }
        lineNum++;
        lastEnd=1;
        TOL = new char [newline.length()+1];
        strcpy (TOL, newline.c_str());
        newpart =strtok(TOL," ");
        if(newpart != nullptr){
            part=newpart;
        }else{
            part=TOL;
        }



    }while (newpart==nullptr);
    return true;

}

void Linker::printSymTable() {
    cout<<"Symbol Table"<<endl;
    for (int i=0;i<(int) SymbolTable.size();i++) {
        cout<<SymbolTable[i].name << "=" << SymbolTable[i].position;
        cout<<SymbolTable[i].errorMess<<endl;
    }
    cout<<endl;
}
void Linker::printMemory() {
    cout<<"Memory Map"<<endl;
    int size = (int)MemoryMap.size();
    for (int i=0; i<size+1; i++) {
        //pringt before next module
        if(WARNINGS.find(i)!=WARNINGS.end()) {
            vector<string> warnings=WARNINGS[i];
            for(string warning:warnings){
                cout<<warning<<endl;
            }
        }
        if(i<size){
            cout <<setw(3)<<setfill('0') <<i << ": " ;
            cout<<setw(4)<<setfill('0')<< MemoryMap[i].m_value << MemoryMap[i].m_errorMess << endl;
        }


    }
}
ifstream Linker::openFile(string filename) {
//    cout<<"Opening:"<<filename<<endl;
    ifstream input(filename);
    if (!input.is_open()) {

        cerr << "open input failed" << endl;
        exit(-1);
    }
    lineNum=0;
    eof=false;
    prevProgNum=0;
    part=nullptr;
    TOL=nullptr;
    lastEnd=1;
    return input;
}

void Linker::neverUsed() {
    cout<<endl;
    for (auto& sym:SymbolTable) {
        if(!sym.visited){
            cout<<"Warning: Module "<<sym.moduleNum<<": "<<sym.name<<" was defined but never used"<<endl;
        }
    }
}

void Linker::memoryAdd(int progNum, int newVal,string errorMess) {
    Memory mem(newVal, errorMess);
    MemoryMap[progNum]=mem;
//    MemoryMap.emplace(progNum,mem);
}

void Linker::memoryAdd(int progNum, int newVal) {
    Memory mem(newVal, "");
    MemoryMap[progNum]=mem;
//    MemoryMap.emplace(progNum,mem);
}
