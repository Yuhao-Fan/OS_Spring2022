//
// Created by Yuhao Fan on 2/4/22.
//


#include "Token.h"



void Token::parseError(int errorCode) const {

    static string errMessage[] = {
            "NUM_EXPECTED", // Number expect, anything >= 2^30 is not a number either
            "SYM_EXPECTED", // Symbol Expected
            "ADDR_EXPECTED", // Addressing Expected which is A/E/I/R
            "SYM_TOO_LONG", // Symbol Name is too long
            "TOO_MANY_DEF_IN_MODULE", // > 16
            "TOO_MANY_USE_IN_MODULE", // > 16
            "TOO_MANY_INSTR", // total num_instr exceeds memory size (512)

    };

    cerr << "Parse Error line " << lineNum << " offset " << lineOffset << ": " <<errMessage[errorCode]<<endl;
    exit(0);
}
