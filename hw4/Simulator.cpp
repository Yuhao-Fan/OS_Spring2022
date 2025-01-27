//
// Created by Yuhao Fan on 4/24/22.
//

#include "Simulator.h"
void Simulator::Simulation() {
    int time=1;
    int req_i=0;
    int finish_num=0;
    if (trace) {cout<<"TRACE"<<endl;}
    while (true) {
        //if a new I/O arrived to the system at this current time
        if (req_i<(int)ops.size()&&ops[req_i]->time_step == time) {
            // → add request to IO-queue
            THE_SCHED->IO_queue.push_back(ops[req_i]);
            if (trace) {
                cout << time << ": "<<setw( 5 ) << req_i << " add " << ops[req_i]->target << endl;
            }
            req_i++;
        }
        // if an IO is active and completed at this time
        if (!THE_SCHED->actives.empty()&&THE_SCHED->actives.front()->complete_time <= time) {
            Request *req = THE_SCHED->actives.front();
            req->end_time = time;
            if (trace) {
                cout << time << ": "<<setw( 5 ) << req->index << " finish " << req->end_time - req->time_step << endl;
            }
            finish_num++;
//            → Compute relevant info and store in IO request for final summary


            avg_turnaround += req->end_time - req->time_step;
            THE_SCHED->actives.pop_front();
        }

//        if no IO request active now
        if(THE_SCHED->actives.empty()){
            // if requests are pending
            int issue_i = THE_SCHED->issue();
            if (issue_i>=0) {
                //→ Fetch the next request from IO-queue and start the new IO.

                int waittime=time-ops[issue_i]->time_step;

                avg_waittime+=waittime;
                max_waittime=max(waittime,max_waittime);
                int move=abs(ops[issue_i]->target-THE_SCHED->current_track);

                tot_movement+=move;
                ops[issue_i]->complete_time=time+move;
                ops[issue_i]->start_time=time;
                if (trace) {
                    cout << time << ": " <<setw( 5 )<< issue_i << " issue " << ops[issue_i]->target << " "
                         << THE_SCHED->current_track << endl;

                }
                THE_SCHED->current_track = ops[issue_i]->target;
                if(move==0)continue;
            }
    //            else if all IO from input file processed → exit simulation
            else if (finish_num==(int)ops.size()) {
                total_time = time;
                return;
            }
        }

//        if an IO is active
//        → Move the head by one unit in the direction its going (to simulate seek)

// Increment time by 1
        time+=1;
    }

}
char* Simulator::readNewLine(char* newline){

    const char *delimiter = " \n\t";
    char *ptr = strtok(newline, delimiter);
//    delete[] newline;
    return ptr;
}
void Simulator::Read_Input(string input_name) {


    string line;
    ifstream readfile(input_name);
//    cout<< "input_name: " << input_name <<endl;
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
            newline = new char [line.length()+1];
            strcpy (newline, line.c_str());
            ptr = readNewLine(newline);

            int time_step = atoi(ptr);
            ptr = strtok (NULL, delimiter);
            int access = atoi(ptr);
            Request* req=new Request(time_step,access,i);
            ops.push_back(req);
            i++;
//            delete[] newline;
        }

        readfile.close();
    }
    else cerr << "Unable to open input file: "<<endl<<input_name <<endl;

//    cout<< "finish reading" <<endl;
}

void Simulator::Print_result() {

    for (int i = 0; i < (int)ops.size(); i++) {
        Request* req=ops[i];
        printf("%5d: %5d %5d %5d\n", i, req->time_step, req->start_time, req->end_time);
        //time_step is arrival_time

    }
    avg_turnaround/=ops.size();
    avg_waittime/=ops.size();
    printf("SUM: %d %d %.2lf %.2lf %d\n",
           total_time, tot_movement, avg_turnaround, avg_waittime, max_waittime);

}


