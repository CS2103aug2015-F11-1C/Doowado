#include "DeleteCommand.h"


void DeleteCommand::generateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_DELETE);
	string entryTypeString;
	string indexString;
	string startTimeString;
	string endTimeString;
	string title;

	int displayIndex = _taskID + 1;
	indexString = to_string(displayIndex);

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
	display->setLatestUpdatedEntry(NULL);
	History::pushCommand(this);
}

void DeleteCommand::undo(Storage * data, Display * display)
{
	restoreToStorage(data, display);
	generateUndoFeedback();
	updateDisplay(display, data);
}

void DeleteCommand::restoreToStorage(Storage* data, Display* display) {
	if (event == _entryType) {
		data->addEvent(_eventDeleted);
		display->setLatestUpdatedEntry(_eventDeleted);
	}
	else if (task == _entryType) {
		data->addTask(_taskDeleted);
		display->setLatestUpdatedEntry(_taskDeleted);
	}
}

void DeleteCommand::generateUndoFeedback()
{
	vector<string>::iterator front = _feedback.begin();

	_feedback.insert(front, "Undone");
}

void DeleteCommand::updateDisplay(Display* display, Storage* data)
{
	vector<Entry*> relevantEventList;
	vector<Entry*> relevantTaskList;
	ptime relevantTime;

	relevantTime = getRelevantTime(_entryType);
	data->retrieveByDate(relevantTime, relevantEventList, relevantTaskList);
	
	display->updateDisplayEventList(relevantEventList);
	display->updateDisplayTaskList(relevantTaskList);
	display->updateCommandFeedback(_feedback);
	if (_entryType == event) {
		display->setLatestUpdatedEntry(_eventDeleted);
	}
	else {
		display->setLatestUpdatedEntry(_taskDeleted);
	}

}

ptime DeleteCommand::getRelevantTime(EntryType _entryType) {
	
	ptime relevantTime;
	if (event == _entryType) {
		relevantTime = _eventDeleted->getStartTime();
	}
	else if (task == _entryType) {

		relevantTime = _taskDeleted->getEndTime();
		
		if (relevantTime.is_not_a_date_time()) {
			ptime currentTime(second_clock::local_time());
			relevantTime = currentTime;
		}
	}
	return relevantTime;
}
