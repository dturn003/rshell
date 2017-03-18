#include "InputConnector.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

InputConnector::InputConnector(BaseAction* command, string file) : Redirector(command, file) { }

int InputConnector::execute() {
    int fd = open(file, O_RDONLY);
    if(fd < 0) {
        perror("open");
    }
    
    pid_t pid = fork();
    
    if (pid < 0) { //fork failed, return 0
        perror("Call fork failed");
        return 0;
    }
    else if (pid == 0) { //child proccess
        close(0);//close std input
        dup(fd);//replace stdinput with our file
        command->execute();
        close(fd);
        exit(1);
    }
    //parent process
    close(fd);
    wait(0);
    return 1;
}