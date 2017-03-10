#include <iostream>
#include "Parser.h"
#include <unistd.h>

using namespace std;

int main() {
    
    char* username = getlogin();
    if(!username) {
        perror("getlogin() error");
    }
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname))) {
        perror("gethostname() error");
    }
    
    Parser filter;
    
    bool exit = false; 
    while(!exit) {
        cout << username << "@" << hostname << "$ ";
        string input;
        getline(cin, input);
            
        BaseAction* syntaxTree = filter.parse(input);
        if (syntaxTree) {
            exit = syntaxTree->execute();
            delete syntaxTree;
        }
    }
   
    return 0;
}
