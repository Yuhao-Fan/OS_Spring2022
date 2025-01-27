//
// Created by Yuhao Fan on 4/10/22.
//

#ifndef LAB3_ASSIGN_PROCESS_H
#define LAB3_ASSIGN_PROCESS_H

#include "VMA.h"

struct PTE{
    //PTE
    unsigned int frame_num:     7;//physical_frame_number
    unsigned int Valid:         1;
    unsigned int REFERENCED:    1;
    unsigned int MODIFIED:      1;
    unsigned int PAGEDOUT:      1;
    unsigned int WRITE_PROTECT: 1;

    unsigned int isFileMapped:  1;
    unsigned int Accessable:  1;
    PTE(): frame_num(0),Valid(0),REFERENCED(0),MODIFIED(0),PAGEDOUT(0),WRITE_PROTECT(0),isFileMapped(0),Accessable(0){};
} ; // can only be total of 32-bit size and will check on this
struct Pstat{
    //Pstat
    long unsigned int unmaps;
    long unsigned int maps;
    long unsigned int ins;
    long unsigned int outs;
    long unsigned int fins;
    long unsigned int fouts;
    long unsigned int zeros;
    long unsigned int segv;
    long unsigned int segprot;
    Pstat(): unmaps(0),maps(0),ins(0),outs(0),fins(0),fouts(0),zeros(0),segv(0),segprot(0){};
} ;


class Process {
public:
    Process(int vma_num){
        vmas = new VMA[vma_num];
    }
    VMA* vmas;
    static const int MAX_VPAGES = 64;
    PTE page_table[MAX_VPAGES];// a per process array of fixed size=64 of pte_t not pte_t pointers !
    int pid;
};


#endif //LAB3_ASSIGN_PROCESS_H
