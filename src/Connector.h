#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "BaseAction.h"

class Connector : public BaseAction
{
	protected:
	BaseAction* left;
	BaseAction* right;

    public:
    Connector(BaseAction* left_temp, BaseAction* right_temp) : left(left_temp), right(right_temp) { };
    virtual bool execute() = 0;
};

#endif