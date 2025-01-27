//
// Created by Yuhao Fan on 4/25/22.
//

#ifndef LAB4_ASSIGN_LOOK_H
#define LAB4_ASSIGN_LOOK_H
#include "Scheduler.h"
class LOOK : public Scheduler {
public:
    LOOK(){}
    int issue(){



        int min_seek_time = INT_MAX;
        int min_seek_i = -1;
        for(int i = 0; i <(int)IO_queue.size();i++){
            int seek_time=IO_queue[i]->target-current_track;
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
            for(int i = 0; i <(int)IO_queue.size();i++){
                int seek_time=IO_queue[i]->target-current_track;
                seek_time*=direction;
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
    int direction=1;

};
#endif //LAB4_ASSIGN_LOOK_H
