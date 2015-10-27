#include "ShowCommand.h"

ShowCommand::ShowCommand(ptime requestedDate)
{
	_requestedDate = requestedDate;
}


ShowCommand::~ShowCommand()
{
}

void ShowCommand::execute(Storage * data, Display * display)
{
	data->retrieveByDate(_requestedDate, _requestedEventList, _requestedTaskList);

	display->updateDisplayEventList(_requestedEventList);
	display->updateDisplayTaskList(_requestedTaskList);

	generateFeedback();
	display->updateCommandFeedback(_feedback);
}

void ShowCommand::generateFeedback()
{
	_feedback.push_back("Showing");
	_feedback.push_back(to_simple_string(_requestedDate));
}
