#include "OutputConnector.h"

#include <string.h>
#include <unistd.h>
#include <fcntl.h>

OutputConnector::OutputConnector(BaseAction* command, string file) {
    this->command = command;
    strcpy(this->file,file.c_str());
}
OutputConnector::~OutputConnector() {
    delete command;
    delete[] file;
}
int OutputConnector::execute() {
    return 1;
}