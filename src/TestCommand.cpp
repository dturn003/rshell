#include <sys/stat.h>

TestCommand::TestCommand(const vector<string> &v) : Command(v) {
    this->flag = args[1][1];
}

int TestCommand::execute() {
    if (length != 4) {
        cout << "Improper input: test command" << endl;
    }
    
    struct stat buf; //struct returned by stat
    int statOut = stat(args[2], &buf);
    if (statOut < 0) {
        perror("stat() failed");
    }

    
    if (flag == 'e') {
        if (statOut == 0) {
            cout << "(False)" << endl;
            return 0;
        }
        else {
            cout << "(True)" << endl;
            return 1;
        }
    }
    else if (flag == 'f') {
        if (statOut == 0) {
            cout << "(False)" << endl;
            return 0;
        }
        else {
            return S_ISREG(buf.st_mode);
        }
    }
    else if (flag == 'd') {
        if (statOut == 0) {
            cout << "(False)" << endl;
            return 0;
        }
        else {
            return S_ISDIR(buf.st_mode);
        }
    }
    else {
        cout << "Improper flag: test command" << endl;
        return -1;
    }
}