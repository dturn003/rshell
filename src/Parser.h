#ifndef PARSER_H
#define PARSER_H

//Leaves/Commands
#include "ExitCommand.h"
#include "TestCommand.h"
#include "BinCommand.h"

//Composites/Connectors
#include "AndConnector.h"
#include "OrConnector.h"
#include "AlwaysConnector.h"
#include "PipeConnector.h"
#include "InputConnector.h"
#include "OutputConnector.h"

//Libraries
#include <string>
#include <vector>
#include <stack>
#include <boost/tokenizer.hpp>

class Parser
{
    private:
        typedef boost::tokenizer<boost::char_separator<char > > Tok; //defines tokenizer object
        BaseAction* LEFT = nullptr; //represents Left parenthesis, means of identifying '(' in Connector stack
        
        boost::tokenizer<boost::char_separator<char> >::iterator getNext(Tok::iterator it, Tok::iterator last);
        
        void deleteStacks(std::stack<BaseAction*> & operands, std::stack<BaseAction*> & connects);
        
        /*
            Assumptions: The type of command is determined by args.at(0), or the command name.
                         If the command fits the format of any of our built in commands, we create
                         that command. If not, it will automatically allocate that command as a bin 
                         command. It is up to the individual command classes to determine if the 
                         actual command was correct or not when execute() is called.
                         
            Description: pushCommand takes the complete command and argument list, std::vector<std::string> &args,
                         and determines what command to push to the std::stack of operands. If there is no 
                         command to push(args is empty), then the method does not push the command into
                         the operands std::stack. pushCommand then clears args so the parser may read in the 
                         next command.
                         
                    Use: Use pushCommand when the parser detects that the complete args list is finished.
                         This situation occurs during one of two scenarios
                         1.     We have read in a connector (&&, ||, ;)
                         2.     We have reached the end of the token list (Last command)
        */
        void pushCommand(std::stack<BaseAction*> &operands, std::vector<std::string> &args);
        
        /*
            Assumptions: process assumes that it is perfectly fine to start connecting the top Connector
                         of the connects std::stack with its children. The other method, cycle, takes care of 
                         when to process. This means the connect stack must not be empty and top != nullptr.
                         process also assumes connector is binary (only has two children).
                         
            Description: process returns 'true' if the current Connector has been correctly processed.
                         process is defined by the following steps:
                         1.     Pop operand std::stack twice. Each BaseAction* element represents
                                the left or right action (connectors or commands) to be connected
                                with the the current top Connector of the connects std::stack.
                                
                         2.     Pop the connects std::stack once. Now that the top Connector is being
                                parsed, we no longer needs to store it as a connector to
                                be processed in the future.
                         
                         3.     Push resultant Connector onto operands std::stack. The resultant connector
                                is defined as having been connected with its correct children/operands.
                                We push the resultant connector onto the operands std::stack so that it can be
                                used as the child of the next connector we may parse in the future.
                                
                    Use: Use process when we have determined that another Connector has been read in from
                         the token list, and it is fine to process previous connectors.
        */
        bool process(std::stack<BaseAction*> &connects, std::stack<BaseAction*> &operands);
        
        /*
            Assumptions: connects stack is not empty; there is a top BaseAction*.
                         
            Description: cycle correctly parses the syntax tree in the correct order in which
                         each Connector has come. We need to process the previous Connectors to correctly 
                         parse the tree for the next Connector to be saved in the connects std::stack and for
                         future Connectors to have the correct children according to the syntax of the inputs.
                         
                    Use: Use cycle for when another Connector has been read in from the token list. If
                         precedence is not equal among Connectors in future add-ons, then another method to
                         check precedence must be added and applied to the while loop when the parser reads
                         in normal Connectors, such as ;, &&, ||. However, this specific case of cycle does 
                         not apply when the parser reads in a ')'. In the case that precedence is unequal among 
                         Connectors and the parser has read in a ')', the while loop should ignore the precedence check.
        */
        bool cycle(std::stack<BaseAction*> &connects, std::stack<BaseAction*> &operands);
        
        /*
            Assumptions: checkDouble assumes that an &, | has been read in from inputs and needs to be checked
                         if it is immediately followed by a corresponding &, |, resulting in a complete
                         AndConnector (&&) or OrConnector(||).
                         
            Description: checkDouble checks if user input is a complete && or ||. checkDouble moves the current 
                         (it) position to the next token to be correctly read in (after second & or |).
                         This is to prevent the parser from double reading the second corresponding &, | as
                         a seperate token and call checkDouble again erroneously. If there is a correct double
                         && or ||, then checkDouble returns true. Else, false.
                         
                    Use: Use checkDouble when a Connector to be read in requires two of the same character twice
                         in a row. i.e. &&, ||.
        */
        bool checkDouble(char link, Tok::iterator it, Tok::iterator last);
        
    public:
        Parser() {}; //default constructor
        
        /*
            Assumptions: parse assumes that the complete tree can be constructed from one line of user input.
                         parse does not take in multiple lines of user input.
                         
            Description: parse splits up the input into readable tokens, and applies a version of
                         Djikstra's shunting yard algorithm where commands are operands and 
                         Connectors( &&, ;, ||) are operations. parse returns a pointer to the completed
                         syntax tree if user input was correct or returns a nullptr and prints an error
                         message otherwise.
                         
                    Use: Use parse when the user had input a string of commands in the shell.
        */
        BaseAction* parse(const std::string &input);
};

#endif
