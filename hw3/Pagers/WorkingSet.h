//
// Created by Yuhao Fan on 4/13/22.
//

#ifndef LAB3_ASSIGN_WORKINGSET_H
#define LAB3_ASSIGN_WORKINGSET_H
class WorkingSet : public Pager {
public:
    WorkingSet(){};
    FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num){
        to=from;
        int stop_i=-1;
        unsigned int oldest=0xFFFFFFFF;
        int oldest_i=to;
        int select=to;
//        if(print){
//
//            cout<<"ASELECT "<<from<<"-"<<(from+MaxFrames-1)%MaxFrames<<" |";
//            int print_i=from;
//            do{
//                PTE *pte=&Procs[frame_table[print_i].proc_num]->page_table[frame_table[print_i].pte_num];
//
//                if(print_i==stop_i){
//                    cout<<"STOP("<<stop_i-from;
//                    break;
//                }
//                print_i=(print_i+1)%MaxFrames;
//            }while((from+MaxFrames)%MaxFrames!=print_i);
//            cout<<" | "<<select<<endl;
//        }


        if(print)cout<<"ASELECT "<<from<<"-"<<(from+MaxFrames-1)%MaxFrames<<" |";
        int scaned_num=0;
        do{
            PTE *pte=&Procs[frame_table[to].proc_num]->page_table[frame_table[to].pte_num];

            if(print)cout<<" "<<to<<"("<<pte->REFERENCED<<" "<<frame_table[to].proc_num<<":"<<frame_table[to].pte_num<<" "<<frame_table[to].time_last_used<<")"<<dec;
            scaned_num++;





            if(pte->REFERENCED==1){
                frame_table[to].time_last_used=instruction_num;//Record current time , reset R
                pte->REFERENCED=0;

            }else {
                if ((unsigned int)instruction_num - frame_table[to].time_last_used > TAU) {
                    stop_i = to;
                    if (print)cout << "STOP(" << scaned_num << ")";
                    break;
                }
                if(frame_table[to].time_last_used<oldest){
                    oldest=frame_table[to].time_last_used;
                    oldest_i=to;
                }
            }
            to=(to+1)%MaxFrames;




        }while(to!=from);

        if(stop_i>-1){
            select=stop_i;
        }else{
            select=oldest_i;
        }
        if(print)cout<<" | "<<select<<endl;

        from= (select+1)%MaxFrames;//next from
        return &frame_table[select];
    }
    int from=0;//pointer
    int to=0;
    unsigned int TAU=49;

};
#endif //LAB3_ASSIGN_WORKINGSET_H
