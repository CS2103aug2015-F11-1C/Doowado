#include "DeleteCommand.h"



DeleteCommand::DeleteCommand(int displayIndex) {
	_taskID = displayIndex;
}


DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::execute(Storage* data, Display* display) {
	//delete command
}
