//
// Created by Yuhao Fan on 4/12/22.
//

#ifndef FRAME_STRUCT_H
#define FRAME_STRUCT_H

typedef struct {
    //FRAME
    unsigned int proc_num:     7;
    unsigned int pte_num:     6;
    unsigned int notFree:         1;
    unsigned int frame_id:     7;
    unsigned int time_last_used:     32;
    unsigned int backup:     11;
} FRAME;
#endif
