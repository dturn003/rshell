#ifndef FILE_COMMAND_H
#define FILE_COMMAND_H

//Hierarchy
#include "BaseAction.h"

//Libraries
#include <vector>
#include <string>

class BinCommand : public BaseAction
{
    private:
        vector<string> file;
    public:
        FileCommand(const std::vector<std::string> &v) : file(v);
        
        int execute();
};

#endif
