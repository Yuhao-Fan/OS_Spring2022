#include <iostream>
#include "Linker.h"
using namespace std;

int main(int argc, char **argv) {

    auto linker = new Linker();
    string filename=argv[argc-1];
    linker->tokenizer(filename);
    cout<<endl;

    return 0;
}
