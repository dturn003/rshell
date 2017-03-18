#ifndef INPUTCONNECTOR_H
#define INPUTCONNECTOR_H

#include "Redirector.h"

#include <string>
using namespace std;

class InputConnector : public Redirector {
    public:
        InputConnector(BaseAction* command, string file);
        int execute();
        
};

#endif