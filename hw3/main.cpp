#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "Simulator.h"
//#include <cassert>
using namespace std;
int main(int argc, char **argv) {


    char *num_frames = nullptr;
    int MAX_FRAMES=0;
    char *algo = nullptr;
    char pager;
    char *options = nullptr;
    char ops[9];//"OPFSxyfa\0"
    opterr = 0;
//    ./mmu –f<num_frames> -a<algo> [-o<options>] inputfile randomfile
    int c;
    while ((c = getopt (argc, argv, "f:a:o:")) != -1)
        switch (c)
        {
            case 'f':
                num_frames = optarg;
                sscanf(num_frames, "%d",&MAX_FRAMES);
                break;
            case 'a':
                algo = optarg;
                sscanf(algo, "%c",&pager);
                break;
            case 'o':
                options=optarg;
                sscanf(options, "%s",ops);
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

    string input_name=argv[argc-2];
    string rfile_name=argv[argc-1];

    Simulator s(input_name,rfile_name,MAX_FRAMES,pager,ops);

    s.Simulation();
    s.Print_result();

    return 0;
//    exit();
}
