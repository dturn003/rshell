#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "Command.h"
using namespace std;

class TestCommand : public Command {
    private:
        char flag;
    public:
        int execute();
        
        /*
        args[0] = test
        args[1] = flag (-e, -f, -d)
        args[>2] = directory/file to check
        */
        TestCommand(const vector<string> &);
};

#endif