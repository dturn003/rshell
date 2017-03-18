#ifndef APPENDCONNECTOR_H
#define APPENDCONNECTOR_H

#include "Redirector.h"
#include <string>

using namespace std;

class AppendConnector : public Redirector {
    public:
        AppendConnector(BaseAction* command, string file);
        int execute();
    
};

#endif