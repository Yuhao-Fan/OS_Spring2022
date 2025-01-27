//
// Created by Yuhao Fan on 4/13/22.
//

#ifndef LAB3_ASSIGN_AGING_H
#define LAB3_ASSIGN_AGING_H
class Aging : public Pager {
public:
    Aging(){};
    FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num){
        to=from;
//        int select;
        unsigned int min_age=0xFFFFFFFF;
        int min_age_i=-1;
        do{
            PTE *pte=&Procs[frame_table[to].proc_num]->page_table[frame_table[to].pte_num];
            if(Ages[to]==0){
                Ages[to] = 0x80000000;
            }else {
                Ages[to]= (Ages[to] >> 1);
                if(pte->REFERENCED==1){
                    Ages[to]= (Ages[to] | 0x80000000);
                }
            }
            pte->REFERENCED=0;

            if(Ages[to]<min_age){
                min_age=Ages[to];
                min_age_i=to;
            }



            to=(to+1)%MaxFrames;
        }while(to!=from);


        if(print){

            cout<<"ASELECT "<<from<<"-"<<(from+MaxFrames-1)%MaxFrames<<" |";
            int print_i=from;

            do{
                cout<<" "<<print_i<<":"<<hex<<Ages[print_i]<<dec;
                print_i=(print_i+1)%MaxFrames;
            }while((from+MaxFrames)%MaxFrames!=print_i);
            cout<<" | "<<min_age_i<<endl;
        }
        from= (min_age_i+1)%MaxFrames;//next from
        return &frame_table[min_age_i];
    }
    int from=0;//pointer
    int to=0;

};

#endif //LAB3_ASSIGN_AGING_H
