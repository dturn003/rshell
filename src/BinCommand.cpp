#include "BinCommand.h"

//Linux Libraries
#include <string.h> //strcpy
#include <stdio.h> //perror
#include <sys/types.h>
#include <sys/wait.h> //wait system call
#include <unistd.h> //fork system call

BinCommand::BinCommand(const std::vector<std::string> &v) {
    length = v.size() + 1;
    args = new char*[length];
    for(unsigned i = 0; i < length-1; i++) {
        args[i] = new char[v[i].size() + 1];
        strcpy(args[i], v[i].c_str());
    }
    args[length-1] = NULL;
}

BinCommand::~BinCommand() {
    for(unsigned i = 0; i < length; i++) {
        delete [] args[i];
    }
    delete [] args;
}

int BinCommand::execute() { //returns 0 if command failed, 1 if command succeeded, and -1 if exit command
    pid_t pid = fork();
    
    if (pid < 0) { //fork failed, return ExitStatus::FAILURE
        perror("Call fork failed");
        return ExitStatus::FAILURE;
    }
    else if (pid == 0) { //child process
        execvp(args[0], args); //run program in bin
        perror("Command has failed");
        return ExitStatus::FAILURE;
    }
    else { //parent
        int status; //status of child process
        if (waitpid(pid, &status, 0) == -1) { //waits for child process to finish
            perror("Call waitpid has failed");
            return ExitStatus::FAILURE; 
        }
        else {
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 0) { //program succeeded
                    return ExitStatus::SUCCESS; //true
                }
                else { //program failed but exited normally
                    return ExitStatus::FAILURE; //false
                }
            }
            else { //program exited abnormally
                return ExitStatus::FAILURE; //false
            }
        }
    }
}
