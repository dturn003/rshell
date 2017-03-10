#ifndef COMMAND_H
#define COMMAND_H

//Hierarchy
#include "BaseAction.h"

//Libraries
#include <vector>
#include <string>

class BinCommand : public BaseAction
{
    protected:
        unsigned length;
        char** args; //args[0] is the command
        
    public:
        BinCommand(const std::vector<std::string> &);
        ~BinCommand();
        
        int execute();
};

#endif
