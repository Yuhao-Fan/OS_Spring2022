//
// Created by Yuhao Fan on 4/25/22.
//

#ifndef LAB4_ASSIGN_FLOOK_H
#define LAB4_ASSIGN_FLOOK_H
#include "Scheduler.h"
class FLOOK : public Scheduler {
public:
    FLOOK(){}
    int issue(){


        if(active_queue.empty()){
            swap(active_queue,IO_queue);
        }
        int min_seek_time = INT_MAX;
        int min_seek_i = -1;
        for(int i = 0; i <(int)active_queue.size();i++){
            int seek_time=active_queue[i]->target-current_track;
            seek_time*=direction;
            if(seek_time>=0&&min_seek_time>seek_time){
                min_seek_time=seek_time;
                min_seek_i=i;
            }
        }

        if(min_seek_i==-1){
            min_seek_time = INT_MAX;
            min_seek_i = -1;
            direction=-direction;
            for(int i = 0; i <(int)active_queue.size();i++){
                int seek_time=active_queue[i]->target-current_track;
                seek_time*=direction;
                if(seek_time>=0&&min_seek_time>seek_time){
                    min_seek_time=seek_time;
                    min_seek_i=i;
                }
            }
        }
        if(min_seek_i<0)return -1;
        int select=active_queue[min_seek_i]->index;
        actives.push_back(active_queue[min_seek_i]);
        active_queue.erase(active_queue.begin()+min_seek_i);
        return select;

    }
    int direction=1;
    //add-queue=IO_queue;
    deque<Request*> active_queue;


};
#endif //LAB4_ASSIGN_FLOOK_H
