//
// Created by Yuhao Fan on 3/4/22.
//

#ifndef LAB2_ASSIGN_SCHEDULER_H
#define LAB2_ASSIGN_SCHEDULER_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Process.h"

using namespace std;
class Scheduler {
    public:
        Scheduler(){}
        //The scheduler classes really have to provide only three functions:virtual:
        virtual bool add_process(Process *p);

        virtual Process* get_next_process();
        virtual bool test_preempt(Process *p, int curtime ); // false but for ‘E’
        // tests whether new ready process should preeempt running
        virtual void showQ();
        list<Process*> activeQ;//queue<Process*>



//        queue<Process*> *activeQ, *expiredQ;
        virtual void deactivate_process(Process *p);
        virtual Process* get_from_expiredQ();


};


#endif //LAB2_ASSIGN_SCHEDULER_H
