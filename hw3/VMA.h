//
// Created by Yuhao Fan on 4/10/22.
//

#ifndef LAB3_ASSIGN_VMA_H
#define LAB3_ASSIGN_VMA_H


class VMA {
public:
    VMA(){

    }
    VMA(int start_vpage,int end_vpage,bool write_protected,bool file_mapped){

    }
    int start_vpage;
    int end_vpage; // (note the VMA has (end_vpage – start_vpage + 1) virtual pages )
    bool write_protected; // binary whether the VMA is write protected or not
    bool file_mapped; // binary to indicate whether the VMA is mapped to a file or not


};


#endif //LAB3_ASSIGN_VMA_H
