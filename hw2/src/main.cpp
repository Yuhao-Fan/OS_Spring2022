//#include <iostream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include "Simulator.h"


using namespace std;

int main (int argc, char **argv)
{
    bool verbose = false;
    bool trace = false;
    bool eventQ = false;
    bool preempt = false;

    char *scheduler = nullptr;
//    int index;
    int c;

    int quantum=-1;
    int maxprio = 4;
    opterr = 0;
    bool read_quantum = false;
    while ((c = getopt (argc, argv, "vteps:")) != -1)
        switch (c)
        {
            case 'v':
                verbose = true;
                break;
            case 't':
                trace = true;
                break;
            case 'e':
                eventQ = true;
                break;
            case 'p':
                preempt = true;
                break;
            case 's':
                scheduler = optarg;

                if(sscanf(scheduler, "E%d:%d",&quantum,&maxprio))read_quantum=true;
                if(sscanf(scheduler, "P%d:%d",&quantum,&maxprio))read_quantum=true;
                if(sscanf(scheduler, "R%d",&quantum))read_quantum=true;
                if(read_quantum){
                    assert(quantum>0);
                }
//                assert(quantum>0);
//                cout<<"scheduler: "<<scheduler<<endl;
                break;
            case '?':
                if (optopt == 's')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown option character `\\x%x'.\n",
                             optopt);
                return 1;
            default:
                abort ();
        }
//    cout<< quantum << endl;
//    cout<< maxprio << endl;
//    printf ("verbose = %d, trace = %d, eventQ = %d, preempt = %d scheduler = %s\n",
//            verbose, trace, eventQ, preempt,scheduler);

//    for (index = optind; index < argc; index++)
//        printf ("Non-option argument %s\n", argv[index]);

//    Unknown Scheduler spec: -v {FLSRPE}
    string input_name=argv[argc-2];
    string rfile_name=argv[argc-1];
    char sched_name = scheduler[0];



    
    Simulator s(input_name,rfile_name,sched_name,quantum,maxprio);

    s.Simulation(verbose, trace, eventQ, preempt);
    s.Print_result();
    return 0;
}

