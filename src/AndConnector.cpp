#include "AndConnector.h"

bool AndConnector::execute()
{
        bool out = false;
        if(left) {
            out = left->execute();
	    if (out && right) //execute left child
	    {
		out = right->execute(); //execute right child and return
	    }       
	}
	return out;
}
