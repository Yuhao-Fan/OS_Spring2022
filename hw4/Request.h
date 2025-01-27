//
// Created by Yuhao Fan on 4/25/22.
//

#ifndef LAB4_ASSIGN_REQUEST_H
#define LAB4_ASSIGN_REQUEST_H
class Request{
public:
    Request(int time_step,int target,int index){
        this->time_step = time_step;
        this->target = target;
        this->index = index;
        start_time=0;
        end_time=0;
        complete_time=0;
    }
    int index;
    int time_step;
    int target;
    int start_time;
    int end_time;
    int complete_time;
};
#endif //LAB4_ASSIGN_REQUEST_H
