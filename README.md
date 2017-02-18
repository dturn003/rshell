# rshell
rshell is a program that takes in bash commands and executes them. It implements the following connectors: ;, &&, ||. It also implements the comment functionality with the symbol #.
The program is designed to loop until the user inputs the command "exit", outputing username and hostname and then taking in a line of input at a time and then exicuting the bash commands inputed.

## Compiling:
  rshell includes a fully functional makefile that is run with the command make. It outputs the executable *rshell* to the created folder bin.

## Known Bugs:
  - Ctrl-c does not work as expected with rshell
  - using the arrow keys does not work on rshell
  - rshell currently does not do anything with bad input other than mark that command as having failed to run
  - combining connectors together, && ||, will run
  - placing a connector in front of the command will allow the command to run. The parser treats the connector as having an empty command       on the left subchild.
  - 
