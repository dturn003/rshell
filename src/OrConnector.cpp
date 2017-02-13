#include "OrConnector.h"

bool OrConnector::execute()
{
    bool out = false;
    if(left) {
        out = left->execute();
        if (out) //execute left child
        {
            return true; //left was executed successfully, return true
        }
        else
        {
            if(right) {
                 return right -> execute(); //execute right child and return it's value
            }
        }
    }
    return out;
}
