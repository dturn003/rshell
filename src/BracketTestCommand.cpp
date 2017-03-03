#include "BracketTestCommand.h"

BracketTestCommand::BracketTestCommand(const vector<string> &v)
{
    if (v.size() == 4 && v.at(3) == "]") {//input as []: flag path or test path
        flag = v.at(1);
        path = v.at(2);
        validArgs = true;
    }
    else if (v.size() == 3 && v.at(2) == "]" ) {//input as [] with implicit flag: path
        flag = "-e";
        path = v.at(1);
        validArgs = true;
    }
    else
    {
        validArgs = false;
    }
}