#include "ShowCommand.h"

std::string ShowCommand::generateStatusDisplayState()
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

void ShowCommand::generateDateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_SHOW);
	if (!_requestedStartDate.is_not_a_date()) {
		_feedback.push_back(to_simple_string(_requestedStartDate));
	}
	_feedback.push_back(to_simple_string(_requestedEndDate));
}

void ShowCommand::generateStatusFeedback()
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
		ptime ptimeStartDate;
		ptime ptimeEndDate(_requestedEndDate);
		data->retrieveByDate(ptimeEndDate, _requestedEventList, _requestedTaskList);
		display->updateDisplayEventList(_requestedEventList);
		display->updateDisplayTaskList(_requestedTaskList);
		generateDateFeedback();
		displayEventState = generateDateDisplayState(ptimeStartDate, ptimeEndDate);
		displayTaskState = generateDateDisplayState(ptimeStartDate, ptimeEndDate);
	}
	else if (_showType == showByRangeOfDate) {
		ptime ptimeStartDate(_requestedStartDate);
		ptime ptimeEndDate(_requestedEndDate);
		data->retrieveByDate(ptimeStartDate, ptimeEndDate, _requestedEventList, _requestedTaskList);
		display->updateDisplayEventList(_requestedEventList);
		display->updateDisplayTaskList(_requestedTaskList);
		generateDateFeedback();
		displayEventState = generateDateDisplayState(ptimeStartDate, ptimeEndDate);
		displayTaskState = generateDateDisplayState(ptimeStartDate, ptimeEndDate);
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
		generateStatusFeedback();
		displayTaskState = generateStatusDisplayState();
		display->updateDisplayTaskList(_requestedTaskList);
	}

	display->updateCommandFeedback(_feedback);
	display->setEventDisplayState(displayEventState);
	display->setTaskDisplayState(displayTaskState);
	display->setLatestUpdatedEntry(NULL);
}
