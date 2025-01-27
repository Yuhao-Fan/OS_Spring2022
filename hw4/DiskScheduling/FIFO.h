//
// Created by Yuhao Fan on 4/24/22.
//

#ifndef LAB4_ASSIGN_FIFO_H
#define LAB4_ASSIGN_FIFO_H

#include "Scheduler.h"
class FIFO : public Scheduler {
public:
    FIFO(){}
    int issue(){
        if(IO_queue.empty())return -1;
        int issue_i=IO_queue.front()->index;
        actives.push_back(IO_queue.front());
        IO_queue.pop_front();
        return issue_i;

    }

};
#endif //LAB4_ASSIGN_FIFO_H
