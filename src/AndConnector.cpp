#include "AndConnector.h"

int AndConnector::execute() {
        int out = 0;
        if(left) {
            out = left->execute();
            if(out == -1) {
                return -1;
            }
            if (out == 1 && right) //execute left child
	    {
		out = right->execute(); //execute right child and return
	    }       
	}
	return out;
}
