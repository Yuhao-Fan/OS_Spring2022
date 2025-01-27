//
// Created by Yuhao Fan on 3/15/22.
//
#include "../Scheduler.h"
#include <vector>
//#include <list>
#ifndef LAB2_ASSIGN_PRIO_SCHEDULER_H
#define LAB2_ASSIGN_PRIO_SCHEDULER_H



class PRIO_Scheduler: public Scheduler {
public:
    PRIO_Scheduler(int priority_num){
        this->priority_num = priority_num;
        activeQ = new vector<list<Process*>>(priority_num);
        expiredQ=   new vector<list<Process*>>(priority_num);

    }

    //The scheduler classes really have to provide only three functions:
    bool add_process(Process *p);
    Process* get_next_process();
    bool test_preempt(Process *p, int curtime ){
        return false;
    }; // false but for ‘E’
    void deactivate_process(Process *p);
    void showQ();
    Process* get_from_runqueue(bool second_try);
    vector<list<Process*>> *activeQ;
    vector<list<Process*>> *expiredQ;
    // tests whether new ready process should preeempt running
//    queue<Process*> RUN_QUEUE;//queue<Process*>
private:
    int priority_num;
    bool switched_queue=false;

};


#endif //LAB2_ASSIGN_PRIO_SCHEDULER_H
