//
// Created by Yuhao Fan on 4/13/22.
//

#ifndef LAB3_ASSIGN_RANDOM_H
#define LAB3_ASSIGN_RANDOM_H
class Random : public Pager {
public:
    Random(){};
    FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num){

        return &frame_table[rand];
    }
    int hand=0;//pointer
};
#endif //LAB3_ASSIGN_RANDOM_H
