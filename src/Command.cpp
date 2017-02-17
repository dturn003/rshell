#include "Command.h"

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
        delete [] arr[i];
    }
    delete [] arr;
}

bool Command::execute()
{
    pid_t pid = fork();
    
    if (pid < 0) //failed
    {
        perror("Fork failed");
        return false;
    }
    else if (pid == 0) //child process
    {
        execvp(args[0], args);
    }
    else //parent
    {
        int status;
        wait(&status);
        return WIFEXITED(status)
    }
}
