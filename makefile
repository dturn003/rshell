CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic

all : rshell

rshell : bin AlwaysConnector AndConnector main Command OrConnector Parser ExitCommand TestCommand WordTestCommand BracketTestCommand
	$(CC) $(CC_FLAGS) src/AlwaysConnector.o src/main.o src/AndConnector.o src/Command.o src/OrConnector.o src/Parser.o src/ExitCommand.o src/TestCommand.o src/BracketTestCommand.o src/WordTestCommand.o -o bin/rshell

AlwaysConnector : src/AlwaysConnector.cpp src/AlwaysConnector.h
	$(CC) $(CC_FLAGS) -c  src/AlwaysConnector.cpp -o src/AlwaysConnector.o

AndConnector : src/AndConnector.cpp src/AndConnector.h
	$(CC) $(CC_FLAGS) -c  src/AndConnector.cpp -o src/AndConnector.o

main : src/main.cpp
	$(CC) $(CC_FLAGS) -c src/main.cpp -o src/main.o

Command : src/Command.cpp src/Command.h
	$(CC) $(CC_FLAGS) -c src/Command.cpp -o src/Command.o

OrConnector : src/OrConnector.cpp src/OrConnector.h
	$(CC) $(CC_FLAGS) -c src/OrConnector.cpp -o src/OrConnector.o
	
Parser : src/Parser.cpp src/Parser.h
	$(CC) $(CC_FLAGS) -c src/Parser.cpp -o src/Parser.o
	
ExitCommand : src/ExitCommand.cpp src/ExitCommand.h
	$(CC) $(CC_FLAGS) -c src/ExitCommand.cpp -o src/ExitCommand.o
	
TestCommand : src/TestCommand.cpp src/TestCommand.h
	$(CC) $(CC_FLAGS) -c src/TestCommand.cpp -o src/TestCommand.o
	
WordTestCommand : src/WordTestCommand.cpp src/WordTestCommand.h
	$(CC) $(CC_FLAGS) -c src/WordTestCommand.cpp -o src/WordTestCommand.o
	
BracketTestCommand : src/BracketTestCommand.cpp src/BracketTestCommand.h
	$(CC) $(CC_FLAGS) -c src/BracketTestCommand.cpp -o src/BracketTestCommand.o

bin :
	mkdir -p  bin

clean:
	rm -rf ./bin
	rm src/*.o
