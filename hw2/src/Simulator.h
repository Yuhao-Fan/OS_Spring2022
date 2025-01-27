//
// Created by Yuhao Fan on 3/6/22.
//

#ifndef LAB2_ASSIGN_SIMULATOR_H
#define LAB2_ASSIGN_SIMULATOR_H

#include <iostream>
#include <cstring>//strcpy
#include <iomanip>//setw
#include <algorithm>//sort
#include "Event.h"
#include "Process.h"
#include "DES_Layer.h"
#include "Schedulers/FIFO_Scheduler.h"
#include "Schedulers/LCFS_Scheduler.h"
#include "Schedulers/RR_Scheduler.h"
#include "Schedulers/SRTF_Scheduler.h"
#include "Schedulers/PRIO_Scheduler.h"
#include "Schedulers/PREPRIO_Scheduler.h"
#include <string>
#include <vector>

const string event_states[] ={"CREATED","READY", "RUNNG","BLOCK","PREEMPT"};
class Simulator {
public:
    Simulator(string input_name, string rfile_name, char sched_name,int cmd_quantum,int cmd_maxprio){
        ofs=0;
        CALL_SCHEDULER = false;
        CURRENT_RUNNING_PROCESS = nullptr;
        time_cpubusy=0, time_iobusy=0, num_processes=0, finishtime=0;
        sum_turnaround=0;
        read_randvals(rfile_name);

        des_ptr = new DES_Layer();
        max_static_priority=cmd_maxprio;
        Read_Processes(input_name);

        quantum=cmd_quantum;
//        Print_result();

        switch(sched_name){
            case 'F':{

                THE_SCHEDULER = new FIFO_Scheduler();
                this->sched_sname= "FCFS";
                break;
            }
            case 'L':{

                THE_SCHEDULER = new LCFS_Scheduler();
                this->sched_sname= "LCFS";
                break;
            }
            case 'R':{

                THE_SCHEDULER = new RR_Scheduler();
                this->sched_sname= "RR";
                break;
            }
            case 'S':{

                THE_SCHEDULER = new SRTF_Scheduler();
                this->sched_sname= "SRTF";
                break;
            }
            case 'P':{

                THE_SCHEDULER = new PRIO_Scheduler(max_static_priority);
                this->sched_sname= "PRIO";
                break;
            }
            case 'E':{

                THE_SCHEDULER = new PREPRIO_Scheduler(max_static_priority);
                this->sched_sname= "PREPRIO";
                break;
            }

            default: cerr<<"scheduler name is not exist "<<endl;
        }


    }

    Scheduler* THE_SCHEDULER;
    void Simulation(bool verbose, bool trace, bool eventQ, bool preempt);
    DES_Layer* des_ptr;
    void decode_event(Event* evt);
    void action();
    bool CALL_SCHEDULER;
    Process* CURRENT_RUNNING_PROCESS;
    void Print_result();
    string sched_sname;



private:
    vector<Process*> proc_list;
    int ofs;
    int time_cpubusy, time_iobusy, num_processes, finishtime;
    int sum_turnaround,sum_cpu_wait=0;

    int *randvals;
    int rand_num;
    int myrandom(int maxprio);
    int quantum;
    int max_static_priority=4;
    void read_randvals(string rfile_name);

    void Read_Processes(string input_name);


    bool show_eventQ=false;
    bool show_event_execution=false;
    bool show_verbose=false;
    bool show_preempt=false;

    void showEventQ();
    void showEventQ_before(Event* evt);
    void showEventQ_after();
    void traceEventExecution();
    void showVerbose(event_state_type oldstate,event_state_type newstate,int CURRENT_TIME,Process *proc,int timeInPrevState);
    void showVerboseRight(event_state_type newstate,int burst_time, Process *proc);

    vector<vector<int>> io_intervals;
    int get_sum_io_busytime();//input io_intervals,output sum of merged_io_intervals
};


#endif //LAB2_ASSIGN_SIMULATOR_H
