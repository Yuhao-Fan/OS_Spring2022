//
// Created by Yuhao Fan on 4/11/22.
//


#ifndef LAB3_ASSIGN_PAGER_H
#define LAB3_ASSIGN_PAGER_H

//#include "../Simulator.h"
#include "../Frame.h"
#include "../Process.h"
#include <vector>
using namespace std;
class Pager {
    // virtual base class
public:
    Pager(){};
    virtual FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num) = 0;
    virtual void reset_age(int MaxFrames){
        Ages=new unsigned int[MaxFrames];
        for(int i=0;i<MaxFrames;i++){
            Ages[i] = 0;
        }
    };
    unsigned int* Ages;
};


#endif //LAB3_ASSIGN_PAGER_H
