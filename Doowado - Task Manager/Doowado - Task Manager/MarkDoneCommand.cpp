#include "MarkDoneCommand.h"

void MarkDoneCommand::_generateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_MARK_DONE);
	
	std::string stringIndex;
	if (_entryType = event) {
		stringIndex += "E";
	}
	else if (_entryType = task) {
		stringIndex += "T";
	}
	
	stringIndex += to_string(_taskID + 1);
	_feedback.push_back(stringIndex);
}

MarkDoneCommand::MarkDoneCommand(EntryType entryType, int displayIdx)
{
	_entryType = entryType;
	_taskID = displayIdx;
}

MarkDoneCommand::~MarkDoneCommand()
{
}

EntryType MarkDoneCommand::getEntryType()
{
	return _entryType;
}

int MarkDoneCommand::getIndex()
{
	return _taskID;
}

Entry * MarkDoneCommand::getEventMarkedDone()
{
	return _eventMarkedDone;
}

Entry * MarkDoneCommand::getTaskMarkedDone()
{
	return _taskMarkedDone;
}

void MarkDoneCommand::execute(Storage * date, Display * display)
{
	Entry* entryToMarkDone = display->retrieveEntry(_entryType, _taskID);
	entryToMarkDone->setDone(true);

	if (_entryType == event) {
		//throw exception, not allowed - marked done is only for task
	}
	else if (_entryType == task) {
		_taskMarkedDone = entryToMarkDone;
	}

	_generateFeedback();
	display->updateCommandFeedback(_feedback);
}
