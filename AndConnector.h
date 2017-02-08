#ifndef AND_CONNECTOR_H
#define AND_CONNECTOR_H

#include "Connector.h"

class AndConnector : public Connector
{
public:
	AndConnector(BaseAction* left_temp, BaseAction* right_temp) : Connector(left_temp, right_temp) { };
	bool execute();
};

#endif