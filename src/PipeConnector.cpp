#include "PipeConnector.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

PipeConnector::PipeConnector() : Connector() {}
PipeConnector::PipeConnector(BaseAction* left, BaseAction* right) : Connector(left, right) {}

int PipeConnector::execute() {
    int pipefd[2];
    
    if(pipe(pipefd) < 0) {
        perror("Pipe failed");
        return 0;
    }
    
    pid_t pid = fork();
    
    if (pid < 0) { //fork failed, return 0
        perror("Call fork failed");
        return 0;
    }
    else if (pid == 0) { //child process, writes - left child
        close(pipefd[0]);
        close(pipefd[1]);
        this->left->execute();
        return 1;
    }
    else { //parent process, reads - right child
        int status; //status of child process
        if (waitpid(pid, &status, 0) == -1) { //waits for child process to finish
            perror("Call waitpid has failed");
            return 1; 
        }
        else {
            close(0); //closes stdin
            dup(pipefd[0]); // puts read end of pipe in dup
            close(pipefd[0]);
            close(pipefd[1]);
            this->right->execute();
            return 1;
        }
    }
    
    
}