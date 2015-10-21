#include "EditCommand.h"

EditCommand::EditCommand(string entryType, int displayIndex, string newTitle, ptime newStartTime, ptime newEndTime, ptime newDueTime)
{
	string _entryType = entryType;
	int _taskId = displayIndex;
	string _newTitle = newTitle;
	ptime _newStartTime = newStartTime;
	ptime _newEndTime = newEndTime;
	ptime _newDueTime = newDueTime;
}


EditCommand::~EditCommand()
{
}

void EditCommand::execute(Storage* data, Display *display)
{
	if (_entryType == eventType) {
		Event* eventEntry = display->retrieveEvent(_taskID);
		eventEntry->setName(_newTitle);
	}

	else if (_entryType == taskType) {
		Task* taskEntry = display->retrieveTask(_taskID);
		taskEntry->setName(_newTitle);
	}

	return;
}
