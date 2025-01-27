//
// Created by Yuhao Fan on 3/15/22.
//

#include "PREPRIO_Scheduler.h"


bool PREPRIO_Scheduler::add_process(Process *p) {
    //if (dynamic prio < 0)
    //  reset and enter into expireQ
    //else
    //  add to activeQ
    if (p->dynamic_priority < 0){
        p->dynamic_priority = p->static_priority-1;
        expiredQ->at(p->dynamic_priority).push_back(p);
    }else{

        activeQ->at(p->dynamic_priority).push_back(p);
    }

    return true;




}



Process *PREPRIO_Scheduler::get_next_process() {
    if(activeQ->empty()) {
        return nullptr;
    }
//    Process const& next= ;

    Process* next;
    next = get_from_runqueue(false);

    if(next==NULL) {
        return nullptr;
    }
//    if(next->remaining_cpu_time==0){
//        expiredQ->push_back(activeQ->back());
//        activeQ->pop_back();
//        next = activeQ->back();
//    }

    while(next!=NULL &&next->remaining_cpu_time==0){
//        expiredQ->push_back(next);
        activeQ->at(next->dynamic_priority).remove(next);
        if(activeQ->empty()) {
            return nullptr;
        }
        next = get_from_runqueue(false);

    }
//    activeQ->remove(next);
//    activeQ->push_front(next);
    return next;
}

void PREPRIO_Scheduler::deactivate_process(Process *p) {
    activeQ->at(p->dynamic_priority).remove(p);
//    expiredQ->at(p->dynamic_priority).push_back(p);

}

void PREPRIO_Scheduler::showQ() {
    //{ [1][][0,2][]} : { [][][][]} :
    if(switched_queue){
        swap(activeQ,expiredQ);
    }
    cout<<"{ ";
    for(int i= priority_num - 1; i >= 0; i--){
        cout<<"[";
        for(auto proc:activeQ->at(i)){
            if(proc!=activeQ->at(i).front()){
                cout<<",";
            }
            cout<<proc->index;
        }
        cout<<"]";

    }
    cout<<"} : { ";
    for(int i= priority_num - 1; i >= 0; i--){
        cout<<"[";
        for(auto proc:expiredQ->at(i)){
            if(proc!=expiredQ->at(i).front()){
                cout<<",";
            }
            cout<<proc->index;
        }
        cout<<"]";

    }
    cout<<"} :"<<endl;
    if(switched_queue){
        swap(activeQ,expiredQ);
        cout<<"switched queues"<<endl;
        switched_queue=false;
    }




}

Process *PREPRIO_Scheduler::get_from_runqueue(bool second_try) {
    //get next process, even it is finished
//    if activeQ not empty
//      pick activeQ[highest prio].front()
//    else
//      swap(activeQ,expiredQ) and try again
    Process* next;
    int highest_prio=-1;
    for(int i= priority_num - 1; i >= 0; i--){
        if(!activeQ->at(i).empty()){
            highest_prio=i;
            break;
        }
    }
    if(highest_prio>=0){

        next = activeQ->at(highest_prio).front();
    }else{
        if(second_try){
            return nullptr;
        }else{
            swap(activeQ,expiredQ);
            switched_queue=true;
            return get_from_runqueue(true);
        }

    }

    return next;

}

Process *PREPRIO_Scheduler::get_from_expiredQ() {

    int highest_prio=-1;
    for(int i= priority_num - 1; i >= 0; i--){
        if(!expiredQ->at(i).empty()){
            highest_prio=i;
            break;
        }
    }
    if(highest_prio>=0){

        return expiredQ->at(highest_prio).front();
    }else{
        return nullptr;
    }

}

