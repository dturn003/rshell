#ifndef ALWAYS_CONNECTOR_H
#define ALWAYS_CONNECTOR_H

#include "Connector.h"

class AlwaysConnector : public Connector {
    public:
        AlwaysConnector() {};
        AlwaysConnector(BaseAction* left_temp, BaseAction* right_temp) : Connector(left_temp, right_temp) { };
        int execute();
};

#endif
