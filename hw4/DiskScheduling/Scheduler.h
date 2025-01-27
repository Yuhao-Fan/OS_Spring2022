//
// Created by Yuhao Fan on 4/24/22.
//

#ifndef LAB4_ASSIGN_SCHEDULER_H
#define LAB4_ASSIGN_SCHEDULER_H

#include <deque>
#include <cmath>//
#include <limits.h>
#include "../Request.h"
using namespace std;

class Scheduler {
public:
    Scheduler(){}
    virtual int issue()=0;
    deque<Request*> IO_queue;
    deque<Request*> actives;
    int current_track=0;

};
#endif //LAB4_ASSIGN_SCHEDULER_H
