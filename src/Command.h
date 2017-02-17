#ifndef COMMAND_H
#define COMMAND_H

#include "BaseAction.h"
#include <string>
#include <vector>
#include <cstring>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Command : public BaseAction
{
    private:
	unsigned length;
	char** args; //args[0] is the command
		
    public:
	Command(const vector<string> &);
	~Command();
	
	int execute();
};

#endif
