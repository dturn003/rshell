#include "Parser.h"

//helper function for process
//creates the connectors in the heap and returns their pointers
//argument op must be pre-determiend to be And, Or, Always before calling this function.
//left and right should be pre-determiend to be valid as well
Connector* Parser::createConnect(Operator op, BaseAction* left, BaseAction* right)
{
    switch(op)
    {
        case And:
            return new AndConnector(left, right);
            break;
        case Or:
            return new OrConnector(left, right);
            break;
        case Always:
            return new AlwaysConnector(left, right);
            break;
        default: //default, should never arrive here
            return 0;
            break;
    }
}

//deletes the current tree
void Parser::deleteTree(BaseAction* curr)
{
    BaseAction* left = curr->getLeft();
    BaseAction* right = curr->getRight();
    
    if (left)
    {
        deleteTree(left);
    }
    if (right)
    {
        deleteTree(right);
    }
    delete curr;
}

//helper function for parse
//creates new command based on given args vector and pushes it onto operands stack
//clears args vector
void Parser::pushCommand(stack<BaseAction*> &operands, vector<string> &args)
{
    if (args.size() != 0) //checks if empty command
    {
        if (args.at(0).at(0) == "exit")
        {
            operands.push(new ExitCommand());
        }
        if (args.at(0).at(0) == "[" && args.at(size() - 1) == "]")
        {
            args.push_front("test");
            operands.push(new TestCommand(args));
        }
        else
        {
             operands.push(new Command(args));
        }
        args.clear();
    }
}

//helper function for cycle
//process() pops the top Operator in connects, two operands are popped, and the resultant connector is pushed into operands
//process returns true if user input is correct, and false if the connector is missing a command to form its left and right pointers
//process assumes connects.top() is a valid Operator i.e. And, Or, Always NOT Left
bool Parser::process(stack<Operator> &connects, stack<BaseAction*> &operands)
{
    if (operands.empty())
    {
        return false; //stack was empty, return false for bad user input
    }
    else
    {
        BaseAction* rightOp = operands.top();
        operands.pop();
        
        if (operands.empty())
        {
            deleteTree(rightOp);
            return false; //stack was empty after popping only 1 element, bad user input
        }
        else
        {
            BaseAction* leftOp = operands.top();
            operands.pop();
            operands.push(createConnect(connects.top(), leftOp, rightOp)); //creates the connector and pushes it to op
            connects.pop();
            return true;
        }
    }
}

//cycle keeps processing the connects stack until the connects stack is empty or hits a left parenthesis
//cycle returns true if user input is correct, and false if the connector is missing a command to form its left and right pointers
bool Parser::cycle(stack<Operator> &connects, stack<BaseAction*> &operands)
{
    while (!connects.empty() && (connects.top() != Left)) //keep processing until we hit a left parenthesis or empty operator stack
    {
        bool syntax = process(connects, operands); //syntax represents if the user input is correct or not
        if (!syntax)
        {
            return false;
        }
    }
    return true;
}

//checks if char delimiter link appears twice in a row
//if yes, return true, otherwise false
//assumes iterator it starts as valid i.e. not == to last or beyond last
bool Parser::checkDouble(char link, Tok::iterator &it, Tok::iterator last)
{
    if (it == last) //if it is already last
    {
        return false;
    }
    
    if ( ( (++it) != last ) && it->empty() ) //checks if next character is an empty token
    {
        if ( ( (++it) != last ) && it->at(0) == link ) //checks if same character
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

//takes in string input and tokenizes it.
//constructs and executes the design hierarchy if input is valid
//if input is not valid, returns true to cycle back for more user input, else exit
//true = continue to get user input, false = exit
//utilizes infix evaluation algorithm to determine parsing
bool Parser::parse(const string &input) //returns false if exiting, otherwise true
{
    stack<Operator> connects;
    stack<BaseAction*> operands; //operations to be connected with, always max 2 in the stack
    vector<string> args; //vector of argument list
    
    boost::char_separator<char> sep(" ", ";&|#()", boost::keep_empty_tokens); //splits up string input into tokens of connector and commands/arguments
    Tok tokens(input, sep); //list of tokens
    Tok::iterator last = tokens.end(); //ending token
    
    for (Tok::iterator it = tokens.begin(); it != last; ++it) //goes through list of tokens
    {
        if ((*it) != "") //if not blank token
        {
            char link = it->at(0);
        
            if (link == '#') //stop parsing, it's a comment
                break; //exits for loop
            else if (link == '(')
            {
                if (args.size() != 0) //there should be no command to push to operands, if there are, there is a user input error
                {
                    return true;
                }
                
                connects.push(Left); //push left parenthesis
            }
            else if (link == ')')
            {
                pushCommand(operands, args); //clears args, pushes new command onto operands stack
    
                if (!cycle(connects, operands))
                {
                    return true;
                }
                if (connects.empty()) //there should still be a left parenthesis if correct
                {
                    return true; //user input error: no left parenthesis
                }
                
                connects.pop(); //pops left parenthesis
            }
            else if (link == ';') //checks if AlwaysConnector
            {
                pushCommand(operands, args); //clears args, pushes new command onto operands stack
                
                if (!cycle(connects, operands))
                {
                    return true;
                }
                connects.push(Always);
            }
            else if (link == '&') //checks if AndConnector
            {
                if (checkDouble('&', it, last))
                {
                    pushCommand(operands, args); //clears args, pushes new command onto operands stack
    
                    if (!cycle(connects, operands))
                    {
                        return true;
                    }
                    connects.push(And); //pushes AndConnector onto connects
                }
                else
                {
                    
                    return true;
                }
                
            }
            else if (link == '|') //checks if OrConnector
            {
                if (checkDouble('|', it, last))
                {
                    pushCommand(operands, args); //clears args, pushes new command onto operands stack
    
                    if (!cycle(connects, operands))
                    {
                        return true;
                    }
                    connects.push(Or); //pushes AndConnector onto connects
                }
                else
                {
                    return true;
                }
            }
            else //Else, add to args vector
            {
                args.push_back(*it);
            }
        }
    }
    
    pushCommand(operands, args); //clears args, pushes new command onto operands stack
    
    if (!cycle(connects, operands)) //cycle 
    {
        return true;
    }
    
    if (!connects.empty()) //remaining left parenthesis, no right parenthesis in user input
    {
        deleteTree(operands.top());
        return true; 
    }
    
    if (operands.empty()) //empty commands
    {
        return true;
    }
    
    if (operands.top()->execute() == -1) //execute, if exit, return false
    {
        deleteTree(operands.top());
        return false;
    }
    
    deleteTree(operands.top());
    return true;
}



/*
//helper function for cycle
//skeleton code, should be added to if operators/connectors have precedence
//returns true if the precedence of link1 > link2
//returns false if the precedence of link1 <= link2
bool Parser::checkPrecedence(Operator link1, Operator link2)
{
    return false;
}
*/

/*
//this version of cycle accounts for precedence in its operators
//keeps processing until connects is empty, hit a left parenthesis, or curr is of greater precedence than the previous one
bool Parser::cycle(Operator curr)
{
    //keep processing until left parenthesis or empty operator stack or curr > top in precedence
    while ( (!connects.empty() && (connects.top() != Left)) && checkPrecedence(connects.top(), curr) ) 
    {
        bool syntax = process(); //syntax represents if the user input is correct or not
        if (!syntax)
        {
            return false;
        }
    }
    return true;
}
*/
