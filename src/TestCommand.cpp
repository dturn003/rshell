#include <sys/stat.h>

TestCommand::TestCommand(const vector<string> &v) : Command(v) {
    this->flag = args[1][1];
}

int TestCommand::execute() {
    if (length != 4) {
        cout << "Improper input: test command" << endl;
    }
    struct stat buf;
    if(stat(args[2], &buf) < 0) {
        perror("stat() failed");
    }
    if (flag == 'e') {
        
    }
    else if (flag == 'f') {
        
    }
    else if (flag == 'd') {
        
    }
    else {
        cout << "Improper flag: test command" << endl;
    }
}