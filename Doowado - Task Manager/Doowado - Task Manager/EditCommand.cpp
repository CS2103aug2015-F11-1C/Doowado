#include "EditCommand.h"

void EditCommand::generateFeedback(Entry * editedEntry)
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_EDIT);
	_feedback.push_back(editedEntry->getTitle());

	ptime startTime = editedEntry->getStartTime();
	ptime endTime = editedEntry->getEndTime();

	if (!startTime.is_not_a_date_time()) {
		_feedback.push_back(to_simple_string(startTime));
		_feedback.push_back(to_simple_string(endTime));
	}
	else if (!endTime.is_not_a_date_time()) {
		_feedback.push_back(to_simple_string(endTime));
	}
	else {

	}
}

void EditCommand::generateUndoFeedBack(Entry * undoneEntry)
{
	_feedback.clear();
	_feedback.push_back(MESSAGE_SUCCESSFUL_UNDO);
}

void EditCommand::updateDisplay(Display * display, Storage * data, Entry * editedEntry)
{
	std::vector<Entry*> relevantEventList;
	std::vector<Entry*> relevantTaskList;
	
	ptime showTime;
	ptime startTime = editedEntry->getStartTime();
	ptime endTime = editedEntry->getEndTime();
	
	if (!startTime.is_not_a_date_time()) {
		showTime = startTime;
		data->retrieveByDate(showTime, relevantEventList, relevantTaskList);
		display->updateDisplayEventList(relevantEventList);
		display->updateDisplayTaskList(relevantTaskList);
	}

	else if (!endTime.is_not_a_date_time()) {
		showTime = endTime;
		data->retrieveByDate(showTime, relevantEventList, relevantTaskList);
		display->updateDisplayEventList(relevantEventList);
		display->updateDisplayTaskList(relevantTaskList);
	}

	else if (editedEntry == _beforeEditEntry) {			//undo
//		if (!_editedEntry->getEndTime().is_not_a_date_time()) {
			display->deleteEntry(_editedEntry);
			relevantTaskList = display->getTaskList();
			relevantTaskList.push_back(editedEntry);
			display->updateDisplayTaskList(relevantTaskList);
//		}
	}

	else if (editedEntry == _editedEntry) {
//		if (!_beforeEditEntry->getEndTime().is_not_a_date_time()) {
			display->deleteEntry(editedEntry);
			relevantTaskList = display->getTaskList();
			relevantTaskList.push_back(editedEntry);
			display->updateDisplayTaskList(relevantTaskList);
//		}
	}
}

void EditCommand::setBeforeEditEntry(Entry * beforeEditEntry)
{
	string title = beforeEditEntry->getTitle();
	ptime startTime = beforeEditEntry->getStartTime();
	ptime endTime = beforeEditEntry->getEndTime();
	bool isDone = beforeEditEntry->isDone();
	bool isOverdue = beforeEditEntry->isOverdue();

	_beforeEditEntry = new Entry(title, startTime, endTime);
	_beforeEditEntry->setDone(isDone);
	_beforeEditEntry->setOverdue(isOverdue);
}

void EditCommand::setEditedEntry(Entry * editedEntry)
{
	_editedEntry = editedEntry;
}

TypeOfTimeEdit EditCommand::checkTimeEditStart()
{
	TypeOfTimeEdit editType;

	if (_newStartDate.is_neg_infinity() || _newStartTime.is_neg_infinity()) {
		editType = editNullStart;
	}
	else if (!_newStartDate.is_not_a_date()) {
		if (!_newStartTime.is_not_a_date_time()) {
			editType = editStartDateTime;
		}
		else {
			editType = editStartDate;
		}
	}
	else if(!_newStartTime.is_not_a_date_time()) {
		editType = editStartTime;
	}
	else {
		editType = noChangeinStart;
	}
	return editType;
}

TypeOfTimeEdit EditCommand::checkTimeEditEnd()
{
	TypeOfTimeEdit editType;

	if (_newEndDate.is_neg_infinity() || _newEndTime.is_neg_infinity()) {
		editType = editNullEnd;
	}
	else if (!_newEndDate.is_not_a_date()) {
		if (!_newEndTime.is_not_a_date_time()) {
			editType = editEndDateTime;
		}
		else {
			editType = editEndDate;
		}
	}
	else if (!_newEndTime.is_not_a_date_time()) {
		editType = editEndTime;
	}
	else {
		editType = noChangeinEnd;
	}
	return editType;
}

bool EditCommand::isOutOfRangeIndex(EntryType entryType, Display * display)
{
	if (_entryType == event) {
		if (_taskID < INDEX_LOWER_LIMIT || _taskID >= display->getEventList().size()) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (_entryType == task) {
		if (_taskID < INDEX_LOWER_LIMIT || _taskID >= display->getTaskList().size()) {
			return true;
		}
		else {
			return false;
		}
	}
}

void EditCommand::processEditTimeEvent(Storage * data, Display * display, Entry * editedEntry, TypeOfTimeEdit typeEditStart, TypeOfTimeEdit typeEditEnd)
{
	//start time processing
	if (typeEditStart == editNullStart) {
		ptime editedStartTime(not_a_date_time);
		editedEntry->setStartTime(editedStartTime);
		data->addTask(editedEntry);
		data->deleteFromEventList(editedEntry); 
	}
	else if (typeEditStart == editStartDateTime) {
		date newStartDate(_newStartDate);
		time_duration newStartTime(_newStartTime);
		ptime editedStartTime(newStartDate, newStartTime);
		editedEntry->setStartTime(editedStartTime);
	}
	else if (typeEditStart == editStartDate) {
		date newStartDate(_newStartDate);
		time_duration originalStartTime = _beforeEditEntry->getStartTime().time_of_day();

		if (originalStartTime.is_not_a_date_time()) {
			ptime editedStartTime(newStartDate);
			editedEntry->setStartTime(editedStartTime);
		}
		else {
			ptime editedStartTime(newStartDate, originalStartTime);
			editedEntry->setStartTime(editedStartTime);
		}
	}

	else if (typeEditStart == editStartTime) {
		time_duration newStartTime(_newStartTime);
		date originalStartDate = _beforeEditEntry->getStartTime().date();

		if (originalStartDate.is_not_a_date()) {
			//exception
		}
		else {
			ptime editedStartTime(originalStartDate, newStartTime);
			editedEntry->setStartTime(editedStartTime);
		}
	}

	else if (typeEditStart == noChangeinStart) {

	}


	//end time processing
	if (typeEditEnd == editNullEnd) {
		ptime editedEndTime(not_a_date_time);
		editedEntry->setEndTime(editedEndTime);
	}
	else if (typeEditEnd == editEndDateTime) {
		date newEndDate(_newEndDate);
		time_duration newEndTime(_newEndTime);
		ptime editedEndTime(newEndDate, newEndTime);
		editedEntry->setEndTime(editedEndTime);
	}
	else if (typeEditEnd == editEndDate) {
		date newEndDate(_newEndDate);
		time_duration originalEndTime = _beforeEditEntry->getEndTime().time_of_day();

		if (originalEndTime.is_not_a_date_time()) {
			ptime editedEndTime(newEndDate);
			editedEntry->setEndTime(editedEndTime);
		}
		else {
			ptime editedEndTime(newEndDate, originalEndTime);
			editedEntry->setEndTime(editedEndTime);
		}
	}

	else if (typeEditEnd == editEndTime) {
		time_duration newEndTime(_newEndTime);
		date originalEndDate = _beforeEditEntry->getEndTime().date();

		if (originalEndDate.is_not_a_date()) {
			//exception
		}
		else {
			ptime editedEndTime(originalEndDate, newEndTime);
			editedEntry->setEndTime(editedEndTime);
		}
	}

	else if (typeEditEnd == noChangeinEnd) {

	}

}

void EditCommand::processEditTimeTask(Storage * data, Entry * editedEntry, TypeOfTimeEdit typeEditStart, TypeOfTimeEdit typeEditEnd)
{
	if (typeEditStart == editNullStart) {

	}

	else if (typeEditStart == editStartDateTime) {
		date newStartDate(_newStartDate);
		time_duration newStartTime(_newStartTime);
		ptime editedStartTime(newStartDate, newStartTime);
		editedEntry->setStartTime(editedStartTime);
		data->deleteFromTaskLIst(editedEntry);
		data->addEvent(editedEntry);
	}
	else if (typeEditStart == editStartDate) {
		date newStartDate(_newStartDate);
		time_duration originalStartTime = _beforeEditEntry->getStartTime().time_of_day();

		if (originalStartTime.is_not_a_date_time()) {
			ptime editedStartTime(newStartDate);
			editedEntry->setStartTime(editedStartTime);
		}
		else {
			ptime editedStartTime(newStartDate, originalStartTime);
			editedEntry->setStartTime(editedStartTime);
		}
	}

	else if (typeEditStart == editStartTime) {
		//exception
	}
	else if (typeEditStart == noChangeinStart) {

	}

	//EndTime edit
	if (typeEditEnd == editNullEnd) {
		ptime editedEndTime(not_a_date_time);
		editedEntry->setEndTime(editedEndTime);
	}
	else if (typeEditEnd == editEndDateTime) {
		date newEndDate(_newEndDate);
		time_duration newEndTime(_newEndTime);
		ptime editedEndTime(newEndDate, newEndTime);
		editedEntry->setEndTime(editedEndTime);
	}
	else if (typeEditEnd == editEndDate) {
		date newEndDate(_newEndDate);
		time_duration originalEndTime = _beforeEditEntry->getEndTime().time_of_day();
		ptime editedEndTime;

		if (originalEndTime.is_not_a_date_time()) {
			ptime editedEndTime(newEndDate);
			editedEntry->setEndTime(editedEndTime);
		}
		else {
			ptime editedEndTime(newEndDate, originalEndTime);
			editedEntry->setEndTime(editedEndTime);
		}
	}

	else if (typeEditEnd == editEndTime) {
		time_duration newEndTime(_newEndTime);
		date originalEndDate = _beforeEditEntry->getEndTime().date();

		if (originalEndDate.is_not_a_date()) {
			//throw exception;
		}
		else {
			ptime editedEndTime(originalEndDate, newEndTime);
			editedEntry->setEndTime(editedEndTime);
		}
	}
	else if (typeEditEnd == noChangeinEnd) {

	}
}

EditCommand::EditCommand(EntryType entryType, int taskID, string newTitle, date newStartDate, time_duration newStartTime, date newEndDate, time_duration newEndTime)
{
	_entryType = entryType;
	_taskID = taskID;
	_newTitle = newTitle;
	_newStartDate = newStartDate;
	_newStartTime = newStartTime;
	_newEndDate = newEndDate;
	_newEndTime = newEndTime;
	_beforeEditEntry = NULL;
}

EditCommand::~EditCommand()
{
}

void EditCommand::execute(Storage* data, Display *display)
{
	if (isOutOfRangeIndex(_entryType, display)) {
		throw CommandException(EXCEPTION_INDEX_OUT_OF_RANGE);
	}

	Entry* editedEntry = display->retrieveEntry(_entryType, _taskID);
	setBeforeEditEntry(editedEntry);

	if (_newTitle != "") {
		editedEntry->setTitle(_newTitle);
	}

	if (_entryType == event) {
		TypeOfTimeEdit typeEditStart = checkTimeEditStart();
		TypeOfTimeEdit typeEditEnd = checkTimeEditEnd();

		processEditTimeEvent(data, display, editedEntry, typeEditStart, typeEditEnd);
	} 

	else if (_entryType == task) {
		TypeOfTimeEdit typeEditStart = checkTimeEditStart();
		TypeOfTimeEdit typeEditEnd = checkTimeEditEnd();

		processEditTimeTask(data, editedEntry, typeEditStart, typeEditEnd);
	} 
	
	setEditedEntry(editedEntry);
	generateFeedback(editedEntry);
	display->updateCommandFeedback(_feedback);
	updateDisplay(display, data, _editedEntry);
	data->saveToFile();

	History::pushCommand(this);

	return;
}

void EditCommand::undo(Storage * data, Display * display)
{
	string prevTitle = _beforeEditEntry->getTitle();
	ptime prevStartTime = _beforeEditEntry->getStartTime();
	ptime prevEndTime = _beforeEditEntry->getEndTime();
	bool prevIsCompleted = _beforeEditEntry->isDone();
	bool prevIsOverdue = _beforeEditEntry->isOverdue();

	if (_editedEntry->getTitle() != prevTitle) {
		_editedEntry->setTitle(prevTitle);
	}

	if (!_editedEntry->getStartTime().is_not_a_date_time() && prevStartTime.is_not_a_date_time()) {
		data->addTask(_beforeEditEntry);
		data->deleteFromEventList(_editedEntry);
	}
	else if (_editedEntry->getStartTime().is_not_a_date_time() && !prevStartTime.is_not_a_date_time()) {
		data->addEvent(_beforeEditEntry);
		data->deleteFromTaskLIst(_editedEntry);
	}

	generateUndoFeedBack(_beforeEditEntry);
	display->updateCommandFeedback(_feedback);
	updateDisplay(display, data, _beforeEditEntry);
	display->setLatestUpdatedEntry(_beforeEditEntry);
	data->saveToFile();
}
