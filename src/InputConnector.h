#ifndef INPUTCONNECTOR_H
#define INPUTCONNECTOR_H

#include "BaseAction.h"

#include <string>
using namespace std;

class InputConnector : public BaseAction {
    private:
        BaseAction* command;
        char* file;
    public:
        InputConnector(BaseAction* command, string file);
        ~InputConnector();
        int execute();
        
};

#endif