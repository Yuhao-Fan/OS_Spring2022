//
// Created by Yuhao Fan on 4/13/22.
//

#ifndef LAB3_ASSIGN_NRU_H
#define LAB3_ASSIGN_NRU_H
class NRU : public Pager {
public:
    NRU(){};
    FRAME* select_victim_frame(FRAME* frame_table,int MaxFrames,vector<Process*> Procs,int rand,bool print,int instruction_num){
        bool reset_r=false;
        if(instruction_num-last_reset>=50){
            last_reset=instruction_num;
            reset_r=true;
        }

//        int selected = hand;
        scan=hand;
        int start=hand;
        int scan_num=0;
//        int* Class_num = new int[MaxFrames];
        int min_Class=4;
        int min_Class_i=0;
        while(scan_num<MaxFrames){
            PTE* pte = &Procs[frame_table[scan].proc_num]->page_table[frame_table[scan].pte_num];
            int Class=2*(int)pte->REFERENCED+(int)pte->MODIFIED;

            if(Class==0){
                if(print){

                    cout<<"ASELECT "<<start<<" "<<reset_r<<" "<<scan<<endl;
                }
                hand= (scan+1)%MaxFrames;

                if(reset_r){
                    for(int i=0;i<MaxFrames;i++){
                        PTE* pte = &Procs[frame_table[i].proc_num]->page_table[frame_table[i].pte_num];
                        pte->REFERENCED=0;
                    }

                }

                return &frame_table[scan];

            }else{
                if(Class<min_Class){
                    min_Class=Class;
                    min_Class_i=scan;
                }
//                Class_num[scan]=Class;
            }
            scan= (scan+1)%MaxFrames;
            scan_num++;
        }
        hand= (min_Class_i+1)%MaxFrames;
        if(print){

            cout<<"ASELECT "<<start<<" "<<reset_r<<" "<<min_Class_i<<endl;
        }
        if(reset_r){
            for(int i=0;i<MaxFrames;i++){
                PTE* pte = &Procs[frame_table[i].proc_num]->page_table[frame_table[i].pte_num];
                pte->REFERENCED=0;
            }

        }
        return &frame_table[min_Class_i];


    }
    int hand=0;//pointer
    int scan=0;
    int last_reset=-1;
};

#endif //LAB3_ASSIGN_NRU_H
