#include "OutputConnector.h"

OutputConnector::OutputConnector(BaseAction* command, string file) {
    this->command = command;
    this->file = file.c_str();
}
OutputConnector::~OutputConnector() {
    delete command;
    delete[] file;
}
int OutputConnector::execute() {
    
}