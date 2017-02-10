#include "AndConnector.h"

bool AndConnector::execute()
{
	if (left->execute()) //execute left child
	{
		return right->execute(); //execute right child and return
	}
	
	return false;
}