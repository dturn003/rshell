#include "OrConnector.h"

int OrConnector::execute() {
    int out = 0;
    if(left) {
        out = left->execute();
        if (out == 1) //execute left child
        {
            return true; //left was executed successfully, return true
        }
        else if(out == 0)
        {
            if(right) {
                 return right -> execute(); //execute right child and return it's value
            }
        }
        else {
            return -1;
        }
    }
    return out;
}
