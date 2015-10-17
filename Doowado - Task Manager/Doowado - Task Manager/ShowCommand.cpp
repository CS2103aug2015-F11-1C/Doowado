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
}
