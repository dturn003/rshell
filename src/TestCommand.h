#ifndef TEST_COMMAND_H
#define TEST_COMMAND_H

#include "BaseAction.h"
#include <vector>
#include <string>

class TestCommand : public BaseAction {
    private:
        std::string flag;
        std::string path;
        std::string errorMessage;
        
    public:
        /*
        args.size() == 3 -> "test" flag path
        args.size() == 2 -> flag path
        args.size() == 1 -> path
        */
        TestCommand(const std::vector<std::string> &v);
        TestCommand(int length, const std::vector<std::string> &v);
        int execute();
};

#endif