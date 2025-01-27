//
// Created by Yuhao Fan on 3/6/22.
//

#ifndef LAB2_ASSIGN_DES_LAYER_H
#define LAB2_ASSIGN_DES_LAYER_H


#include "Event.h"
#include <set>

using namespace std;
class DES_Layer {
    //Discrete Event Simulation

public:
    DES_Layer(){

    }
    multiset<Event> evt_SET;
    multiset<Event>::iterator get_event();
    multiset<Event>::iterator have_preemptor();
    bool have_block();
    void put_event(Event evt);
    void rm_event(multiset<Event>::iterator it);
    int get_next_event_time();

};


#endif //LAB2_ASSIGN_DES_LAYER_H
