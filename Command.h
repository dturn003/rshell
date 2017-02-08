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
		
    public:
		Command(string cmd_tmp, vector<BaseAction*> args_temp);
		bool execute();
};

#endif