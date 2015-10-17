#include "ShowCommand.h"



ShowCommand::ShowCommand()
{
}


ShowCommand::~ShowCommand()
{
}

void ShowCommand::execute(Storage * data, Display * display)
{
	data->displayByDate(_requestedEventList, _requestedTaskList, _requestedDate);
}
