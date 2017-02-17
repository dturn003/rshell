#include "Command.h"

Command::Command(const vector<string> &v)
{
    args = new char*[v.size() + 1];
    for(unsigned i = 0; i < v.size(); i++) {
        args[i] = new char[v[i].size() + 1];
        strcpy(args[i], v[i].c_str());
    }
    args[v.size()] = NULL;
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
