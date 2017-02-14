#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "BaseAction.h"

class Connector : public BaseAction {
    public:
        Connector(BaseAction* left_temp, BaseAction* right_temp) : BaseAction(left_temp, right_temp) { };
        virtual bool execute() = 0;
};

#endif
