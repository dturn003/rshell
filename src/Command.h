#ifndef COMMAND_H
#define COMMAND_H

#include "BaseAction.h"
#include <string>
#include <vector>
using namespace std;

class Command : public BaseAction
{
    private:
        string cmd;
        vector<string> args;
	
    public:
        Command(string cmd_tmp, vector<string> args_temp);
        bool execute();
};

#endif
