//
// Created by Yuhao Fan on 4/13/22.
//

#ifndef LAB3_ASSIGN_CLOCK_H
#define LAB3_ASSIGN_CLOCK_H
#include<iostream>
using namespace std;
class Clock : public Pager {
public:
    Clock(){};
    FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num){
        int select_num=0;
        if(hand==tail){
            cout<<"";

            do{
                PTE* pte = &Procs[frame_table[tail].proc_num]->page_table[frame_table[tail].pte_num];
                if(pte->REFERENCED==0){
                    hand=tail;
                    int selected = hand;
                    hand= (hand+1)%MaxFrames;
                    return &frame_table[selected];
                }
                pte->REFERENCED=0;
//                pte->MODIFIED=0;
                select_num++;
                tail=(tail+1)%MaxFrames;

            }while(hand!=tail);

        }
//        PTE* pte = &Procs[frame_table[tail].proc_num]->page_table[frame_table[tail].pte_num];
        int selected = hand;
        while(Procs[frame_table[hand].proc_num]->page_table[frame_table[hand].pte_num].REFERENCED==1){
            Procs[frame_table[hand].proc_num]->page_table[frame_table[hand].pte_num].REFERENCED=0;
            hand= (hand+1)%MaxFrames;
            selected=(selected+1)%MaxFrames;

        }
        hand= (hand+1)%MaxFrames;
        return &frame_table[selected];
    }
    int hand=0;//head
    int tail=0;
};
#endif //LAB3_ASSIGN_CLOCK_H
