#include "Command.h"
#include <unistd.h>

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