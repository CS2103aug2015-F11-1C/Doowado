#include "EditCommand.h"

void EditCommand::_generateFeedback(Entry * editedEntry)
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

void EditCommand::_updateDisplay(Display * display, Storage * data, Entry * editedEntry)
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
	else {
		display->deleteEntry(_entryType, _taskID);
		relevantTaskList = display->getTaskList();
		relevantTaskList.push_back(editedEntry);
		display->updateDisplayTaskList(relevantTaskList);
	}

}

void EditCommand::_setBeforeEditEntry(Entry * editEntry)
{
	string title = editEntry->getTitle();
	ptime startTime = editEntry->getStartTime();
	ptime endTime = editEntry->getEndTime();
	bool isDone = editEntry->isDone();
	bool isOverdue = editEntry->isOverdue();

	_beforeEditEntry = new Entry(title, startTime, endTime);
	_beforeEditEntry->setDone(isDone);
	_beforeEditEntry->setOverdue(isOverdue);
}

TypeOfTimeEdit EditCommand::_checkTimeEditStart()
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

TypeOfTimeEdit EditCommand::_checkTimeEditEnd()
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
	Entry* editedEntry = display->retrieveEntry(_entryType, _taskID);
	_setBeforeEditEntry(editedEntry);

	if (_newTitle != "") {
		editedEntry->setTitle(_newTitle);
	}
	if (_entryType == event) {
		TypeOfTimeEdit typeEditStart = _checkTimeEditStart();
		TypeOfTimeEdit typeEditEnd = _checkTimeEditEnd();

		//startTime edit
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
			ptime editedStartTime(newStartDate, originalStartTime);
			editedEntry->setStartTime(editedStartTime);
		}

		else if (typeEditStart == editStartTime) {
			time_duration newStartTime(_newStartTime);
			date originalStartDate = _beforeEditEntry->getStartTime().date();
			ptime editedStartTime(originalStartDate, newStartTime);
			editedEntry->setStartTime(editedStartTime);
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
			ptime editedEndTime(newEndDate, originalEndTime);
			editedEntry->setEndTime(editedEndTime);
		}

		else if (typeEditEnd == editEndTime) {
			time_duration newEndTime(_newEndTime);
			date originalEndDate = _beforeEditEntry->getEndTime().date();
			ptime editedEndTime(originalEndDate, newEndTime);
			editedEntry->setEndTime(editedEndTime);
		}
		else if (typeEditEnd == noChangeinEnd) {

		}
		
	} 

	else if (_entryType == task) {
		//throw exception if it is a floating task and newStartTime and newStartDate are ! is_special 
		if (!_newStartTime.is_special()) {		//got new startTime
			if (!_newStartDate.is_special()) {	//got new startDate
				ptime editedStartTime(_newStartDate, _newStartTime);
				editedEntry->setStartTime(editedStartTime);
				data->addEvent(editedEntry);
				data->deleteFromTaskLIst(editedEntry);
			}
			else {						//got no new startDate
				//throw exception
			}
		}
		else {			//no startTime
			if (!_newStartDate.is_special()) {		//new startDate
				time_duration startTime(not_a_date_time);
				ptime editedStartTime(_newStartDate, startTime);
				editedEntry->setStartTime(editedStartTime);
				data->addEvent(editedEntry);
				data->deleteFromTaskLIst(editedEntry);
			}
		}

		if (!_newEndDate.is_special()) {		//new endDate
			if (!_newEndTime.is_special()) {	//new endTime
				ptime editedEndTime(_newEndDate, _newEndTime);
				editedEntry->setEndTime(editedEndTime);
			}
			else if (_newEndTime.is_not_a_date_time()) {	//no change in endTime
				ptime endTime = editedEntry->getEndTime();
				time_duration originalEndTime = endTime.time_of_day();
				ptime editedEndTime(_newEndDate, originalEndTime);
				editedEntry->setEndTime(editedEndTime);
			}
		}
		else if (_newEndDate.is_neg_infinity() || _newEndDate.is_neg_infinity()) {
			date endDate(not_a_date_time);
			time_duration endTime(not_a_date_time);
			ptime editedEndTime(endDate, endTime);
			editedEntry->setEndTime(editedEndTime);
		}
	} 
	
	_generateFeedback(editedEntry);
	display->updateCommandFeedback(_feedback);
	_updateDisplay(display, data, editedEntry);
	data->saveToFile();
	return;
}
