#include "Command.h"
#include <stdlib.h>

Command::Command(const vector<string> &v)
{
    length = v.size() + 1;
    args = new char*[length];
    for(unsigned i = 0; i < length-1; i++) {
        args[i] = new char[v[i].size() + 1];
        strcpy(args[i], v[i].c_str());
    }
    args[length-1] = NULL;
}

Command::~Command()
{
    for(unsigned i = 0; i < length; i++)
    {
        delete [] args[i];
    }
    delete [] args;
}

bool Command::execute()
{
    if (args[0] == "exit")
        exit(1);
    
    pid_t pid = fork();
    
    if (pid < 0) //failed
    {
        perror("Fork failed");
        return false;
    }
    else if (pid == 0) //child process
    {
        if (length == 1) {
            exit(-1);
        }
        execvp(args[0], args);
    }
    else //parent
    {
        int status;
        wait(&status);
        
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 0) //program succeeded
            {
                return true;
            }
            else //program failed but exited normally
            {
                perror("Command failed");
                return false;
            }
        }
        else //program exited abnormally
        {
            perror("Exited abnormally");
            return false;
        }
    }
    return false;
}
