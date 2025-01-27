//
// Created by Yuhao Fan on 3/4/22.
//

#include "Scheduler.h"

//Process *Scheduler::get_next_process() {
//    return nullptr;
//}
//
//void Scheduler::add_process(Process *p) {
//
//}
//
//bool Scheduler::test_preempt(Process *p, int curtime) {
//    return false;
//}
bool Scheduler::add_process(Process *p) {
    return false;
}


bool Scheduler::test_preempt(Process *p, int curtime) {
    return false;
}

void Scheduler::deactivate_process(Process *p) {

}

Process *Scheduler::get_next_process() {
    return nullptr;
}

void Scheduler::showQ() {

}

Process *Scheduler::get_from_expiredQ() {
    return nullptr;
}
