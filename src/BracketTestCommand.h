#ifndef BRACKET_TEST_COMMAND_H
#define BRACKET_TEST_COMMAND_H

#include "TestCommand.h"

class BracketTestCommand : public TestCommand {
    public:
        /*
        args.size() == 3 -> "test" flag path
        args.size() == 2 -> flag path
        args.size() == 1 -> path
        */
        BracketTestCommand(const vector<string> &v);
};

#endif