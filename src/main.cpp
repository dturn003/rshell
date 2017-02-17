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


void parse(const string &input) {
    
    BaseAction* root = 0;
    BaseAction* curr = root;
    
    vector<string> currArguments; //vector of argument list
    bool expectCommand = true; //flag to expect next command
    
    typedef tokenizer<char_separator<char > > Tok; //defines tokenizer object
    char_separator<char> sep(" ", ";&|#"); //splits up string input into tokens of connector and commands/arguments
    Tok tokens(input, sep); //list of tokens
    
     for (Tok::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        if (it->at(0) == ';') {
            BaseAction* left = new Command(currArguments);
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

            currArguments.clear();
            expectCommand = true;
        }
        else if (it->at(0) == '#') {
            break;
        }
        else if (it->at(0) == '&') {
            BaseAction* left = new Command(currArguments);
            
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
            currArguments.clear();
            expectCommand = true;
        }
        else if (it->at(0) == '|') {
            BaseAction* left = new Command(currArguments);

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
        root->execute();
    }
}

int main() {
    
    char* username = getlogin();
    if(username) {
        perror("getlogin() error");
    }
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname))) {
        perror("gethostname() error");
    }
    
    while(1) {
        cout << username << "@" << hostname << "$ ";
        string input;
        getline(cin, input);
    
        if (input == "exit")
            return 0;
            
        parse(input);
    }
   
    return 0;
}
