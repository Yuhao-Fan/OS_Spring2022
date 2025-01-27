//
// Created by Yuhao Fan on 3/4/22.
//

#ifndef LAB2_ASSIGN_LCFS_SCHEDULER_H
#define LAB2_ASSIGN_LCFS_SCHEDULER_H


#include "../Scheduler.h"
#include <list>

class LCFS_Scheduler : public Scheduler {

public:
    LCFS_Scheduler(){
        activeQ=new list<Process*>;
        expiredQ=new list<Process*>;
    }

    //The scheduler classes really have to provide only three functions:
    bool add_process(Process *p);
    Process* get_next_process();
    bool test_preempt(Process *p, int curtime ){
        return false;
    }; // false but for ‘E’
    void deactivate_process(Process *p);
    void showQ();
    list<Process*> *activeQ, *expiredQ;
    // tests whether new ready process should preeempt running
//    queue<Process*> RUN_QUEUE;//queue<Process*>
private:

};


#endif //LAB2_ASSIGN_LCFS_SCHEDULER_H
