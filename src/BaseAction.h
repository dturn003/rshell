#ifndef BASE_ACTION_H
#define BASE_ACTION_H

class BaseAction
{
    protected:
        BaseAction* left;
        BaseAction* right;
    public:
        BaseAction() {};
        BaseAction(BaseAction* left, BaseAction* right): left(left), right(right) {};
        BaseAction* getLeft() {
            return left;
        }
        BaseAction* getRight() {
            return right;
        }
        void setRight(BaseAction* right) {
            this->right = right;
        }
        void setLeft(BaseAction* left) {
            this->left = left;
        }
        virtual bool execute() = 0;
};

#endif
