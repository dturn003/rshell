#include "AlwaysConnector.h"

bool AlwaysConnector::execute() 
{
    bool out = false;
    if(left) {
        out = left -> execute(); //execute left child
    }
    if(right) {
        out = right -> execute(); //execute right child and return 
    }
    return out;
}
