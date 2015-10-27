#include "EditCommand.h"

EditCommand::EditCommand(EntryType entryType, int taskID, string newTitle, ptime newStartDate, ptime newStartTime, ptime newEndDate, ptime newEndTime)
{
	_entryType = entryType;
	_taskID = taskID;
	_newTitle = newTitle;
	_newStartDate = newStartDate;
	_newStartTime = newStartTime;
	_newEndDate = newEndDate;
	_newEndTime = newEndTime;
}

EditCommand::~EditCommand()
{
}

void EditCommand::execute(Storage* data, Display *display)
{
	if (_entryType == event) {
		Event* eventEntry = display->retrieveEvent(_taskID);
		
		if (_newTitle != "") {
			eventEntry->setTitle(_newTitle);
		}
		if (!_newStartDate.is_not_a_date_time()) {
			date startDate = _newStartDate.date();
			if (!_newStartTime.is_not_a_date_time()) {
				time_duration startTime = _newStartTime.time_of_day();
				ptime editStartTime(startDate, startTime);
				eventEntry->setStartTime(editStartTime);
			}
			else {
				ptime originalStartTime = eventEntry->getStartTime();
				time_duration startTime = originalStartTime.time_of_day();
				ptime editStartTime(startDate, startTime);
				eventEntry->setStartTime(editStartTime);
			}
		}
		else if (!_newStartTime.is_not_a_date_time()) {
			time_duration startTime = _newStartTime.time_of_day();
			ptime originalStartDate = eventEntry->getStartTime();
			date startDate = originalStartDate.date();
			ptime editStartTime(startDate, startTime);
			eventEntry->setStartTime(editStartTime);
		}
		
		if (!_newEndDate.is_not_a_date_time()) {
			date endDate = _newEndDate.date();
			if (!_newEndTime.is_not_a_date_time()) {
				time_duration endTime = _newEndTime.time_of_day();
				ptime editEndTime(endDate, endTime);
				eventEntry->setEndTime(editEndTime);
			}
			else {
				ptime originalEndTime = eventEntry->getEndTime();
				time_duration endTime = originalEndTime.time_of_day();
				ptime editEndTime(endDate, endTime);
				eventEntry->setEndTime(editEndTime);
			}
		}
		else if (!_newEndTime.is_not_a_date_time()) {
			time_duration endTime = _newEndTime.time_of_day();
			ptime originalEndDate = eventEntry->getEndTime();
			date endDate = originalEndDate.date();
			ptime editEndTime(endDate, endTime);
			eventEntry->setEndTime(editEndTime);
		}
		
	}

	else if (_entryType == task) {
		Task* taskEntry = display->retrieveTask(_taskID);
		if (_newTitle != "") {
			taskEntry->setTitle(_newTitle);
		}
		if (!_newEndDate.is_not_a_date_time()) {
			date dueDate = _newEndDate.date();
			if (!_newEndTime.is_not_a_date_time()) {
				time_duration dueTime = _newEndTime.time_of_day();
				ptime editDueTime(dueDate, dueTime);
				taskEntry->setDueTime(editDueTime);
			}
			else {
				ptime originalDueTime = taskEntry->getDueTime();
				time_duration dueTime = originalDueTime.time_of_day();
				ptime editDueTime(dueDate, dueTime);
				taskEntry->setDueTime(editDueTime);
			}
		}
		else if (!_newEndTime.is_not_a_date_time()) {
			time_duration dueTime = _newEndTime.time_of_day();
			ptime originalDueDate = taskEntry->getDueTime();
			date dueDate = originalDueDate.date();
			ptime editDueTime(dueDate, dueTime);
			taskEntry->setDueTime(editDueTime);
		}
	}

	return;
}
