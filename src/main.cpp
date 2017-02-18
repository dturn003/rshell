#include <iostream>

#include "BaseAction.h"
#include "AndConnector.h"
#include "AlwaysConnector.h"
#include "OrConnector.h"
#include "Command.h"
#include <stack>
#include <boost/tokenizer.hpp>
using namespace std;
using namespace boost;

//the stack represents the left and right nodes that need to be set into prevConnector
//resetStack sets these connections and returns false if there is an error in tree construction
bool resetStack(Connector* connect, stack<BaseAction*> &op)
{
    if (op.empty())
    {
        return false; //stack was empty, return false for bad user input
    }
    else
    {
        connect->setRight(op.top()); //sets right child of the connector
        op.pop();
        
        if (op.empty())
        {
            return false; //stack was empty after popping only 1 element, bad user input
        }
        else
        {
            connect->setLeft(op.top());
            op.pop();
            op.push(connect); //pushes next node to build on tree
            return true;
        }
    }
}

bool parse(const string &input) //returns false if exiting, otherwise true
{
    Connector* prevConnector = 0; //keeps track of the previous connector
    stack<BaseAction*> operands; //operations to be connected with, always max 2 in the stack
  
    vector<string> args; //vector of argument list
    
    typedef tokenizer<char_separator<char > > Tok; //defines tokenizer object
    char_separator<char> sep(" ", ";&|#"); //splits up string input into tokens of connector and commands/arguments
    Tok tokens(input, sep); //list of tokens
    
    for (Tok::iterator it = tokens.begin(); it != tokens.end(); ++it) //goes through list of tokens
    {
        if (it->at(0) == '#') //stop parsing, it's a comment
            break;
            
        if (it->at(0) == ';') //checks if AlwaysConnector
        {
            operands.push(new Command(args));
            args.clear();
            
            if (prevConnector)
            {
                bool syntax = resetStack(prevConnector, operands);
                if (!syntax) //user input is incorrect
                {
                    perror("syntax error, expected a token");
                    return true;
                }
            }

            prevConnector = new AlwaysConnector(0, 0); //replace previous connect with OrConnector
        }
        
        else if (it->at(0) == '&') //checks if AndConnector
        {
            if ((++it) != tokens.end() && it->at(0) == '&') //checks if next character is also &
            {
                operands.push(new Command(args));
                args.clear();
                
                if (prevConnector)
                {
                    bool syntax = resetStack(prevConnector, operands);
                    if (!syntax) //user input is incorrect
                    {
                        perror("syntax error, expected a token");
                        return true;
                    }
                }

                prevConnector = new AndConnector(0, 0); //replace previous connect with OrConnector
            }
            --it;
        }
        
        else if (it -> at(0) == '|') //checks if OrConnector
        {
            if ((++it) != tokens.end() && it->at(0) == '|')
            {
                operands.push(new Command(args));
                args.clear();
                
                if (prevConnector)
                {
                    bool syntax = resetStack(prevConnector, operands);
                    if (!syntax) //user input is incorrect
                    {
                        perror("syntax error, expected a token");
                        return true;
                    }
                }
    
                prevConnector = new OrConnector(0, 0); //replace previous connect with OrConnector
            }
            --it;
        }
        
        else //Else, add to args
        {
            args.push_back(*it);
        }
    }
    
    operands.push(new Command(args)); //pushes back last command
    
    if (prevConnector) //connects last connector
    {
        bool syntax = resetStack(prevConnector, operands);
        if (!syntax) //user input is incorrect
        {
            perror("syntax error, expected a token");
            return true;
        }
    }
    
    if (operands.top()->execute() == -1)
    {
        return false;
    }
    
    return true;
}

int main() {
    
    char* username = getlogin();
    if(!username) {
        perror("getlogin() error");
    }
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname))) {
        perror("gethostname() error");
    }
    
    bool exit = false; 
    while(!exit) {
        cout << username << "@" << hostname << "$ ";
        string input;
        getline(cin, input);
            
        if(!parse(input)) {
            exit = true;
        }
    }
   
    return 0;
}
