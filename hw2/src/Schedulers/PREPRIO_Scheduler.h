//
// Created by Yuhao Fan on 3/15/22.
//
#include "../Scheduler.h"
#include <vector>
#ifndef LAB2_ASSIGN_PREPRIO_SCHEDULER_H
#define LAB2_ASSIGN_PREPRIO_SCHEDULER_H


class PREPRIO_Scheduler: public Scheduler {
public:
    PREPRIO_Scheduler(int priority_num){
        this->priority_num = priority_num;
        activeQ = new vector<list<Process*>>(priority_num);
        expiredQ= new vector<list<Process*>>(priority_num);

    }

    //The scheduler classes really have to provide only three functions:
    bool add_process(Process *p);
    Process* get_next_process();
    bool test_preempt(Process *preemptor, int curtime ){
        Process* next=get_from_runqueue(true);//from back to get process just added

        if(preemptor->dynamic_priority>next->dynamic_priority){
            return true;
        }
        return false;
    }; // false but for ‘E’
    void deactivate_process(Process *p);
    void showQ();
    Process* get_from_runqueue(bool second_try);
    Process* get_from_expiredQ();
    vector<list<Process*>> *activeQ;
    vector<list<Process*>> *expiredQ;
    // tests whether new ready process should preeempt running
//    queue<Process*> RUN_QUEUE;//queue<Process*>
private:
    int priority_num;
    bool switched_queue=false;
};


#endif //LAB2_ASSIGN_PREPRIO_SCHEDULER_H
