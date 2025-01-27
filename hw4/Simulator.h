//
// Created by Yuhao Fan on 4/24/22.
//

#ifndef LAB4_ASSIGN_SIMULATOR_H
#define LAB4_ASSIGN_SIMULATOR_H

#include "DiskScheduling/FLOOK.h"
#include "DiskScheduling/CLOOK.h"
#include "DiskScheduling/LOOK.h"
#include "DiskScheduling/FIFO.h"
#include "DiskScheduling/SSTF.h"
#include "DiskScheduling/Scheduler.h"

#include "Request.h"
#include <iomanip>//setw
#include <string>//string strtok
#include <iostream>//cout
#include <fstream>//ifstream
#include <vector>//vector
#include <unordered_set>
#include <unordered_map>//unordered_map
#include <deque>
#include <cstring>//strcpy
#include <algorithm>//sort
#include <cmath>//abs


using namespace std;
class Simulator {
public:


    Simulator(string input_name, char algo, bool trace, bool queue, bool flook){
        this->trace=trace;
        this->trace=queue;
        this->trace=flook;
        this->input_name=input_name;

        Read_Input(input_name);


//        this->MaxFrames=MAX_FRAMES;
//        frame_table=new FRAME[MaxFrames];
//        for(int i=0;i<MaxFrames;i++){
//            free_frames.push_back(&frame_table[i]);//initially
//            frame_table[i].frame_id=i;
//            frame_table[i].notFree=0;
//        }
//        string ops=options;
//        for(char option:ops){
//            optionSet.insert(option);
//        }


        switch(algo){
            case 'i':{

                THE_SCHED = new FIFO();

                break;
            }
            case 'j':{

                THE_SCHED = new SSTF();

                break;
            }
            case 's':{

                THE_SCHED = new LOOK();

                break;
            }
            case 'c':{

                THE_SCHED = new CLOOK();//Enhanced Second Chance

                break;
            }
            case 'f':{

                THE_SCHED = new FLOOK();
                break;
            }

            default: cerr<<"Algorithm name is not exist "<<endl;
        }

    }
    void Simulation();

    void Print_result();
private:
    bool trace=false, queue=false, flook=false;
    string input_name;
    Scheduler* THE_SCHED;
    void Read_Input(string input_name);
    char* readNewLine(char* newline);
    deque<Request*> ops;
    int total_time=0, tot_movement=0,  max_waittime=0;
    double avg_turnaround=0.0, avg_waittime=0.0;



};


#endif //LAB4_ASSIGN_SIMULATOR_H
