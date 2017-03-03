#include "WordTestCommand.h"

WordTestCommand::WordTestCommand(const vector<string> &v) {
    if(v.size() == 3) { //input like regular command: test flag path
        flag = v.at(1);
        path = v.at(2);
        validArgs = true;
    }
    else if (v.size() == 2) {
        flag = "-e";
        path = v.at(1);
        validArgs = true;
    }
    else { //any other amount of input is wrong
        validArgs = false;
    }
}