#ifndef ALWAYS_CONNECTOR_H
#define ALWAYS_CONNECTOR_H

#include "Connector.h"

class AlwaysConnector : public Connector
{
    public:
        AlwaysConnector(BaseAction* left_temp, BaseAction* right_temp) : Connector(left_temp, right_temp) { };
        bool execute();
};

#endif
