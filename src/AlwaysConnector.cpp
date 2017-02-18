#include "AlwaysConnector.h"

int AlwaysConnector::execute() 
{
    int out = 0; //out is false
    if(left) {
        out = left -> execute(); //execute left child
    }
    if(out == -1) {
        return -1;
    }
    if(right) {
        out = right -> execute(); //execute right child and return 
    }
    return out;
}
