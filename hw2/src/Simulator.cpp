//
// Created by Yuhao Fan on 3/6/22.
//

#include "Simulator.h"

void Simulator::Simulation(bool verbose, bool trace, bool eventQ, bool preempt) {

    show_eventQ = eventQ;
    show_event_execution=trace;
    show_verbose=verbose;
    show_preempt = preempt;

    showEventQ();
    while (!des_ptr->evt_SET.empty()) {
        multiset<Event>::iterator evt;
        evt = des_ptr->get_event();

        Process *proc = evt->evtProcess;
        int CURRENT_TIME = evt->Timestamp;
        event_trans_type transition = evt->transition;
        int timeInPrevState = CURRENT_TIME - proc->state_ts;
        event_state_type oldstate = evt->oldstate;


        des_ptr->rm_event(evt);


        switch (transition) {  // which state to transition to?

            case TRANS_TO_BLOCK: {
                showVerbose(oldstate,BLOCK,CURRENT_TIME,proc,timeInPrevState);
                if(proc->remaining_cpu_time!=0){


                    //create an event for when process becomes READY again

                    int io_burst_time = myrandom(proc->io_burst);
//                    time_iobusy += io_burst_time;
                    proc->IO_time += io_burst_time;
                    proc->ib=io_burst_time;
                    showVerboseRight(BLOCK,io_burst_time,proc);


                    int io_end_time = CURRENT_TIME + io_burst_time;
                    io_intervals.push_back({CURRENT_TIME,io_end_time});//parallel
                    proc->state_ts = CURRENT_TIME;
//                    THE_SCHEDULER->add_process(proc);
                    Event io_event(io_end_time, proc, BLOCK, READY, TRANS_TO_READY);
//                    traceEventExecution(&io_event, TRANS_TO_READY);
                    showEventQ_before(&io_event);
                    des_ptr->put_event(io_event);
                    showEventQ_after();
                }
                try {
                    THE_SCHEDULER->deactivate_process(proc);//deactivate specific process, not the last one

                }
                catch (const std::exception& e) {
                    cout<<"e.what()"<<e.what();
                }



                CURRENT_RUNNING_PROCESS=nullptr;

                CALL_SCHEDULER = true;
                break;
            }
            case TRANS_TO_READY: {
                // must come from BLOCKED or from PREEMPTION
                // must add to run queue
                showVerbose(oldstate,READY,CURRENT_TIME,proc,timeInPrevState);


                if(proc->cb>0){
                    if(show_verbose)
                        cout<<" ";
                    showVerboseRight(RUNNG,proc->cb,proc);
//                    CURRENT_RUNNING_PROCESS=nullptr;
                }
//                if(oldstate==RUNNG){
//                    proc->dynamic_priority--;
//                    if(proc->dynamic_priority == -1)
//                        proc->dynamic_priority=proc->static_priority-1;
//                }

                if(oldstate==BLOCK){
                    proc->dynamic_priority=proc->static_priority-1;
//                    if(proc->dynamic_priority == -1)
//                        proc->dynamic_priority=proc->static_priority-1;
                }else if(oldstate==RUNNG){//from PREEMPTION
                    proc->dynamic_priority--;
//                    if(proc->dynamic_priority == -1)
//                        proc->dynamic_priority=proc->static_priority-1;
                }
                proc->state_ts = CURRENT_TIME;
//                cout<<"add_process: "<<proc->index;//for test
                THE_SCHEDULER->add_process(proc);
//                try {
//                    THE_SCHEDULER->add_process(proc);
//                }
//                catch (const std::exception& e) {
//                    cout<<"e.what()"<<e.what();
//                }
                CURRENT_RUNNING_PROCESS=nullptr;//make sure preempt -> ready process not running


//                if(!insert_success){//if remaining_cpu_time ==0 means this proc is done already
//                    cout<<"insert_failed";//test
//                }

                multiset<Event>::iterator preemptor_evt=des_ptr->have_preemptor();

                if(sched_sname!="PREPRIO"){
                    if(!des_ptr->have_block()){
                        CALL_SCHEDULER = true; // conditional on whether something is run
                    }


                }else if(preemptor_evt==des_ptr->evt_SET.end()){
                    CALL_SCHEDULER = true; // conditional on whether something is run
                }
                else {
                    bool test_preempt=false;
                    Process* preemptor =preemptor_evt->evtProcess;
//                    if(CURRENT_RUNNING_PROCESS==nullptr){
//                        if(preemptor_evt->newstate==PREEMPT)
//                            test_preempt=true;
//                        else{
//                            test_preempt=THE_SCHEDULER->test_preempt(preemptor_evt->evtProcess,CURRENT_TIME);
//                        }
//                    }
////                    else if(CURRENT_RUNNING_PROCESS->index==preemptor->index){
////                        test_preempt=true;
////                    }
//                    else{
//                        test_preempt=THE_SCHEDULER->test_preempt(preemptor_evt->evtProcess,CURRENT_TIME);
//
//                    }
                    if(preemptor->dynamic_priority<proc->dynamic_priority){
                        test_preempt=true;
                    }

                    if(preemptor_evt->Timestamp==CURRENT_TIME){
                        test_preempt=false;
                    }
//                    Process* preempted = THE_SCHEDULER->get_next_process();
                    Process* preempted=proc;
//                    multiset<Event>::iterator preempted_evt=des_ptr->();

                    if(show_preempt){
                        //---> PRIO preemption 1 by 2 ? 1 TS=32 now=32) --> NO

                        cout<<"---> PRIO preemption "<<preemptor->index<<" by "<<preempted->index<<" ? ";
                        cout<<preempted->dynamic_priority<<" TS="<<preemptor_evt->Timestamp<<" now="<<CURRENT_TIME<<") --> ";
                        if(test_preempt){
                            cout<<"YES"<<endl;
                        }else{
                            cout<<"NO"<<endl;
                        }
                    }
                    if(test_preempt){
                        int add_time = preemptor_evt->Timestamp-CURRENT_TIME;
                        preemptor->cb+=add_time;
                        preemptor->remaining_cpu_time+=add_time;
//                        if(preemptor_evt->oldstate==BLOCK)
//                            time_cpubusy-=add_time;
                        Event preempt_evt(CURRENT_TIME, preemptor, RUNNG, PREEMPT, TRANS_TO_PREEMPT);
                        THE_SCHEDULER->deactivate_process(preemptor);

                        des_ptr->rm_event(preemptor_evt);
                        showEventQ_before(&preempt_evt);
                        des_ptr->put_event(preempt_evt);
                        showEventQ_after();

//                        preemptor_evt->Timestamp=CURRENT_TIME;
                    }
                }




                break;
            }


            case TRANS_TO_RUNNG:{
                // create event for either preemption or blocking
                showVerbose(oldstate,RUNNG,CURRENT_TIME,proc,timeInPrevState);
                int cpu_burst_time;
                if(proc->cb>0){
                    cpu_burst_time=proc->cb;
                }else{
                    cpu_burst_time = myrandom(proc->cpu_burst);

                }
                cpu_burst_time=min(cpu_burst_time,proc->remaining_cpu_time);
                bool preemption = false;
                showVerboseRight(RUNNG,cpu_burst_time,proc);//show before changes
                proc->cb=cpu_burst_time;
                int duration = cpu_burst_time;
                if(quantum>0){


                    if(quantum<duration){
                        duration=quantum;
                        preemption=true;
                    }
                }


                if(proc->remaining_cpu_time>duration){
                    int cpu_end_time = CURRENT_TIME + duration;
                    proc->state_ts = CURRENT_TIME;
                    proc->cb=proc->cb-duration;//
                    proc->CPU_wait_time+=timeInPrevState;
                    proc->remaining_cpu_time-=duration;
//                    time_cpubusy+=duration;
                    Event cpu_event;
                    if(preemption){
                        //proc->cb=cpu_burst_time;

                        THE_SCHEDULER->deactivate_process(proc);

                        CURRENT_RUNNING_PROCESS=NULL;
                        cpu_event = Event(cpu_end_time, proc, RUNNG, PREEMPT, TRANS_TO_PREEMPT);

                    }
                    else {
                        proc->cb=0;
                        cpu_event = Event(cpu_end_time, proc, RUNNG, BLOCK, TRANS_TO_BLOCK);
                    }
                    showEventQ_before(&cpu_event);
                    des_ptr->put_event(cpu_event);
                    showEventQ_after();

                }else{
                    //finished
                    duration = proc->remaining_cpu_time;
                    int cpu_end_time = CURRENT_TIME + duration;
                    proc->state_ts = CURRENT_TIME;
                    proc->CPU_wait_time+=timeInPrevState;
                    proc->cb=0;


                    proc->remaining_cpu_time=0;

//                    time_cpubusy+=duration;
                    Event end_event(cpu_end_time, proc, RUNNG, BLOCK, TRANS_TO_BLOCK);

//                    traceEventExecution(&end_event,TRANS_TO_BLOCK);

                    showEventQ_before(&end_event);

                    des_ptr->put_event(end_event);
                    showEventQ_after();
                    CURRENT_RUNNING_PROCESS=nullptr;
//                    CALL_SCHEDULER = true;



                    proc->Finishing_time = cpu_end_time;
                    proc->Turnaround_time = proc->Finishing_time - proc->start_time;
                    finishtime = proc->Finishing_time;
//                    sum_turnaround+=proc->Turnaround_time;
//                    sum_cpu_wait+=proc->CPU_wait_time;


                }


                break;
            }


            case TRANS_TO_PREEMPT:{
//                showVerbose(oldstate,READY,CURRENT_TIME,proc,timeInPrevState);


                Event ready_preempt(CURRENT_TIME, proc, RUNNG, READY, TRANS_TO_READY);
                des_ptr->put_event(ready_preempt);
                CALL_SCHEDULER = true;
                break;
            }

        }
        if (CALL_SCHEDULER) {

            if (des_ptr->get_next_event_time() == CURRENT_TIME){

//                showVerboseRight(READY,proc);
                continue; //process next event from Event queue
            }
            if(des_ptr->evt_SET.size() != 0&&des_ptr->get_event()->evtProcess->remaining_cpu_time==0){
                continue;
            }

            CALL_SCHEDULER = false; // reset global flag

            if (CURRENT_RUNNING_PROCESS == nullptr) {
                CURRENT_RUNNING_PROCESS = THE_SCHEDULER->get_next_process();
                traceEventExecution();

                if (CURRENT_RUNNING_PROCESS == nullptr)
                    continue;
                if(CURRENT_RUNNING_PROCESS->remaining_cpu_time==0){
                    Event done_event(CURRENT_TIME, CURRENT_RUNNING_PROCESS, BLOCK, READY, TRANS_TO_READY);
                    //do not need to show done event
                    des_ptr->put_event(done_event);

                }else{
                    // create event to make this process runnable for same time.
                    Event run_event(CURRENT_TIME, CURRENT_RUNNING_PROCESS, READY, RUNNG, TRANS_TO_RUNNG);

                    showEventQ_before(&run_event);
                    des_ptr->put_event(run_event);

                    showEventQ_after();
                }



//                Event sched_event(CURRENT_TIME, CURRENT_RUNNING_PROCESS, READY, RUNNG, TRANS_TO_RUNNG);
//                des_ptr->put_event(sched_event);
            }
        }
    }


}

void Simulator::Read_Processes(string input_name) {
//    for each input line (process spec)

    string line;
    ifstream readfile(input_name);
//    cout<< "input_name: " << input_name <<endl;
    if (readfile.is_open())
    {
        int i=0;
        while ( getline (readfile, line) )
        {
            char * newline = new char [line.length()+1];
            strcpy (newline, line.c_str());

            const char *delimiter = " \n\t";
            char *ptr = strtok(newline, delimiter);

            int AT = atoi(ptr);
            ptr = strtok (NULL, delimiter);
            int TC = stoi(ptr);
            ptr = strtok (NULL, delimiter);
            int CB = stoi(ptr);
            ptr = strtok (NULL, delimiter);
            int IO = stoi(ptr);
            int SP = myrandom(max_static_priority);//used first few random numbers in rfile,0-max_static_priority
//            cout<<AT<<endl;
//            cout<<TC<<endl;
//            cout<<CB<<endl;
//            cout<<IO<<endl;
//            cout<<SP<<endl;
            // 1. create a process object
            Process* proc_ptr =  new Process(i,AT,TC,CB,IO,SP,AT);

            proc_list.push_back(proc_ptr);

            // 2. create a process-create event
            Event input_evt(AT,proc_ptr,CREATED,READY,TRANS_TO_READY);
//            Event input_evt(AT,proc_ptr,CREATED,READY,TRANS_TO_READY);

            // 3. enter this event into the event queue.
            des_ptr->put_event(input_evt);
//            delete proc_ptr;
            i++;

            delete[] newline;
        }



        num_processes = i;
        readfile.close();
    }
    else cerr << "Unable to open input file: "<<endl<<input_name <<endl;

//    cout<< "finish reading" <<endl;
}

void Simulator::decode_event(Event *evt) {

}

void Simulator::action() {

}

void Simulator::Print_result() {


    time_iobusy=get_sum_io_busytime();
    double io_util = 100.0 * (time_iobusy / (double) finishtime);
    double throughput = 100.0 * (num_processes / (double) finishtime);



    cout<<sched_sname;
    if(quantum>0){
        cout<<" "<<quantum;
    }
    cout<<endl;
    int i = 0;
    time_cpubusy=0;
    for(Process *proc:proc_list){
        cout <<setw(4)<<setfill('0') <<i << ": " ;
        cout <<setw(4) <<setfill(' ') <<proc->start_time << " " ;
        cout <<setw(4) <<proc->cpu_time << " " ;
        cout <<setw(4) <<proc->cpu_burst << " ";
        cout <<setw(4) <<proc->io_burst << " "<<proc->static_priority<<" |  ";
        cout <<setw(4)<<proc->Finishing_time << " " ;
        cout <<setw(5)<<proc->Turnaround_time << " " ;

        sum_turnaround+=proc->Turnaround_time;
        cout <<setw(5)<<proc->IO_time << " " ;
        cout <<setw(5)<<proc->CPU_wait_time<<endl;
        sum_cpu_wait+=proc->CPU_wait_time;
        time_cpubusy+=proc->Turnaround_time-proc->IO_time-proc->CPU_wait_time;
        i++;

    }
    double cpu_util = 100.0 * (time_cpubusy / (double) finishtime);
    double avg_turnaround = sum_turnaround/(double)num_processes;
    double avg_cpu_wait = sum_cpu_wait/(double)num_processes;
    cout<<"SUM: "<<finishtime<<" ";
    printf("%.2lf %.2lf %.2lf %.2lf %.3lf\n", cpu_util, io_util, avg_turnaround,avg_cpu_wait, throughput);

    for(Process *p:proc_list){
       delete p;
    }
    delete[] randvals;
}
int Simulator::myrandom(int burst) {
    int res = 1 + (randvals[ofs] % burst);
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

void Simulator::showEventQ() {
    if(show_verbose && show_eventQ){
        cout<<"ShowEventQ:";

        for (auto const &each_evt : des_ptr->evt_SET){
            cout<<"  " << each_evt.Timestamp<<":"<<each_evt.evtProcess->index;

        }
        cout<<endl;

    }

}

void Simulator::traceEventExecution() {

    if(show_verbose && show_event_execution){
        THE_SCHEDULER->showQ();
    }
}

void Simulator::showEventQ_before(Event *evt) {
    if(show_verbose && show_eventQ){
        cout<<"  AddEvent("<<evt->Timestamp<<":"<<evt->evtProcess->index<<":"<<event_states[evt->newstate]<<"):";
        for (auto const &each_evt : des_ptr->evt_SET){
            cout<<"  " << each_evt.Timestamp<<":"<<each_evt.evtProcess->index<<":"<<event_states[each_evt.newstate];

        }
        cout<<" ==> ";
    }


}

void Simulator::showEventQ_after() {
    if(show_verbose && show_eventQ){
        for (auto const &each_evt : des_ptr->evt_SET){
            cout<<"  " << each_evt.Timestamp<<":"<<each_evt.evtProcess->index<<":"<<event_states[each_evt.newstate];

        }
        cout<<endl;
    }
}

void Simulator::showVerbose(event_state_type oldstate,event_state_type newstate, int CURRENT_TIME, Process *proc, int timeInPrevState) {
    if(show_verbose){

        cout<<CURRENT_TIME<<" "<<proc->index<<" "<<timeInPrevState<<": ";
        if(proc->remaining_cpu_time==0){
            cout<<"Done"<<endl;
        }else{
            cout<<event_states[oldstate]<< " -> "<<event_states[newstate];
        }


    }
}

void Simulator::showVerboseRight(event_state_type newstate,int burst_time, Process *proc) {
    if(show_verbose) {
        if (newstate == RUNNG) {
            cout << " cb=" << burst_time << " rem=" << proc->remaining_cpu_time << " prio=" ;
            if(sched_sname!="PREPRIO"&&sched_sname!="PRIO"){
                cout<< proc->static_priority-1;
            }else{
                cout<< proc->dynamic_priority;
            }
        }
        if (newstate == BLOCK) {
            cout << "  ib=" << burst_time << " rem=" << proc->remaining_cpu_time;
        }
        cout <<endl;
    }

}
int Simulator::get_sum_io_busytime() {
    if (io_intervals.size() == 0) {
        return 0;
    }
    sort(io_intervals.begin(), io_intervals.end());
//    for(auto x:io_intervals) {
//        for(auto y:x){
//            cout<<y<<" ";
//        }
//        cout<<endl;
//
//    }
    vector<vector<int>> merged_io_intervals;
    for (int i = 0; i < (int)io_intervals.size(); i++) {
        int left = io_intervals[i][0];
        int right = io_intervals[i][1];
        if (merged_io_intervals.size()==0 || left>merged_io_intervals.back()[1]) {
            merged_io_intervals.push_back({left, right});
        }
        else {
            merged_io_intervals.back()[1] = max(right,merged_io_intervals.back()[1]);
        }
    }
    int sum=0;
    for (int i = 0; i < (int)merged_io_intervals.size(); i++){
        sum+=merged_io_intervals[i][1]-merged_io_intervals[i][0];
    }
    return sum;
}



