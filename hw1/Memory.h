//
// Created by Yuhao Fan on 2/7/22.
//

#ifndef OS_HW1_MEMORY_H
#define OS_HW1_MEMORY_H

#include <string>
using namespace std;

class Memory {
public:
//    Memory(int value, string errorMess):m_value(value), m_errorMess(errorMess){}
    Memory(int value, string errorMess){
        this->m_value = value;
        this->m_errorMess = errorMess;

    }

    Memory(){};
    int m_value;
    string m_errorMess;
};


#endif //OS_HW1_MEMORY_H
