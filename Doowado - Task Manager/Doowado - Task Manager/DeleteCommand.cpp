#include "DeleteCommand.h"


DeleteCommand::DeleteCommand(EntryType entryType, int displayIndex) {
	_entryType = entryType;
	_taskID = displayIndex;
}


DeleteCommand::~DeleteCommand()
{
}

void DeleteCommand::execute(Storage* data, Display* display) {
	//delete command
	if (_entryType = event) {
		Event* event = display->retrieveEvent(_taskID);
		data->deleteFromEventList(event);
	}
	else if (_entryType = task) {
		Task* task = display->retrieveTask(_taskID);
		data->deleteFromTaskLIst(task);
	}
}
