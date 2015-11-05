#include "EditCommand.h"

EditCommand::EditCommand(EntryType entryType, int taskID, string newTitle, date newStartDate, time_duration newStartTime, date newEndDate, time_duration newEndTime)
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
	Entry* editedEntry = display->retrieveEntry(_entryType, _taskID);
	if (_newTitle != "") {
		editedEntry->setTitle(_newTitle);
	}
	if (_entryType == event) {
		//throw exception if StartDate/StartTime is not neg infin but EndDate/EndTime is neg inifin
		if (_newEndDate.is_neg_infinity() || _newEndTime.is_neg_infinity()) {
			/*if (!_newStartDate.is_neg_infinity() || !_newStartTime.is_neg_infinity()) {
				//throw exception
			}*/
			ptime editedStartTime(not_a_date_time);
			ptime editedEndTime(not_a_date_time);

			editedEntry->setStartTime(editedStartTime);
			editedEntry->setEndTime(editedEndTime);
			data->addTask(editedEntry);
			data->deleteFromEventList(editedEntry);
		}
		else if (_newStartDate.is_neg_infinity() || _newStartTime.is_neg_infinity()) {
			ptime editedStartTime(not_a_date_time);
			editedEntry->setStartTime(editedStartTime);
			data->addTask(editedEntry);
			data->deleteFromEventList(editedEntry);
		}

		if (!_newStartDate.is_special()) {
			if (!_newStartTime.is_special()) {
				ptime editedStartTime(_newStartDate, _newStartTime);
				editedEntry->setStartTime(editedStartTime);
			}
			else if (_newStartTime.is_not_a_date_time()) {
				ptime startTime = editedEntry->getStartTime();
				time_duration originalStartTime = startTime.time_of_day();
				ptime editedStartTime(_newStartDate, originalStartTime);
				editedEntry->setStartTime(editedStartTime);
			}
		}
		else if (_newStartDate.is_not_a_date()) {		//no change in StartDate
			if (!_newStartTime.is_not_a_date_time()) {	//there is change in StartTime
				ptime endTime = editedEntry->getEndTime();	
				date originalStartDate = endTime.date();	//retrieve oristartDate
				ptime editedStartTime(originalStartDate, _newStartTime);	//oristartDate and newStartTime
				editedEntry->setStartTime(editedStartTime);
			}
		}

		if (!_newEndDate.is_special()) {
			if (!_newEndTime.is_special()) {
				ptime editedEndTime(_newEndDate, _newEndTime);
				editedEntry->setEndTime(editedEndTime);
			}
			else if (_newEndTime.is_not_a_date_time()) {
				ptime endTime = editedEntry->getEndTime();
				time_duration originalEndTime = endTime.time_of_day();
				ptime editedEndTime(_newEndDate, originalEndTime);
				editedEntry->setEndTime(editedEndTime);
			}
		}
		
		else if (_newStartDate.is_not_a_date()) {		//no change in StartDate
			if (!_newStartTime.is_not_a_date_time()) {	//there is change in StartTime
				ptime endTime = editedEntry->getEndTime();
				date originalStartDate = endTime.date();	//retrieve oristartDate
				ptime editedStartTime(originalStartDate, _newStartTime);	//oristartDate and newStartTime
				editedEntry->setStartTime(editedStartTime);
			}
		}
		
	}

	else if (_entryType == task) {
		//throw exception if it is a floating task and newStartTime and newStartDate are ! is_special 
		if (!_newStartTime.is_special()) {
			if (!_newStartDate.is_special()) {
				ptime editedStartTime(_newStartDate, _newStartTime);
				editedEntry->setStartTime(editedStartTime);
				data->addEvent(editedEntry);
				data->deleteFromTaskLIst(editedEntry);
			}
			else {
				//throw exception
			}
		}
		else {
			if (!_newStartDate.is_special()) {
				time_duration startTime(not_a_date_time);
				ptime editedStartTime(_newStartDate, startTime);
				editedEntry->setStartTime(editedStartTime);
				data->addEvent(editedEntry);
				data->deleteFromTaskLIst(editedEntry);
			}
		}

		if (!_newEndDate.is_special()) {
			if (!_newEndTime.is_special()) {
				ptime editedEndTime(_newEndDate, _newEndTime);
				editedEntry->setEndTime(editedEndTime);
			}
			else if (_newEndTime.is_not_a_date_time()) {
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

	return;
}
