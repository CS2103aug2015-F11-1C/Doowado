#include "DeleteCommand.h"


void DeleteCommand::generateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_DELETE);
	string entryTypeString;
	string indexString;
	string startTimeString;
	string endTimeString;
	string title;

	indexString = to_string(_taskID);

	if (_entryType == event) {
		entryTypeString = "E";
		title = _eventDeleted->getTitle();
		startTimeString = to_simple_string(_eventDeleted->getStartTime());
		endTimeString = to_simple_string(_eventDeleted->getEndTime());

		_feedback.push_back(entryTypeString + indexString);
		_feedback.push_back(title);
		_feedback.push_back(startTimeString);
		_feedback.push_back(endTimeString);
	}
	else if (_entryType == task) {
		entryTypeString = "T";
		title = _taskDeleted->getTitle();
		endTimeString = to_simple_string(_taskDeleted->getEndTime());

		_feedback.push_back(entryTypeString + indexString);
		_feedback.push_back(title);
		_feedback.push_back(endTimeString);
	}
	
}

DeleteCommand::DeleteCommand(EntryType entryType, int displayIndex) {
	_entryType = entryType;
	_taskID = displayIndex;
}


DeleteCommand::~DeleteCommand()
{
}

EntryType DeleteCommand::getEntryType()
{
	return _entryType;
}

int DeleteCommand::getIndex()
{
	return _taskID;
}

void DeleteCommand::execute(Storage* data, Display* display) {
	//delete command

	Entry* entryToDelete = display->retrieveEntry(_entryType, _taskID);

	if (_entryType == event) {
		_eventDeleted = entryToDelete;
		data->deleteFromEventList(_eventDeleted);
		display->deleteEntry(_entryType, _taskID);
	}
	else if (_entryType == task) {
		_taskDeleted = entryToDelete;
		data->deleteFromTaskLIst(_taskDeleted);
		display->deleteEntry(_entryType, _taskID);
	}

	generateFeedback();
	display->updateCommandFeedback(_feedback);

	History::pushCommand(this);
}

void DeleteCommand::undo(Storage * data, Display * display)
{
	data->addEvent(_eventDeleted);
	generateUndoFeedback();
	display->updateCommandFeedback(_feedback);
}

void DeleteCommand::generateUndoFeedback()
{
	vector<string>::iterator front = _feedback.begin();

	_feedback.insert(front, "Undone");
}
