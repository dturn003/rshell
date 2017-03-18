#include "Parser.h"
#include <iostream>

void Parser::deleteStacks(std::stack<BaseAction*> & operands, std::stack<BaseAction*> & connects) {
    while (!operands.empty()) {
        delete operands.top();
        operands.pop();
    }
    while (!connects.empty()) {
        delete connects.top();
        connects.pop();
    }
}

void Parser::pushCommand(std::stack<BaseAction*> &operands, std::vector<std::string> &args) {
    if (args.size() != 0) { //checks if empty command 
        if (args.at(0) == "exit") {
            operands.push(new ExitCommand());
        }
        else if (args.at(0) == "test") {
            operands.push(new TestCommand(args));
        }
        else if (args.at(0) == "[") {
            operands.push(new TestCommand(args.size(), args));
        }
        else {
             operands.push(new BinCommand(args));
        }
        args.clear();
    }
}

bool Parser::process(std::stack<BaseAction*> &connects, std::stack<BaseAction*> &operands) {
    if (operands.empty()) {
        return false; //std::stack was empty, Connector has no children. process failed.
    }
    else {
        BaseAction* rightOp = operands.top(); //moves ownership to rightOp
        operands.pop();
        
        if (operands.empty()) {
            return false; //std::stack was empty after popping only 1 element, Connector does not have 2 children. process failed.
        }
        else {
            BaseAction* leftOp = operands.top(); //moves ownership to leftOp
            operands.pop();
            BaseAction* result = connects.top(); //moves ownership to resultant connector
            result->setLeft(leftOp); //leftOp switches ownership to result
            result->setRight(rightOp); //rightOp switches ownership to result
            operands.push(result); 
            connects.pop();
            return true; //process succeeded.
        }
    }
}

//change first 'if' to 'while' if there is precedence among connectors
bool Parser::cycle(std::stack<BaseAction*> &connects, std::stack<BaseAction*> &operands) {
    if (!connects.empty() && (connects.top() != LEFT)) { //keep processing until we hit a left parenthesis or empty BaseAction*in the connect stack
        bool syntax = process(connects, operands); //syntax represents if each Connector has the correct number of children to process.
        if (!syntax) {
            return false;
        }
    }
    return true;
}

bool Parser::checkDouble(char link, Tok::iterator it, Tok::iterator last)
{
    if (it == last) { //if iterator is already last token. No double to be read in.
        return false;
    }
    
    if ( ( (++it) != last ) && it->empty() ) { //checks if next character is an empty token
        if ( ( (++it) != last ) && !(it->empty()) && it->at(0) == link ) { //checks if same character
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

boost::tokenizer<boost::char_separator<char> >::iterator Parser::getNext(Tok::iterator it, Tok::iterator last) {
    while(it != last) {
        if ((*it) != "") { //if not blank token
            return it;
        }
        ++it;
    }
    return last;
}

BaseAction* Parser::parse(const std::string &input)
{
    //initializes two std::stacks for Djikstra's shunting yard algorithm
    std::stack<BaseAction*> connects; //Connectors
    std::stack<BaseAction*> operands; //Commands/Connectors
    std::vector<std::string> args; //stores std::vector of arguments for reading in commands
    
    boost::char_separator<char> sep(" ", ";&|#()<>", boost::keep_empty_tokens); //splits up std::string input into tokens of connector and commands/arguments
    Tok tokens(input, sep); //list of tokens
    Tok::iterator last = tokens.end(); //ending token
    
    for (Tok::iterator it = tokens.begin(); it != last; ++it) { //iterates through list of tokens
        if ((*it) != "") { //if not blank token
            char link = it->at(0);
        
            if (link == '#') //stop parsing, it's a comment
                break; //exits for loop
            else if (link == '(') {
                if (args.size() != 0) { //there should be no command to push to operands, if there are, there is a user input error
                    std::cout << "'('" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr;
                }
                connects.push(LEFT); //push left parenthesis
            }
            else if (link == ')') { //TODO
                pushCommand(operands, args);
                
                if (!connects.empty() && operands.empty() && connects.top() == LEFT) { //case of (), but no command
                    std::cout << "Unexpected token near ')'" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr;
                }
                if (!cycle(connects, operands)) {
                    std::cout << "Unexpected token before ')' token" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr;
                }
                if (connects.empty()) { //there should still be a left parenthesis if correct
                    std::cout << "Unexpected token near ')'" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr;
                }
            
                connects.pop(); //pops left parenthesis
            }
            else if (link == ';') { //checks if AlwaysConnector
                pushCommand(operands, args);
                if (!cycle(connects, operands)) {
                    std::cout << "Unexpected token near ';'" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr;
                }
                connects.push(new AlwaysConnector());
            }
            else if (link == '&') { //initial check for checkDouble
                if (checkDouble('&', it, last)) { //checks if AndConnector
                    ++it; ++it;
                    pushCommand(operands, args); 
                    if (!cycle(connects, operands)) {
                        std::cout << "Unexpected token near '&&'" << std::endl;
                        deleteStacks(operands, connects);
                        return nullptr;
                    }
                    connects.push(new AndConnector()); //pushes AndConnector onto connects
                }
                else { //detected only a single '&'
                    std::cout << "Unexpected token near '&'" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr;
                }
            }
            else if (link == '|') { //initial check for checkDouble
                if (checkDouble('|', it, last)) { //checks if OrConnector
                    ++it; ++it;
                    pushCommand(operands, args);
                    if (!cycle(connects, operands)) {
                        std::cout << "Unexpected token near '||'" << std::endl;
                        deleteStacks(operands, connects);
                        return nullptr;
                    }
                    connects.push(new OrConnector()); //pushes OrConnector onto connects
                }
                else { //detected only a single '|' , TODO: PIPING
                    pushCommand(operands, args);
                    if (!cycle(connects, operands)) {
                        std::cout << "Unexpected token near '|'" << std::endl;
                        deleteStacks(operands, connects);
                        return nullptr;
                    }
                    connects.push(new PipeConnector()); //pushes PipeConnector onto connects
                }
            }
            else if (link == '<') {
                pushCommand(operands, args); 
                Tok::iterator file_ptr = getNext(++it, last);
                if (operands.empty() || file_ptr == last) {
                    std::cout << "Unexpected token near '<'" << std::endl;
                    deleteStacks(operands, connects);
                    return nullptr; //std::stack was empty, Connector has no children. process failed.
                }
                else {
                    BaseAction* singleOp = operands.top();
                    operands.pop();
                    operands.push(new InputConnector(singleOp, *file_ptr));
                    it = file_ptr;
                }
            }
            else if (link == '>') {
                if (checkDouble('>', it, last)) {
                    ++it; ++it;
                    pushCommand(operands, args);
                    Tok::iterator file_ptr = getNext(++it, last);
                    if (operands.empty() || file_ptr == last) {
                        std::cout << "Unexpected token near '>>'" << std::endl;
                        deleteStacks(operands, connects);
                        return nullptr;
                    }
                    else {
                        BaseAction* singleOp = operands.top();
                        operands.pop();
                        operands.push(new AppendConnector(singleOp, *file_ptr));
                        it = file_ptr;
                    }
                }
                else {
                    pushCommand(operands, args); 
                    Tok::iterator file_ptr = getNext(++it, last);
                    if (operands.empty() || file_ptr == last) {
                        std::cout << "Unexpected token near '>'" << std::endl;
                        deleteStacks(operands, connects);
                        return nullptr; //std::stack was empty, Connector has no children. process failed.
                    }
                    else {
                        BaseAction* singleOp = operands.top();
                        operands.pop();
                        operands.push(new OutputConnector(singleOp, *file_ptr));
                        it = file_ptr;
                    }
                }
            }
            else { //Else, add to args
                args.push_back(*it);
            }
        }
    }

    //Last pass to read in final command, and process final Connector if they exist.
    pushCommand(operands, args); //pushes last command if there was one
    if (!cycle(connects, operands)) { //cycle last connector if there is one
        std::cout << "Unexpected token near last connector" << std::endl;
        deleteStacks(operands, connects);
        return nullptr;
    }
    else if (!connects.empty()) { //remaining left parenthesis, no right parenthesis in user input
        std::cout << "Unexpected token near ')'" << std::endl;
        deleteStacks(operands, connects);
        return nullptr;
    }
    else if (operands.empty()) { //empty command line
        return nullptr;
    }
    else {
        return operands.top();
    }
}