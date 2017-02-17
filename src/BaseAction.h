#ifndef BASE_ACTION_H
#define BASE_ACTION_H

class BaseAction
{
    public: 
        BaseAction() {};
        virtual BaseAction* getLeft() {return 0;};
        virtual BaseAction* getRight() {return 0;};
        virtual void setRight(BaseAction* right) {};
        virtual void setLeft(BaseAction* left) {};
        virtual bool execute() = 0;
};

#endif
