//
// Created by Yuhao Fan on 4/24/22.
//

#ifndef LAB4_ASSIGN_SSTF_H
#define LAB4_ASSIGN_SSTF_H
#include "Scheduler.h"

class SSTF : public Scheduler {
public:
    SSTF(){}
    int issue(){
        int min_seek_time = INT_MAX;
        int min_seek_i = -1;
        for(int i = 0; i <(int)IO_queue.size();i++){
            int seek_time=abs(IO_queue[i]->target-current_track);
            if(min_seek_time>seek_time){
                min_seek_time=seek_time;
                min_seek_i=i;
            }
        }
        if(min_seek_i<0)return -1;
        int select=IO_queue[min_seek_i]->index;
        actives.push_back(IO_queue[min_seek_i]);
        IO_queue.erase(IO_queue.begin()+min_seek_i);
        return select;

    }

};
#endif //LAB4_ASSIGN_SSTF_H
