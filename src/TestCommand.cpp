#include <sys/stat.h>
#include <iostream>
#include <stdio.h>

#include "TestCommand.h"

int TestCommand::execute() {
    if (!validArgs)
    {
        cout << "Invalid argument length" << endl;
        return 0;
    }
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
    if (flag == "-e") {
        cout << "(True)" << endl;
        return 1;
    }
    else if (flag == "-f") { //tests if regular file
        if(S_ISREG(buf.st_mode)) {//is regular file macro
            cout << "(True)" << endl;
            return 1;
        }
        else {
            cout << "(False)" << endl;
            return 0;
        }
    }
    else if (flag == "-d") { //tests if directory
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
        return 0;
    }
}