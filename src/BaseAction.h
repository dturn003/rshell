#ifndef BASE_ACTION_H
#define BASE_ACTION_H

class BaseAction
{
    public:
	BaseAction() {};
    virtual bool execute() = 0;
};

#endif