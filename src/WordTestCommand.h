#ifndef WORD_TEST_COMMAND_H
#define WORD_TEST_COMMAND_H

#include "TestCommand.h"

class WordTestCommand : public TestCommand {
    public:
        /*
        args.size() == 3 -> "test" flag path
        args.size() == 2 -> flag path
        args.size() == 1 -> path
        */
        WordTestCommand(const vector<string> &v);
};

#endif