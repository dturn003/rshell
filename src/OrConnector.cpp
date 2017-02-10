#include "OrConnector.h"

bool OrConnector::execute()
{
    if (left -> execute()) //execute left child
    {
        return true; //left was executed successfully, return true
    }
    else
    {
        return right -> execute(); //execute right child and return it's value
    }
}