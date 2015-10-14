#include "EditTitleCommand.h"


EditTitleCommand::EditTitleCommand(string entryType, int displayIndex, string newTitle)
{
	string _entryType = entryType;
	int _taskId = displayIndex;
	string _newTitle = newTitle;
}


EditTitleCommand::~EditTitleCommand()
{
}

void EditTitleCommand::execute(Storage* data, Display *display)
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
