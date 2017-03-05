#include "Parser.h"
#include <iostream>

void Parser::pushCommand(std::stack<std::unique_pointer<BaseAction> > &operands, std::vector<std::string> &args) {
    if (args.size() != 0) { //checks if empty command 
        if (args.at(0) == "exit") {
            operands.push(std::make_unique<ExitCommand>(args));
        }
        else if (args.at(0) == "test") {
            operands.push(std::make_unique<TestCommand>(args));
        }
        else if (args.at(0) == "[") {
            operands.push(std::make_unique<TestCommand>(args));
        }
        else {
             operands.push(std::make_unique<BinCommand>(args));
        }
        args.clear();
    }
}

bool Parser::process(std::stack<std::unique_pointer<BaseAction> > &connects, std::stack<std::unique_pointer<BaseAction> > &operands) {
    if (operands.empty()) {
        //TODO: error with first connector
        return false; //std::stack was empty, Connector has no children. process failed.
    }
    else {
        std::unique_pointer<BaseAction> rightOp = operands.top(); //moves ownership to rightOp
        operands.pop();
        
        if (operands.empty()) {
            //TODO: error rhs of connects top()
            return false; //std::stack was empty after popping only 1 element, Connector does not have 2 children. process failed.
        }
        else {
            std::unique_pointer<BaseAction> leftOp = operands.top(); //moves ownership to leftOp
            operands.pop();
            std::unique_pointer<BaseAction> result = connects.top(); //moves ownership to resultant connector
            result->setLeft(leftOp); //leftOp switches ownership to result
            result->setRight(rightOp); //rightOp switches ownership to result
            operands.push(result); 
            connects.pop();
            return true; //process succeeded.
        }
    }
}

//change first 'if' to 'while' if there is precedence among connectors
bool Parser::cycle(std::stack<std::unique_pointer<BaseAction> > &connects, std::stack<std::unique_pointer<BaseAction> > &operands) {
    if (!connects.empty() && (connects.top() != LEFT)) { //keep processing until we hit a left parenthesis or empty std::unique_pointer<BaseAction> in the connect stack
        bool syntax = process(connects, operands); //syntax represents if each Connector has the correct number of children to process.
        if (!syntax) {
            return false;
        }
    }
    return true;
}

bool Parser::checkDouble(char link, Tok::iterator &it, Tok::iterator last)
{
    if (it == last) { //if iterator is already last token. No double to be read in.
        return false;
    }
    
    if ( ( (++it) != last ) && it->empty() ) { //checks if next character is an empty token
        if ( ( (++it) != last ) && it->at(0) == link ) { //checks if same character
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

std::unique_pointer<BaseAction> Parser::parse(const std::string &input)
{
    //initializes two std::stacks for Djikstra's shunting yard algorithm
    std::stack<std::unique_pointer<BaseAction> > connects; //Connectors
    std::stack<std::unique_pointer<BaseAction> > operands; //Commands/Connectors
    
    std::vector<std::string> args; //stores std::vector of arguments for reading in commands
    
    boost::char_separator<char> sep(" ", ";&|#()", boost::keep_empty_tokens); //splits up std::string input into tokens of connector and commands/arguments
    Tok tokens(input, sep); //list of tokens
    Tok::iterator last = tokens.end(); //ending token
    
    for (Tok::iterator it = tokens.begin(); it != last; ++it) { //iterates through list of tokens
        if ((*it) != "") { //if not blank token
            char link = it->at(0);
        
            if (link == '#') //stop parsing, it's a comment
                break; //exits for loop
            else if (link == '(') {
                if (args.size() != 0) { //there should be no command to push to operands, if there are, there is a user input error
                    std::cout << "Unexpected token near '('" << std::endl;
                    return nullptr;
                }
                connects.push(LEFT); //push left parenthesis
            }
            else if (link == ')') {
                pushCommand(operands, args);
                if (!connects.empty() && connects.top() == LEFT) { //case of (), but no command
                    std::cout << "Unexpected token near ')'" << std::endl;
                    return nullptr;
                }
                if (!cycle(connects, operands)) {
                    //TODO: unaware of what to print here
                    std::cout << "Unexpected token before ')'" << std::endl;
                    return nullptr;
                }
                if (connects.empty()) { //there should still be a left parenthesis if correct
                    std::cout << "No corresponding '(' token found" << std::endl;
                    return nullptr;
                }
                connects.pop(); //pops left parenthesis
            }
            else if (link == ';') { //checks if AlwaysConnector
                pushCommand(operands, args);
                if (!cycle(connects, operands)) {
                    std::cout << "Unexpected token near ';'" << std::endl;
                    return nullptr;
                }
                connects.push(std::unique_pointer<AlwaysConnector>());
            }
            else if (link == '&') { //initial check for checkDouble
                if (checkDouble('&', it, last)) { //checks if AndConnector
                    pushCommand(operands, args); 
                    if (!cycle(connects, operands)) {
                        std::cout << "Unexpected token near '&&'" << std::endl;
                        return nullptr;
                    }
                    connects.push(std::unique_pointer<AndConnector>()); //pushes AndConnector onto connects
                }
                else { //detected only a single '&'
                    std::cout << "Unexpected token near '&'" << std::endl;
                    return nullptr;
                }
            }
            else if (link == '|') { //initial check for checkDouble
                if (checkDouble('|', it, last)) { //checks if OrConnector
                    pushCommand(operands, args);
                    if (!cycle(connects, operands)) {
                        std::cout << "Unexpected token near '||'" << std:: endl;
                        return nullptr;
                    }
                    connects.push(std::unique_pointer<OrConnector>()); //pushes OrConnector onto connects
                }
                else { //detected only a single '|'
                    std::cout << "Unexpected token near '|'" << std:: endl;
                    return nullptr;
                }
            }
            else { //Else, add to args
                args.push_back(*it);
            }
        }
    }
    
    //Last pass to read in final command, and process final Connector if they exist.
    pushCommand(operands, args); //pushes last command if there was one
    if (!cycle(connects, operands)) { //cycle last connector if there is one since there was no future connector to call cycle.
        
        return nullptr;
    }
    else if (!connects.empty()) { //remaining left parenthesis, no right parenthesis in user input
        std::cout << "No corresponding token ')' found" << std::endl;
        return nullptr;
    }
    else if (operands.empty()) { //empty command line
        return nullptr;
    }
    else {
        return operands.top();
    }
}