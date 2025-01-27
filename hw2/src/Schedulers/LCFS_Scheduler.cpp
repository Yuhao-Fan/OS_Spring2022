//
// Created by Yuhao Fan on 3/4/22.
//

#include "LCFS_Scheduler.h"

bool LCFS_Scheduler::add_process(Process *p) {

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



Process *LCFS_Scheduler::get_next_process() {
    if(activeQ->empty()||activeQ->size() == 0) {
        return nullptr;
    }
    Process* next = activeQ->back();
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
        next = activeQ->back();
    }
    return next;
}

void LCFS_Scheduler::deactivate_process(Process *p) {
    if(activeQ->empty()||activeQ->size() == 0)return;
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

void LCFS_Scheduler::showQ() {

    cout<<"SCHED ("<<activeQ->size()<<"):";//use current transition, rather than future transition in evt
    if(activeQ->size()!=0){
        cout<<" ";
    }

    for (list<Process*>::reverse_iterator proc=activeQ->rbegin(); proc!=activeQ->rend(); ++proc){
        cout<<" "<<(*proc)->index<<":"<<(*proc)->state_ts;
    }

    cout<<endl;


}
