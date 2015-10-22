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
			eventEntry->setName(_newTitle);
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
		/*
		if (!_newEndDate.is_not_a_date_time()) {
			date endDate = _newEndDate.date();
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
		*/
	}

	else if (_entryType == task) {
		Task* taskEntry = display->retrieveTask(_taskID);
		taskEntry->setName(_newTitle);
	}

	return;
}
