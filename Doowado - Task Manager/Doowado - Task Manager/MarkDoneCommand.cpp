#include "MarkDoneCommand.h"

//@@author A0114137R

void MarkDoneCommand::generateFeedback()
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

Entry * MarkDoneCommand::getTaskMarkedDone()
{
	return _taskMarkedDone;
}

void MarkDoneCommand::execute(Storage * date, Display * display)
{
	if (_entryType == event) {
		if (_taskID < 0 || _taskID >= display->getEventList().size()) {
			throw CommandException(EXCEPTION_INDEX_OUT_OF_RANGE);
		}
	}
	else if (_entryType == task) {
		if (_taskID < 0 || _taskID >= display->getTaskList().size()) {
			throw CommandException(EXCEPTION_INDEX_OUT_OF_RANGE);
		}
	}

	Entry* entryToMarkDone = display->retrieveEntry(_entryType, _taskID);
	entryToMarkDone->setDone(true);

	if (_entryType == event) {
		throw CommandException(EXCEPTION_INVALID_MARK_EVENT);
	}
	else if (_entryType == task) {
		_taskMarkedDone = entryToMarkDone;
	}

	generateFeedback();
	display->updateCommandFeedback(_feedback);
	display->setLatestUpdatedEntry(_taskMarkedDone);
}
