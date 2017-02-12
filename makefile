CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic

all : rshell

rshell : bin AlwaysConnector AndConnector main Command OrConnector
	$(CC) $(CC_FLAGS) src/AlwaysConnector.o src/main.o src/AndConnector.o src/Command.o src/OrConnector.o -o bin/rshell

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

bin :
	mkdir -p  bin

clean:
	rm -rf ./bin
	rm src/*.o
