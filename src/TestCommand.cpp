#include <sys/stat.h>
#include <iostream>

#include "TestCommand.h"

TestCommand::TestCommand(const vector<string> &v) : Command(v) {
    this->flag = args[1][1];
}

int TestCommand::execute() {
    //checks if format is correct for TestCommand object
    if (length != 4) {
        cout << "Improper input: test command" << endl;
    }
    //checks if default flag should be used as user did not input one
    if (length == 3) {
        flag = 'e';
    }
    
    struct stat buf; //struct returned by stat function
    int statOut = stat(args[2], &buf); //stat() takes in 1. path for file/directory and 2. struct reference to return to
    /*
    if (statOut < 0) {
        perror("stat() failed");
        cout << ("False") << endl;
    }
    */
    
    //if directory/file doesn't exist
    //functions same way for each flag
    if (statOut != 0) {
            cout << "(False)" << endl;
            return 0;
    }
    
    //if directory/file does exist
    //tests flag condition
    if (flag == 'e') {
        cout << "(True)" << endl;
        return 1;
    }
    else if (flag == 'f') { //tests if regular file
        if(S_ISREG(buf.st_mode)) {//is regular file macro
            cout << "(True)" << endl;
            return 1;
        }
        else {
            cout << "(False)" << endl;
            return 0;
        }
    }
    else if (flag == 'd') { //tests if directory
        if(S_ISDIR(buf.st_mode)) {//is directory macro
            cout << "(True)" << endl;
            return 1;
        }
        else {
            cout << "(False)" << endl;
            return 0;
        }
    }
    else {
        cout << "Improper flag: test command" << endl;
        return -1;
    }
}