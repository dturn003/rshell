#ifndef OUTPUTCONNECTOR_H
#define OUTPUTCONNECTOR_H

#include "BaseAction.h"
#include <string>

using namespace std;

class OutputConnector : public BaseAction {
    private:
        BaseAction* command;
        char* file;
    public:
        OutputConnector(BaseAction* command, string file);
        ~OutputConnector();
        int execute();
    
};

#endif