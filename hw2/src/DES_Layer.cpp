//
// Created by Yuhao Fan on 3/6/22.
//

#include "DES_Layer.h"

multiset<Event>::iterator DES_Layer::get_event() {

    multiset<Event>::iterator it = evt_SET.begin();
    return it;
}

void DES_Layer::put_event(Event evt) {
    evt_SET.insert(evt);
}

void DES_Layer::rm_event(multiset<Event>::iterator it) {
    evt_SET.erase(it);
}

int DES_Layer::get_next_event_time() {
    multiset<Event>::iterator it = evt_SET.begin();
    return it->Timestamp;
}

multiset<Event>::iterator DES_Layer::have_preemptor() {
    if(evt_SET.size() == 0)    return evt_SET.end();
    for (auto it = evt_SET.begin(); it != evt_SET.end(); it++){
        if(it->newstate==PREEMPT||it->newstate==BLOCK){
            return it;
        }
    }
    return evt_SET.end();



}

bool DES_Layer::have_block() {
    for (auto it = evt_SET.begin(); it != evt_SET.end(); it++){
        if(it->newstate==PREEMPT||it->newstate==BLOCK){
            return true;
        }
    }
    return false;
}
