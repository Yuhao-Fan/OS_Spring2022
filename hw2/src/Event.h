//
// Created by Yuhao Fan on 3/6/22.
//

#ifndef LAB2_ASSIGN_EVENT_H
#define LAB2_ASSIGN_EVENT_H


#include "Process.h"
#include <string>
using namespace std;
typedef enum { CREATED, READY, RUNNG , BLOCK ,PREEMPT} event_state_type;

typedef enum { TRANS_TO_READY , TRANS_TO_RUNNG , TRANS_TO_BLOCK , TRANS_TO_PREEMPT } event_trans_type;

class Event {
public:
    Event(int Timestamp, Process *evtProcess,event_state_type oldstate,
    event_state_type newstate,event_trans_type transition){
        this->Timestamp = Timestamp;
        this->evtProcess = evtProcess;
        this->oldstate = oldstate;
        this->newstate = newstate;
        this->transition = transition;
//        transition = TRANS_TO_READY;

    }
    Event(){
    }
    void assign_newstate(event_state_type newstate) {
        this->newstate = newstate;
    };

    int Timestamp;
    Process *evtProcess;

    event_state_type oldstate;
    event_state_type newstate;
    // Time ordered, and FIFO if same time
    bool operator<(const Event &evt) const { return this->Timestamp < evt.Timestamp; }
    event_trans_type transition;
};


#endif //LAB2_ASSIGN_EVENT_H
