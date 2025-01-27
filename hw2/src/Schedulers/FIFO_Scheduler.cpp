//
// Created by Yuhao Fan on 3/4/22.
//

#include "FIFO_Scheduler.h"

bool FIFO_Scheduler::add_process(Process *p) {
//    if(){
//        expiredQ->push_back(activeQ->front());
////        activeQ->pop();
//        activeQ->erase(activeQ->begin());
//    }
//    activeQ->push_back(p);

    if(p->remaining_cpu_time==0){
        //false means insert failed
//        deactivate_process(p);
//        expiredQ->push_back(p);
        return false;
    }else{
        try{
            activeQ->push_back(p);
        }catch(const exception& e){
            cout <<"e.what()" <<e.what();
        }

        return true;
    }
}



Process *FIFO_Scheduler::get_next_process() {
    if(activeQ->empty()||activeQ->size() == 0) {
        return nullptr;
    }
    Process* next = activeQ->front();
//    if(next==NULL) {
//        return nullptr;
//    }
    while(next!=NULL &&next->remaining_cpu_time==0){
//        expiredQ->push_back(next);
//        activeQ->pop();
        activeQ->remove(next);
        if(activeQ->empty()||activeQ->size() == 0) {
            return nullptr;
        }
        next = activeQ->front();
    }
    return next;
}

void FIFO_Scheduler::deactivate_process(Process *p) {
//    if(activeQ->empty()||activeQ->size() == 0)return;
//    for (int i=0;i<activeQ->size();i++){
//        if(p->index==activeQ->at(i)->index){
//            activeQ->erase(activeQ->begin()+i);
//        }
//    }
//    for (auto it=activeQ->begin(); it!=activeQ->end(); it++){
//        if(p->index==(*it)->index){
//            try{
//                activeQ->erase(it);
//            }catch(const exception& e){
//                cout << e.what();
//            }
//
//        }
//    }

    for(auto proc:*activeQ){
        if(proc==nullptr){
            return;
        }
        if(p->index==proc->index){
            activeQ->remove(proc);
            return;
        }

    }

}

void FIFO_Scheduler::showQ() {

    cout<<"SCHED ("<<activeQ->size()<<"):";//use current transition, rather than future transition in evt
    if(activeQ->size()!=0){
        cout<<" ";
    }
    for(auto proc:*activeQ){
        cout<<" "<<proc->index<<":"<<proc->state_ts;
    }

    cout<<endl;

}

//void FIFO_Scheduler::expire_process(Process *p) {
//
//}
