# Rshell
  Rshell is a program that takes in bash commands and executes them on a single line. To connect each command, the following connectors are implemented: ; , && , ||. ; always executes the next command. && executes the next command only if the first command succeeded, and || executes the next command only if the first command failed. In addition, the comment functionality is also present with #. The program is designed to loop until the user inputs the command "exit", outputting the result of each successful command executed, and printing out an error for each command that failed. In the case of a user input error, the parser outputs the token nearest to the error and does not read in any commands.

## Compiling:
  Rshell includes a fully functional makefile that is run with the command "make". It outputs the executable *rshell* to the created folder bin.

## Known Bugs:
  - Ctrl-c does not work as expected with rshell.
  - Using the arrow keys does not work on rshell.
  - Placing empty parentheses [ex: () echo a] will still allow the command to run afterwards.
  - Placing commands after an input redirection is not checked for, which may lead to errors parsing.
