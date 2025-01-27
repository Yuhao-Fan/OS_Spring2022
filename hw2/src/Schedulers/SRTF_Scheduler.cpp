


//
// Created by Yuhao Fan on 3/4/22.
//
#include "SRTF_Scheduler.h"


bool SRTF_Scheduler::add_process(Process *p) {

    if(p->remaining_cpu_time==0){
        //false means insert failed
//        deactivate_process(p);
        expiredQ->push_back(p);
        return false;
    }else{
        activeQ->push_back(p);
        return true;
    }

}



Process *SRTF_Scheduler::get_next_process() {
    if(activeQ->empty()||activeQ->size() == 0) {
        return nullptr;
    }
//    Process const& next= ;

    Process* next;
    next = get_next();

    if(next==NULL) {
        return nullptr;
    }
//    if(next->remaining_cpu_time==0){
//        expiredQ->push_back(activeQ->back());
//        activeQ->pop_back();
//        next = activeQ->back();
//    }

    while(next!=NULL &&next->remaining_cpu_time==0){
        expiredQ->push_back(next);
        activeQ->remove(next);
        if(activeQ->empty()||activeQ->size() == 0) {
            return nullptr;
        }
        next = get_next();

    }
    activeQ->remove(next);
    activeQ->push_front(next);
    return next;
}

void SRTF_Scheduler::deactivate_process(Process *p) {
    for(auto proc:*activeQ){
        if(proc==NULL){
            return;
        }
        if(p->index==proc->index){
            activeQ->remove(proc);
            return;
        }

    }
}

void SRTF_Scheduler::showQ() {

    cout<<"SCHED ("<<activeQ->size()<<"):";//use current transition, rather than future transition in evt
    if(activeQ->size()!=0){
        cout<<" ";
    }


    for(auto proc:*activeQ){
        cout<<" "<<proc->index<<":"<<proc->state_ts;
    }

    cout<<endl;

}

Process *SRTF_Scheduler::get_next() {
    //get next process, even it is finished
    Process* next = activeQ->front();
    for (auto const& i : *activeQ) {
        if(i->remaining_cpu_time<next->remaining_cpu_time){
            next=i;
        }

    }
    return next;

}

