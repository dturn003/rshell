#include "AlwaysConnector.h"

bool AlwaysConnector::execute() 
{
    left -> execute(); //execute left child
    return right -> execute(); //execute right child and return 
}