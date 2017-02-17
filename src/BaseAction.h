#ifndef BASE_ACTION_H
#define BASE_ACTION_H

class BaseAction
{
    public:
        BaseAction() {};
        virtual ~BaseAction();
        virtual BaseAction* getLeft() = 0;
        virtual BaseAction* getRight() = 0;
        virtual void setRight(BaseAction* right) = 0;
        virtual void setLeft(BaseAction* left) = 0;
        virtual bool execute() = 0;
};

#endif
