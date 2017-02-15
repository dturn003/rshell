#include <iostream>

#include "BaseAction.h"
#include "AndConnector.h"
#include "AlwaysConnector.h"
#include "OrConnector.h"
#include "Command.h"

#include <boost/tokenizer.hpp>


int main() {
	bool exit = false;
	while(!exit) {
		std::cout << "$ ";
		std::string input;
		std::getline(std::cin, input);
		
                //temporary
                if(input == "exit") {
                    exit = true;
                }

		std::string currCommand;
		std::vector<std::string> currArguments;
                
                BaseAction* root = 0;
        
                boost::char_separator<char> sep(" ", ";&|#");
                boost::tokenizer<boost::char_separator<char > > tokens(input, sep);
                bool expectCommand = true;
                BaseAction* curr = root;
                
                for (boost::tokenizer<boost::char_separator<char > >::iterator it = tokens.begin(); it != tokens.end(); ++it) {
                    if (it->at(0) == ';') {
                        BaseAction* left = new Command(currCommand, currArguments);
                        if(curr == 0) {
                            curr = new AlwaysConnector(left, 0);
                        }
                        else {
                            curr->setRight(new AlwaysConnector(left, 0));
                            curr = curr->getRight();
                        }
                        if(root == 0) {
                            root = curr;
                        }
                        currCommand.clear();
                        currArguments.clear();
                        expectCommand = true;
                    }
                    else if (it->at(0) == '#') {
                        break;
                    }
                    else if (it->at(0) == '&') {
                        BaseAction* left = new Command(currCommand, currArguments);
                        
                        if(curr == 0) {
                            curr = new AndConnector(left, 0);
                        }
                        else {
                            curr->setRight(new AndConnector(left, 0));
                            curr = curr->getRight();
                        }
                        if(root == 0) {
                            root = curr;
                        }
                        it++;
                        currCommand.clear();
                        currArguments.clear();
                        expectCommand = true;
                    }
                    else if (it->at(0) == '|') {
                        BaseAction* left = new Command(currCommand, currArguments);
 
                        if(curr == 0) {
                            curr = new OrConnector(left, 0);
                        }
                        else {
                            curr->setRight(new OrConnector(left, 0));
                            curr = curr->getRight();
                        }
                        if(root == 0) {
                            root = curr;
                        }


                        it++;
                        currCommand.clear();
                        currArguments.clear();
                        expectCommand = true;
                    }
                    else {
                        if (expectCommand) {
                            expectCommand = false;
                            currCommand = *it;
                            currArguments.clear();
                        }
                        else {
                            currArguments.push_back(*it);
                        }
                    }
                }
                if(!expectCommand) {
                    if(curr == 0) {
                        curr = new Command(currCommand, currArguments);
                    }
                    else {
                        curr->setRight(new Command(currCommand, currArguments));
                    }
                    if (root == 0) {
                        root = curr;
                    }
                }
                if(root) {
                    root->execute();
                }
	}
	return 0;
}
