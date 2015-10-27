#include "EditTimeCommand.h"


EditTimeCommand::EditTimeCommand(string entryType, int displayIndex, ptime newStartTime, ptime newEndTime) {
	_entryType = entryType;
	_taskID = displayIndex;
	_newStartTime = newStartTime;
	_newEndTime = newEndTime;
}


EditTimeCommand::~EditTimeCommand()
{
}

void EditTimeCommand::execute(Storage* data, Display *display) {
	if (_entryType == "e") {
		Event* eventEntry = display->retrieveEvent(_taskID);
		eventEntry->setStartTime(_newStartTime);
		eventEntry->setEndTime(_newEndTime);
	}
	/*
	else if (_entryType == taskType) {
		Task* taskEntry = display->retrieveTask(_taskID);
		taskEntry->setTitle(_newTitle);
	}
	*/
}
