#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "BaseAction.h"

class Connector : public BaseAction {
    protected:
        BaseAction* left;
        BaseAction* right;
    public:
        Connector(BaseAction* left_temp, BaseAction* right_temp) : left(left_temp), right(right_temp) {};
        ~Connector() {
            delete left;
            delete right;
        };
        
        virtual int execute() = 0;
        BaseAction* getLeft() {
            return left;
        };
        BaseAction* getRight() {
            return right;
        };
        void setLeft(BaseAction* left) {
            this->left = left;
        };
        void setRight(BaseAction* right) {
            this->right = right;
        };
};

#endif
