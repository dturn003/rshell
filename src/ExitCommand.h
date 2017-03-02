#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "BaseAction.h"

class ExitCommand : public BaseAction {
    public:
        int execute();
        ExitCommand();
};

#endif