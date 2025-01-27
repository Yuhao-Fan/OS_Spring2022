//
// Created by Yuhao Fan on 4/9/22.
//


#ifndef LAB3_ASSIGN_SIMULATOR_H
#define LAB3_ASSIGN_SIMULATOR_H

#include "Pagers/Pager.h"
#include "Pagers/FIFO.h"
#include "Pagers/Random.h"
#include "Pagers/Clock.h"
#include "Pagers/NRU.h"
#include "Pagers/Aging.h"
#include "Pagers/WorkingSet.h"

#include "Frame.h"
#include "Process.h"
#include <string>//string strtok
#include <iostream>//cout
#include <fstream>//ifstream
#include <vector>//vector
#include <unordered_set>
#include <unordered_map>//unordered_map
#include <deque>
#include <cstring>//strcpy
#include <algorithm>//sort
using namespace std;



class Simulator {
public:
    Simulator(string input_name,string rfile_name,int MAX_FRAMES,char pager,char *options){

        read_randvals(rfile_name);
        Read_Input(input_name);
        this->MaxFrames=MAX_FRAMES;
        frame_table=new FRAME[MaxFrames];
        for(int i=0;i<MaxFrames;i++){
            free_frames.push_back(&frame_table[i]);//initially
            frame_table[i].frame_id=i;
            frame_table[i].notFree=0;
        }
        string ops=options;
        for(char option:ops){
            optionSet.insert(option);
        }
//        Costs[""]

        switch(pager){
            case 'f':{

                THE_PAGER = new FIFO();
                this->pager_name= "FCFS";
                break;
            }
            case 'r':{

                THE_PAGER = new Random();
                this->pager_name= "Random";
                break;
            }
            case 'c':{

                THE_PAGER = new Clock();
                this->pager_name= "Clock";
                break;
            }
            case 'e':{

                THE_PAGER = new NRU();//Enhanced Second Chance
                this->pager_name= "NRU";
                break;
            }
            case 'a':{

                THE_PAGER = new Aging();
                this->pager_name= "Aging";
                break;
            }
            case 'w':{

                THE_PAGER = new WorkingSet();
                this->pager_name= "WorkingSet";
                break;
            }

            default: cerr<<"pager name is not exist "<<endl;
        }
        THE_PAGER->reset_age(MaxFrames);
    }
    void Simulation();

    void Print_result();

private:
    unordered_set<char> optionSet;
    unsigned int proc_num=0;
    void Read_Input(string input_name);
    char* readNewLine(char* newline);
    char operation='n';
    int vpage=-1;

    unsigned int instruction_i=0;
    unsigned int instruction_num=0;
    bool get_next_instruction(char &operation, int &vpage);
    vector<pair<char,int>> instructions;
    Pager* THE_PAGER;
    string pager_name;
    FRAME* get_frame();

    FRAME* frame_table;


    Process* current_process;
    int current_process_id=0;
    int MaxFrames=16;

    deque<FRAME*> free_frames;
    int front_id=0;
    FRAME *allocate_frame_from_free_list();

    vector<Process*> Procs;

    int ofs=0;
    int *randvals;
    int rand_num;
    int myrandom(int max_num);
    void read_randvals(string rfile_name);

    void OhNoOutput(FRAME *newframe,PTE* oldPTE,PTE* newPTE);//O
    void OhNoOutput();
    void OUT_FOUT(FRAME *newframe,PTE* oldPTE);
    void PagetableOutput();//P
    void FrameTableOutput();//F
    void ProcStatisticOutput();//S

    void PrintCurrPT();//x
    void PrintAllPT();//y
    void PrintFrame();//f
    void PrintAging();//a

    void ResetPTE(PTE *pte);

    unordered_map<int,PTE> swapped_out_pages;
    unordered_map<int,PTE> files;

    unsigned long inst_count=0;
    unsigned long ctx_switches=0;
    unsigned long process_exits=0;
    unsigned long long cost=0;
    vector<Pstat> Pstats;
    unordered_map<string,int> Costs;
};


#endif //LAB3_ASSIGN_SIMULATOR_H
