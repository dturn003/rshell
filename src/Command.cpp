#include "Command.h"
#include <unistd.h>

Command::Command(string cmd, vector<string> args) {
    this->cmd = cmd;
    this->args = args;
}

bool Command::execute()
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork failed.");
		exit(1);
	}
	else if (pid == 0)
	{
		char* args[] = {"./dfdfdf"}
		execv()
	}
		
	return false;
}
