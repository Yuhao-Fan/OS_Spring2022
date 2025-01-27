//
// Created by Yuhao Fan on 4/25/22.
//

#ifndef LAB4_ASSIGN_CLOOK_H
#define LAB4_ASSIGN_CLOOK_H
#include "Scheduler.h"
class CLOOK : public Scheduler {
public:
    CLOOK(){}
    int issue(){

        int min_seek_time = INT_MAX;
        int min_seek_i = -1;

        for(int i = 0; i <(int)IO_queue.size();i++){
            int seek_time=IO_queue[i]->target-current_track;

            if(seek_time>=0&&min_seek_time>seek_time){
                min_seek_time=seek_time;
                min_seek_i=i;
            }
        }

        if(min_seek_i==-1){

            min_seek_time = INT_MAX;
            min_seek_i = -1;

            for(int i = 0; i <(int)IO_queue.size();i++){
                int seek_time=IO_queue[i]->target-0;

                if(seek_time>=0&&min_seek_time>seek_time){
                    min_seek_time=seek_time;
                    min_seek_i=i;
                }
            }
        }
        if(min_seek_i<0)return -1;
        int select=IO_queue[min_seek_i]->index;
        actives.push_back(IO_queue[min_seek_i]);
        IO_queue.erase(IO_queue.begin()+min_seek_i);
        return select;
    }

};
#endif //LAB4_ASSIGN_CLOOK_H
