//
// Created by Yuhao Fan on 4/9/22.
//

#include "Simulator.h"
void Simulator::OUT_FOUT(FRAME *newframe,PTE *oldPTE) {
    if(oldPTE->MODIFIED){
        //OUT
        if(oldPTE->isFileMapped){
            //FOUT
            cout<<" FOUT"<<endl;
            Pstats[newframe->proc_num].fouts++;
            cost+=2400;

            int rtag=newframe->pte_num;
            int ltag=newframe->proc_num<<16;
            int tag =ltag+rtag;
            PTE out;
            out.frame_num=oldPTE->frame_num;
            out.Valid=oldPTE->Valid;
            out.REFERENCED=oldPTE->REFERENCED;
            out.MODIFIED=0;
            out.WRITE_PROTECT=oldPTE->WRITE_PROTECT;
            out.isFileMapped=oldPTE->isFileMapped;
            out.Accessable=oldPTE->Accessable;
            out.PAGEDOUT=oldPTE->PAGEDOUT;
            files.insert({tag,out});

        }else{

            oldPTE->PAGEDOUT=1;


            PTE out;
            out.frame_num=oldPTE->frame_num;
            out.Valid=oldPTE->Valid;
            out.REFERENCED=oldPTE->REFERENCED;
            out.MODIFIED=0;
            out.WRITE_PROTECT=oldPTE->WRITE_PROTECT;
            out.isFileMapped=oldPTE->isFileMapped;
            out.Accessable=oldPTE->Accessable;
            out.PAGEDOUT=oldPTE->PAGEDOUT;

            int rtag=newframe->pte_num;
            int ltag=newframe->proc_num<<16;
            int tag =ltag+rtag;
            swapped_out_pages.insert({tag,out});
            cout<<" OUT"<<endl;
            Pstats[newframe->proc_num].outs++;
            cost+=2700;
        }

    }
}

void Simulator::OhNoOutput(FRAME *newframe,PTE* oldPTE,PTE* newPTE) {
//    cout<<instruction_i<<": ==> "<<instructions[instruction_i].first<<" "<<instructions[instruction_i].second<<endl;
    //-> figure out if/what to do with old frame if it was mapped
    if (!optionSet.count('O'))return;


    if(newframe->notFree){
        //UNMAP
        cout<<" UNMAP "<<newframe->proc_num<<":"<<newframe->pte_num<<endl;
        Pstats[newframe->proc_num].unmaps++;
        cost+=400;
    }
    if(newframe->notFree==1){
        OUT_FOUT(newframe,oldPTE);


    }
    if(newframe->notFree==1){
        if(oldPTE->PAGEDOUT==1){
            oldPTE->MODIFIED=1;
        }
//            oldPTE->REFERENCED=0;
//            oldPTE->MODIFIED=1;
//            ResetPTE(oldPTE);
    }
    if(newPTE->PAGEDOUT){
        //IN
        cout<<" IN"<<endl;
        Pstats[current_process_id].ins++;
        cost+=3100;

        int rtag=vpage;
        int ltag=current_process_id<<16;
        int tag =ltag+rtag;
        PTE pte=swapped_out_pages[tag];
        current_process->page_table[vpage]=pte;

//        if(operation=='w'){
//            newPTE->MODIFIED=1;
//        }else if(operation=='r'){
//            newPTE->MODIFIED=0;
//        }

    }else if(newPTE->isFileMapped){
        //FIN
        cout<<" FIN"<<endl;
        Pstats[current_process_id].fins++;
        cost+=2800;

        int rtag=vpage;
        int ltag=current_process_id<<16;
        int tag =ltag+rtag;
        PTE pte=files[tag];
        current_process->page_table[vpage]=pte;

    }else{
        //ZERO

        cout<<" ZERO"<<endl;
        Pstats[current_process_id].zeros++;
        cost+=140;
        if(newframe->notFree==1){
//            if(oldPTE->PAGEDOUT==1){
//                oldPTE->MODIFIED=1;
//            }
//            oldPTE->REFERENCED=0;
//            oldPTE->MODIFIED=1;
            ResetPTE(oldPTE);
        }


    }

    //MAP

    cout<<" MAP "<<newframe->frame_id<<endl;//
    //age has to be reset to 0 on each MAP operation.
    THE_PAGER->Ages[newframe->frame_id]=0x00000000;
    Pstats[current_process_id].maps++;
    cost+=300;


}
void Simulator::OhNoOutput() {
    if (!optionSet.count('O'))return;
    cout<<instruction_i<<": ==> "<<instructions[instruction_i].first<<" "<<instructions[instruction_i].second<<endl;
}
void Simulator::Simulation() {


//    for

    while (get_next_instruction(operation, vpage)) {
        // handle special case of “c” and “e” instruction
        OhNoOutput();

        inst_count++;


        if(operation=='c'){
            ctx_switches++;
            cost+=130;

            current_process=Procs[vpage];
            current_process_id=vpage;

            instruction_i++;
            continue;
        }else if(operation=='e'){
            cout<<"EXIT current process "<<current_process_id<<endl;

            vector<int> unmaps;
            for(int i=0;i<MaxFrames;i++){
                if(frame_table[i].notFree&&(int)frame_table[i].proc_num==current_process_id){
                    unmaps.push_back((int)frame_table[i].pte_num);
                    frame_table[i].proc_num=0;
                    frame_table[i].pte_num=0;
                    frame_table[i].notFree=0;

                }
            }
            sort(unmaps.begin(), unmaps.end());
            //unmap and outs
            for(int i=0;i<(int)unmaps.size();i++){

                cout<<" UNMAP "<<current_process_id<<":"<<unmaps[i]<<endl;
                Pstats[current_process_id].unmaps++;
                cost+=400;

                //fouts
                PTE* oldPTE =&Procs[current_process_id]->page_table[unmaps[i]];
                FRAME* free_frame=&frame_table[oldPTE->frame_num];

                if(oldPTE->MODIFIED) {
                    //OUT
                    if (oldPTE->isFileMapped) {
                        //FOUT
                        cout << " FOUT" << endl;
                        Pstats[current_process_id].fouts++;
                        cost += 2400;

                        int rtag = free_frame->pte_num;
                        int ltag = current_process_id << 16;
                        int tag = ltag + rtag;
                        PTE out;
                        out.frame_num = oldPTE->frame_num;
                        out.Valid = oldPTE->Valid;
                        out.REFERENCED = oldPTE->REFERENCED;
                        out.MODIFIED = 0;
                        out.WRITE_PROTECT = oldPTE->WRITE_PROTECT;
                        out.isFileMapped = oldPTE->isFileMapped;
                        out.Accessable = oldPTE->Accessable;
                        out.PAGEDOUT = oldPTE->PAGEDOUT;
                        files.insert({tag, out});

                    }
                }
//                OUT_FOUT(free_frame,pte);

                //add back to free frames pool
                free_frames.push_back(free_frame);
            }
            //reset frame
            for(int i=0;i<Procs[current_process_id]->MAX_VPAGES;i++){
                PTE* pte=&Procs[current_process_id]->page_table[i];
                pte->frame_num=0;
                pte->Valid=0;
                pte->REFERENCED=0;
                pte->MODIFIED=0;
            }



            process_exits++;
            cost+=1250;
            instruction_i++;
            continue;
        }
        cost++;

        // now the real instructions for read and write
        PTE *pte = &current_process->page_table[vpage];
        if ( ! pte->Valid) {
            // this in reality generates the page fault exception and now you execute
            if(!pte->Accessable){
                //            SEGV output line
                cout<<" SEGV"<<endl;
                Pstats[current_process_id].segv++;
                cost+=340;
                instruction_i++;
                continue;
            }

            // verify this is actually a valid page in a vma if not raise error and next inst
            FRAME *newframe = get_frame();
            if(newframe!=nullptr){

                PTE *oldPTE = &Procs[newframe->proc_num]->page_table[newframe->pte_num];

                OhNoOutput(newframe, oldPTE, pte);
                if (newframe->notFree) {
                    //            PTE must be reset
                    ResetPTE(oldPTE);
                }


//            if()


                // see general outline in MM-slides under Lab3 header and writeup below
                // see whether and how to bring in the content of the access page.
                newframe->proc_num = current_process_id;
                newframe->pte_num = vpage;
                newframe->notFree = 1;
                pte->frame_num=newframe->frame_id;
                pte->Valid = 1;
            }
        }
        // check write protection
        if(pte->WRITE_PROTECT==1){
            if(operation=='w'){
                //SEGPROT
                cout<<" SEGPROT"<<endl;
                Pstats[current_process_id].segprot++;
                cost+=420;
                pte->MODIFIED=0;

            }
        }else{
            // simulate instruction execution by hardware by updating the R/M PTE bits
            // update_pte(read/modify) bits based on operations.

            if(operation=='w'){
                pte->MODIFIED=1;
            }
        }
        pte->REFERENCED=1;



        if (optionSet.count('y'))PrintAllPT();
        if (optionSet.count('f'))PrintFrame();

        instruction_i++;
    }

}




char* Simulator::readNewLine(char* newline){

    const char *delimiter = " \n\t";
    char *ptr = strtok(newline, delimiter);
//    delete[] newline;
    return ptr;
}
void Simulator::Read_Input(string input_name) {
//    for each input line (process spec)

    string line;
    ifstream readfile(input_name);
//    cout<< "input_name: " << input_name <<endl;
    bool read_process=true,read_proc_num=false;
    const char *delimiter = " \n\t";
    if (readfile.is_open())
    {
        int i=0;
        while ( getline (readfile, line) )
        {
            char * newline = new char [line.length()+1];
            strcpy (newline, line.c_str());

            char *ptr = readNewLine(newline);
            if(line[0]=='#'){
                continue;//#’ must be ignored
            }
            if(!read_proc_num){//First line not starting with a ‘#’ is the number of processes.
                proc_num = atoi(ptr);
                read_proc_num=true;
                read_process=true;
                continue;
            }
            if(read_process){
                //
                int vma_num = atoi(ptr);
                Pstat pstat;
                Pstats.push_back(pstat);

                Process* proc_ptr = new Process(vma_num);
                proc_ptr->pid=i;
                i++;
                Procs.push_back(proc_ptr);

                for(int i=0; i<vma_num; i++){
                    getline (readfile, line);
                    newline = new char [line.length()+1];
                    strcpy (newline, line.c_str());
                    ptr = readNewLine(newline);

                    int start_vpage = atoi(ptr);
                    ptr = strtok (NULL, delimiter);
                    int end_vpage = atoi(ptr);
                    ptr = strtok (NULL, delimiter);
                    bool write_protected = ptr[0]=='1'?true:false;
                    ptr = strtok (NULL, delimiter);
                    bool file_mapped = ptr[0]=='1'?true:false;
                    proc_ptr->vmas[i].start_vpage=start_vpage;
                    proc_ptr->vmas[i].end_vpage=end_vpage;
                    proc_ptr->vmas[i].write_protected=write_protected;
                    proc_ptr->vmas[i].file_mapped=file_mapped;
                    for(int j=start_vpage;j<=end_vpage;j++){

                        proc_ptr->page_table[j].Accessable=1;
                        proc_ptr->page_table[j].WRITE_PROTECT=write_protected;
                        proc_ptr->page_table[j].isFileMapped=file_mapped;
                        if(file_mapped){
                            PTE pte;
                            pte.Accessable=1;
                            pte.WRITE_PROTECT=write_protected;
                            pte.isFileMapped=1;
                            int rtag=j;
                            int ltag=proc_ptr->pid<<16;
                            int tag =ltag+rtag;
                            files[tag]=pte;
                        }
                    }
//                    delete[] newline;
                }



                if(Procs.size()==proc_num)read_process= false;
            }else{
                char operation = ptr[0];
                ptr = strtok (NULL, delimiter);
                int vpage = atoi(ptr);
                pair<char, int> instruction(operation, vpage);
                instructions.push_back(instruction);
            }

//            delete[] newline;
        }

        readfile.close();
    }
    else cerr << "Unable to open input file: "<<endl<<input_name <<endl;

//    cout<< "finish reading" <<endl;
}

FRAME *Simulator::get_frame() {


    for(int i=0; i<MaxFrames;i++){
        if(frame_table[i].notFree&&frame_table[i].proc_num==current_process_id&&frame_table[i].pte_num==vpage){
            return nullptr;
        }
    }
    FRAME *frame = allocate_frame_from_free_list();
    if (frame == nullptr) {
        int rand=myrandom(MaxFrames);

        frame = THE_PAGER->select_victim_frame(frame_table, MaxFrames,Procs,rand,optionSet.count('a'),instruction_i);

    }
    frame->time_last_used=instruction_i;
    return frame;

}

bool Simulator::get_next_instruction(char &operation, int &vpage) {
    if(instruction_i>=instructions.size())
        return false;
    operation = instructions[instruction_i].first;
    vpage = instructions[instruction_i].second;

    return true;
}

FRAME *Simulator::allocate_frame_from_free_list() {
    if(!free_frames.empty()){
        FRAME* frame = free_frames.front();
        free_frames.pop_front();
        return frame;
    }
    else return nullptr;
}

int Simulator::myrandom(int max_num) {
    int res = randvals[ofs] % max_num;
    ofs=(ofs+1)%rand_num;
    return res;//ofs++ after return
}
void Simulator::read_randvals(string rfile_name) {

    string line;
    ifstream readfile(rfile_name);
//    cout<< "rfile_name: " << rfile_name <<endl;
    if (readfile.is_open())
    {
        getline (readfile, line);
        rand_num =stoi(line);
        randvals = new int[rand_num];
        int i=0;
        while ( getline (readfile, line) )
        {
            randvals[i] = stoi(line);
            i++;
        }
        readfile.close();
    }
    else cerr << "Unable to open randvals" <<endl;
//    cout<< "finish reading" <<endl;
}

void Simulator::Print_result() {
    if (optionSet.count('P'))PrintAllPT();
    if (optionSet.count('F'))PrintFrame();
    if (optionSet.count('S'))ProcStatisticOutput();

//    for(Process *p:Procs){
//        delete[] p->vmas;
////        delete[] p->page_table;
//        delete p;
//    }
//    delete[] THE_PAGER->Ages;
//    delete[] frame_table;
//    delete[] randvals;
}

void Simulator::PrintAllPT() {
    for (int i=0;i<(int)Procs.size();i++){
        cout<<"PT["<<i<<"]:";
        PTE* pte = Procs[i]->page_table;
        for(int j=0;j<Procs[i]->MAX_VPAGES;j++){
            if(pte[j].PAGEDOUT==1&&pte[j].MODIFIED==1&&pte[j].Valid==0){
                cout<<" #";
                continue;
            }
            if(pte[j].Valid==0) {
                cout << " *";
                continue;
            }
            else{
                cout<<" "<<j<<":";
                if(pte[j].REFERENCED==1){
                    cout<<"R";
                }else{
                        cout << "-";
                    }
            }

            if(pte[j].MODIFIED){
                cout<<"M";
            }else{
                cout<<"-";
            }
            pte[j].PAGEDOUT? cout<<"S": cout<<"-";



        }
        cout<<endl;
    }
}

void Simulator::PrintCurrPT() {
    if (!optionSet.count('x'))return;
}

void Simulator::PrintFrame() {

    cout<<"FT:";
    for(int i=0;i<MaxFrames;i++){
        if(frame_table[i].notFree){
            cout<<" "<<frame_table[i].proc_num<<":"<<frame_table[i].pte_num;
        }else{
            cout<<" *";
        }



    }
    cout<<endl;
}

void Simulator::PrintAging() {

}

void Simulator::ResetPTE(PTE *pte) {

    pte->frame_num=0;
    pte->Valid=0;
    pte->REFERENCED=0;
//    pte->MODIFIED=0;
//    pte->WRITE_PROTECT=0;//vma defined
//    pte->isFileMapped=0;//vma difined
//    pte->Accessable=0;
//    PAGEDOUT flag is set it will never be reset as it indicates there is content on the swap device
}



void Simulator::ProcStatisticOutput() {
    //Per process output:
    for(int i=0; i<(int)Procs.size(); i++) {
        Pstat pstat= Pstats[i];
        printf("PROC[%d]: U=%lu M=%lu I=%lu O=%lu FI=%lu FO=%lu Z=%lu SV=%lu SP=%lu\n",
               i,
               pstat.unmaps, pstat.maps, pstat.ins, pstat.outs,
               pstat.fins, pstat.fouts, pstat.zeros,
               pstat.segv, pstat.segprot);
    }

    ////Summary output:
    printf("TOTALCOST %lu %lu %lu %llu %lu\n",
    inst_count, ctx_switches, process_exits, cost, sizeof(PTE));
}

