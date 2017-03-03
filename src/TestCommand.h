#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "BaseAction.h"

#include <vector>
#include <string>

using namespace std;

class TestCommand : public BaseAction {
    protected:
        string flag;
        string path;
        bool validArgs;
        
    public:
        int execute();
        
        /*
        args.size() == 3 -> "test" flag path
        args.size() == 2 -> flag path
        args.size() == 1 -> path
        */
        TestCommand() { };
};

#endif