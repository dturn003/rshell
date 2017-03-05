#include "TestCommand.h"

#include <sys/stat.h>
#include <iostream>
#include <stdio.h>

TestCommand::TestCommand(int length, const std::vector<std::string> &v) {
    //int length = v.size();
    if (length == 4) {//input as []: flag path or test path
        if (v.at(3) == "]") {
            flag = v.at(1);
            path = v.at(2);
            errorMessage = "";
        {
        else {
            errorMessage = "Expected token ']'";
        }
    }
    else if (length == 3) {//input as [] with implicit flag: path
        if (v.at(2) == "]") {
            flag = "-e";
            path = v.at(1);
            errorMessage =  "";
        }
        else {
            errorMessage = "Expected token ']'";
        }
    }
    else {
        errorMessage = "Invalid argument length";
    }
}
    
TestCommand::TestCommand(const std::vector<std::string> &v) {
    int length = v.size();
    if(length == 3) { //input like regular command: test flag path
        flag = v.at(1);
        path = v.at(2);
        errorMessage = "";
    }
    else if (length == 2) {
        flag = "-e";
        path = v.at(1);
        errorMessage = "";
    }
    else { //any other amount of input is wrong
        errorMessage = "Invalid argument length";
    }
}

int TestCommand::execute() {
    if (errorMessage.size() == 1) {
        cout << "Invalid argument length" << endl;
        return ExitStatus::FAILURE;
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
            return 0
    }
    
    //if directory/file does exist
    //tests flag condition
    if (flag == "-e") {
        cout << "(True)" << endl;
        return 1 //ExitStatus::SUCCESS;
    }
    else if (flag == "-f") { //tests if regular file
        if(S_ISREG(buf.st_mode)) {//is regular file macro
            cout << "(True)" << endl;
            return 1 //ExitStatus::SUCCESS;
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