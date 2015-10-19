#include "ShowCommand.h"



ShowCommand::ShowCommand(date requestedDate)
{
	_requestedDate = requestedDate;
}


ShowCommand::~ShowCommand()
{
}

void ShowCommand::execute(Storage * data, Display * display)
{
	data->displayByDate(&_requestedEventList, &_requestedTaskList, _requestedDate);

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
