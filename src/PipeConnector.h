#ifndef PIPCONNECTOR_H
#define PIPECONNECTOR_H

#include "Connector.h"

class PipeConnector : public Connector {
    private:
        
    public:
        PipeConnector();
        PipeConnector(BaseAction*, BaseAction*);
        int execute();
};

#endif