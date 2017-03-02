#include <sys/stat.h>
#include <iostream>
#include <stdio.h>

#include "TestCommand.h"

TestCommand::TestCommand(const vector<string> &v) {
    if(v.size() == 3) { //input like regular command: test flag path
        flag = v.at(1).at(1);
        path = v.at(2);
    }
    else if (v.size() == 2) {//input as []: flag path
        flag = v.at(0).at(1);
        path = v.at(1);
    }
    else if (v.size() == 1){//input as [] with implicit flag: path
        flag = 'e';
        path = v.at(0);
    }
    else {//any other amount of input is wrong
        cout << "Improper input: test command" << endl;
    }
}

int TestCommand::execute() {
    
    struct stat buf; //struct returned by stat function
    int statOut = stat(path.c_str(), &buf);

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
            perror("stat() failed");
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