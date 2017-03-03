#ifndef PARSER_H
#define PARSER_H

#include "BaseAction.h"
#include "ExitCommand.h"
#include "TestCommand.h"
#include "Command.h"
#include "Connector.h"
#include "AndConnector.h"
#include "OrConnector.h"
#include "AlwaysConnector.h"

#include <vector>
#include <string>
#include <stack>
#include <boost/tokenizer.hpp>
using namespace std;

class Parser
{
    typedef boost::tokenizer<boost::char_separator<char > > Tok; //defines tokenizer object
    
    private:
        enum Operator {And, Or, Always, Left}; //Left = (, Always = ;, Or = ||, And = &&
        
        //bool checkPrecedence(Operator link1, Operator link2); //checks precedence
        //bool cycle(Operator curr);
        
        void deleteTree(BaseAction* curr);
        bool checkDouble(char link, Tok::iterator &it, Tok::iterator last);
        bool process(stack<Operator> &connects, stack<BaseAction*> &operands); //helper function for cycle
        bool cycle(stack<Operator> &connects, stack<BaseAction*> &operands);
        
        Connector* createConnect(Operator op, BaseAction* left, BaseAction* right); //helper function for process
        void pushCommand(stack<BaseAction*> &operands, vector<string> &args); //helper function for parse

    public:
        
        Parser() {}; //default constructor
        bool parse(const string &input); //returns false if exiting, otherwise true
};

#endif
