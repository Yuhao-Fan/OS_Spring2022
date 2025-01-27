//
// Created by Yuhao Fan on 3/4/22.
//

#ifndef LAB2_ASSIGN_PROCESS_H
#define LAB2_ASSIGN_PROCESS_H

//#include <stdio.h>      /* printf, scanf, puts, NULL */
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */

class Process {
    public:

        int start_time;
        int cpu_time;
        int remaining_cpu_time;
        int cpu_burst;//static
        int cb;//random number
        int io_burst;//static
        int ib;//random number
        int static_priority;
        int dynamic_priority;
        int state_ts;


        int Finishing_time;
        int Turnaround_time=0;
        int IO_time=0;
        int CPU_wait_time=0;

        int index;

        Process(int index,int start_time, int cpu_time, int cpu_burst, int io_burst, int static_priority, int state_ts) {
            this->index = index;
            this->start_time = start_time;
            this->cpu_time = cpu_time;
            this->remaining_cpu_time = cpu_time;

            this->cpu_burst = cpu_burst;
            this->io_burst = io_burst;
            this->static_priority = static_priority;
            this->dynamic_priority = static_priority-1;
            this->state_ts = state_ts;

            this->Finishing_time=0;
            this->cb=0;
            this->ib=0;
        }
        void compute_cpu_bust();

//    if (proc->state == STATE_RUNNING)


};


#endif //LAB2_ASSIGN_PROCESS_H
