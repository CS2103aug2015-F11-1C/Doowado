#include "ShowCommand.h"

std::string ShowCommand::_generateDateDisplayState()
{ 
	std::string displayState;

	int endDay = _requestedEndDate.day();
	int endMonth = _requestedEndDate.month();
	int endYear = _requestedEndDate.year();
	int intEndDayOfWeek = _requestedEndDate.day_of_week();
	std::string endDayOfWeek;
	
	switch (intEndDayOfWeek)
	{
		case 0:
			endDayOfWeek = "Sunday";
			break;
		case 1:
			endDayOfWeek = "Monday";
			break;
		case 2:
			endDayOfWeek = "Tuesday";
			break;
		case 3:
			endDayOfWeek = "Wednesday";
			break;
		case 4:
			endDayOfWeek = "Thursday";
			break;
		case 5:
			endDayOfWeek = "Friday";
			break;
		case 6:
			endDayOfWeek = "Saturday";
			break;
		default:
			break;
	}

	displayState = endDayOfWeek + ", " + to_string(endDay) + "/" + to_string(endMonth) + "/" + to_string(endYear);

	if (!_requestedStartDate.is_not_a_date()) {
		int startDay = _requestedStartDate.day();
		int startMonth = _requestedStartDate.month();
		int startYear = _requestedStartDate.year();
		int intStartDayOfWeek = _requestedStartDate.day_of_week();
		
		std::string startDayOfWeek;
		
		switch (intStartDayOfWeek)
		{
		case 0:
			startDayOfWeek = "Sunday";
			break;
		case 1:
			startDayOfWeek = "Monday";
			break;
		case 2:
			startDayOfWeek = "Tuesday";
			break;
		case 3:
			startDayOfWeek = "Wednesday";
			break;
		case 4:
			startDayOfWeek = "Thursday";
			break;
		case 5:
			startDayOfWeek = "Friday";
			break;
		case 6:
			startDayOfWeek = "Saturday";
			break;
		default:
			break;
		}

		displayState += " - " + startDayOfWeek + ", " + to_string(startDay) + "/" + to_string(startMonth) + "/" + to_string(startYear);
	}
	
	return displayState;
}

std::string ShowCommand::_generateStatusDisplayState()
{
	std::string taskDisplayState;

	if (_entryStatus == completed) {
		taskDisplayState = ENTRY_STATUS_COMPLETED;
	}
	else if (_entryStatus == incomplete) {
		taskDisplayState = ENTRY_STATUS_INCOMPLETE;
	}
	else if (_entryStatus == overdue) {
		taskDisplayState = ENTRY_STATUS_OVERDUE;
	}
	else if (_entryStatus == intime) {
		taskDisplayState = ENTRY_STATUS_INTIME;
	}

	return taskDisplayState;

}

void ShowCommand::_generateDateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_SHOW);
	if (!_requestedStartDate.is_not_a_date()) {
		_feedback.push_back(to_simple_string(_requestedStartDate));
	}
	_feedback.push_back(to_simple_string(_requestedEndDate));
}

void ShowCommand::_generateStatusFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_SHOW);

	if (_entryStatus == completed) {
		_feedback.push_back(ENTRY_STATUS_COMPLETED);
	}
	else if (_entryStatus == incomplete) {
		_feedback.push_back(ENTRY_STATUS_INCOMPLETE);
	}
	else if (_entryStatus == overdue) {
		_feedback.push_back(ENTRY_STATUS_OVERDUE);
	}
	else if (_entryStatus == intime) {
		_feedback.push_back(ENTRY_STATUS_INTIME);
	}
}

ShowCommand::ShowCommand(date endDate)
{
	_requestedEndDate = endDate;
	_showType = showByDate;
}

ShowCommand::ShowCommand(date startDate, date endDate)
{
	_requestedStartDate = startDate;
	_requestedEndDate = endDate;
	_showType = showByRangeOfDate;
}

ShowCommand::ShowCommand(entryStatus status)
{
	_entryStatus = status;
	_showType = showByStatus;
}

ShowCommand::~ShowCommand()
{
}

void ShowCommand::execute(Storage * data, Display * display)
{
	std::string displayEventState;
	std::string displayTaskState;

	if (_showType == showByDate) {
		ptime ptimeEndDate(_requestedEndDate);
		data->retrieveByDate(ptimeEndDate, _requestedEventList, _requestedTaskList);
		display->updateDisplayEventList(_requestedEventList);
		display->updateDisplayTaskList(_requestedTaskList);
		_generateDateFeedback();
		displayEventState = _generateDateDisplayState();
		displayTaskState = _generateDateDisplayState();
	}
	else if (_showType == showByRangeOfDate) {
		ptime ptimeStartDate(_requestedStartDate);
		ptime ptimeEndDate(_requestedEndDate);
		data->retrieveByDate(ptimeStartDate, ptimeEndDate, _requestedEventList, _requestedTaskList);
		display->updateDisplayEventList(_requestedEventList);
		display->updateDisplayTaskList(_requestedTaskList);
		_generateDateFeedback();
		displayEventState = _generateDateDisplayState();
		displayTaskState = _generateDateDisplayState();
	}
	else if (_showType == showByStatus) {
		if (_entryStatus == completed) {
			_requestedTaskList = data->retrieveTaskByDone(true);
		}
		else if (_entryStatus == incomplete) {
			_requestedTaskList = data->retrieveTaskByDone(false);
		}
		else if (_entryStatus == overdue) {
			_requestedTaskList = data->retrieveTaskByOverdue(true);
		}
		else if (_entryStatus == intime) {
			_requestedTaskList = data->retrieveTaskByOverdue(false);
		}
		_generateStatusFeedback();
		displayTaskState = _generateStatusDisplayState();
		display->updateDisplayTaskList(_requestedTaskList);
	}

	display->updateCommandFeedback(_feedback);
	display->setEventDisplayState(displayEventState);
	display->setTaskDisplayState(displayTaskState);
}
