#ifndef REDIRECTOR_H
#define REDIRECTOR_H

#include "BaseAction.h"
#include <string>
#include <string.h>

using namespace std;

class Redirector : public BaseAction {
    protected:
        BaseAction* command;
        char* file;
    public:
        Redirector(BaseAction* command, string file) {
            this->command = command;
            this->file = new char[file.size() + 1];
            strcpy(this->file, file.c_str());
        }
        ~Redirector() {
            delete command;
            delete[] file;
        }
        virtual int execute();
    
};

#endif