#ifndef OR_CONNECTOR_H
#define OR_CONNECTOR_H

#include "Connector.h"

class OrConnector : public Connector
{
    public:
    OrConnector(BaseAction* left_temp, BaseAction* right_temp) : Connector(left_temp, right_temp) { };
    int  execute();
};

#endif
