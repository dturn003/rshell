#include "OutputConnector.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

OutputConnector::OutputConnector(BaseAction* command, string file) : Redirector(command, file) { }

int OutputConnector::execute() {
    int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd < 0) {
        perror("open");
    }
    
    pid_t pid = fork();
    
    if (pid < 0) { //fork failed, return 0
        perror("Call fork failed");
        return 0;
    }
    else if (pid == 0) { //child proccess
        close(1);//close std input
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