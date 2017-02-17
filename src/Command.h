#ifndef COMMAND_H
#define COMMAND_H

#include "BaseAction.h"
#include <string.h>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class Command : public BaseAction
{
    private:
	char** args; //args[0] is the command
	unsigned length;
    public:
	Command(const vector<string> &);
	bool execute();
};

#endif
