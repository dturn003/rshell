#include <sys/stat.h>

TestCommand::TestCommand(const vector<string> &v) : Command(v) {
    this->flag = args[1][1];
}

int TestCommand::execute() {
    //checks if format is correct for TestCommand object
    if (length != 4) {
        cout << "Improper input: test command" << endl;
    }
    
    struct stat buf; //struct returned by stat function
    int statOut = stat(args[2], &buf); //stat() takes in 1. path for file/directory and 2. struct reference to return to
    if (statOut < 0) {
        perror("stat() failed");
    }

    //tests existence
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
    else if (flag == 'f') { //tests if regular file
        if (statOut == 0) {
            cout << "(False)" << endl;
            return 0;
        }
        else {
            return S_ISREG(buf.st_mode);
        }
    }
    else if (flag == 'd') { //tests if directory
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