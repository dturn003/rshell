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
            
        if(!filter.parse(input)) {
            exit = true;
        }
    }
   
    return 0;
}
