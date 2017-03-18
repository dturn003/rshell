#include "InputConnector.h"

InputConnector::InputConnector(BaseAction* command, string file) {
    this->command = command;
    this->file = file.c_str();
}
InputConnector::~InputConnector() {
    delete command;
    delete[] file;
}
int InputConnector::execute() {
    
}