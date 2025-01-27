//
// Created by Yuhao Fan on 4/11/22.
//

#ifndef LAB3_ASSIGN_FIFO_H
#define LAB3_ASSIGN_FIFO_H

#include "Pager.h"

class FIFO : public Pager {
public:
    FIFO(){};
    FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num){
        int selected = hand;
        hand= (hand+1)%MaxFrames;
        return &frame_table[selected];
    }
    int hand=0;//pointer
};


#endif //LAB3_ASSIGN_FIFO_H
