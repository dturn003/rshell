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

int Command::execute() //returns 0 if command failed, 1 if command succeeded, and -1 if exit command
{
    if (args[0] == "exit")
    {
        return -1; //exit
    }
        
    pid_t pid = fork();
    
    if (pid < 0) //failed
    {
        perror("Fork failed");
        return 0; //false
    }
    else if (pid == 0) //child process
    {
        if (length == 1) //empty list of arguments and commands
        {
            perror("Missing Command");
            return 0; //false
        }
        else
        {
            execvp(args[0], args); //run program in bin
        }
    }
    else //parent
    {
        int status; //status of child process
        wait(&status); //waits for child process to finish
        
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 0) //program succeeded
            {
                return 1; //true
            }
            else //program failed but exited normally
            {
                perror("Command failed");
                return 0; //false
            }
        }
        else //program exited abnormally
        {
            perror("Exited abnormally");
            return 0; //false
        }
    }
    
    return 0; //default, should never reach here
}
