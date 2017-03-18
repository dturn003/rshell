#ifndef OUTPUTCONNECTOR_H
#define OUTPUTCONNECTOR_H

#include "Redirector.h"
#include <string>

using namespace std;

class OutputConnector : public Redirector {
    public:
        OutputConnector(BaseAction* command, string file);
        int execute();
    
};

#endif