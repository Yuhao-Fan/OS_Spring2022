#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include "Simulator.h"
//#include <cassert>
using namespace std;
int main(int argc, char **argv) {


    bool trace = false;
    bool queue = false;
    bool flook = false;

    opterr = 0;
    char *schedalgo = nullptr;
    char algo;

//    ./iosched [ –s<schedalgo> | -v | -q | -f ] <inputfile>
    int c;
    while ((c = getopt (argc, argv, "s:vqf")) != -1)
        switch (c)
        {
            case 'v':
                trace=true;
                break;
            case 'q':
                queue=true;
                break;
            case 'f':
                flook=true;
                break;
            case 's':
                schedalgo=optarg;
                sscanf(schedalgo, "%c",&algo);
                break;
            case '?':
                if (optopt == 'f'||optopt == 'a'||optopt == 'o')
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

    string input_name=argv[argc-1];


    Simulator s(input_name,algo,trace,queue,flook);

    s.Simulation();
    s.Print_result();

    return 0;

}
