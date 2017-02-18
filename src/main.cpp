#include <iostream>

#include "BaseAction.h"
#include "AndConnector.h"
#include "AlwaysConnector.h"
#include "OrConnector.h"
#include "Command.h"

#include <boost/tokenizer.hpp>
#include <unistd.h>

using namespace std;
using namespace boost;


bool parse(const string &input) {
    
    BaseAction* root = 0;
    BaseAction* curr = root;
    
    vector<string> currArguments; //vector of argument list
    bool expectCommand = true; //flag to expect next command
    
    typedef tokenizer<char_separator<char > > Tok; //defines tokenizer object
    char_separator<char> sep(" ", ";&|#"); //splits up string input into tokens of connector and commands/arguments
    Tok tokens(input, sep); //list of tokens
    
     for (Tok::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        if (it->at(0) == ';') {
            BaseAction* temp = new Command(currArguments);
            if(curr == 0) {
                curr = new AlwaysConnector(temp, 0);
                root = curr;
            }
            else {
                if(curr->getLeft() == 0) {
                    curr->setLeft(temp);
                }
                else if (curr->getRight() == 0) {
                    curr->setRight(temp);
                }
                root = new AlwaysConnector(curr, 0);
                curr = root;
            }
            currArguments.clear();
            expectCommand = true;
        }
        else if (it->at(0) == '#') {
            break;
        }
        else if (it->at(0) == '&') {
            BaseAction* temp = new Command(currArguments);
            
            if(curr == 0) {
                curr = new AndConnector(temp, 0);
                root = curr;
            }
            else {
                if(curr->getLeft() == 0) {
                    curr->setLeft(temp);
                }
                else if (curr->getRight() == 0) {
                    curr->setRight(temp);
                }
                root = new AndConnector(curr, 0);
                curr = root;
            }
            
            it++;
            currArguments.clear();
            expectCommand = true;
        }
        else if (it->at(0) == '|') {
            BaseAction* temp = new Command(currArguments);

            if(curr == 0) {
                curr = new OrConnector(temp, 0);
                root = curr;
            }
            else {
                if(curr->getLeft() == 0) {
                    curr->setLeft(temp);
                }
                else if (curr->getRight() == 0) {
                    curr->setRight(temp);
                }
                root = new OrConnector(curr, 0);
                curr = root;
            }


            it++;
            currArguments.clear();
            expectCommand = true;
        }
        else {
            if (expectCommand) {
                expectCommand = false;
                currArguments.clear();
                currArguments.push_back(*it);
            }
            else {
                currArguments.push_back(*it);
            }
        }
    }
    
    if(!expectCommand) {
        if(curr == 0) {
            curr = new Command(currArguments);
        }
        else {
            curr->setRight(new Command(currArguments));
        }
        if (root == 0) {
            root = curr;
        }
    }
    if(root) {
        if(root->execute() == -1) {
            return false;
        }
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
