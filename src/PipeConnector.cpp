#include "PipeConnector.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

PipeConnector::PipeConnector() : Connector() {}
PipeConnector::PipeConnector(BaseAction* left, BaseAction* right) : Connector(left, right) {}

int PipeConnector::execute() {
    int pipefd[2];//0-input end, 1-output end
    
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
        // dup(pipefd[1]);
        dup2(pipefd[1], fileno(stdout));
        this->left->execute();
        return 1;
    }
    else { //parent process, reads - right child
        close(pipefd[1]);
        // dup(pipefd[0]); // puts read end of pipe in dup
        dup2(pipefd[0], fileno(stdin));
        this->right->execute();
        return 1;
    }
    
    
}