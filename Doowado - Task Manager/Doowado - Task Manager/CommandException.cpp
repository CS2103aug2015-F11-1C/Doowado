#include "CommandException.h"



CommandException::CommandException(std::string message)
{
	_message = message;
}

std::string CommandException::getMessage()
{
	return _message;
}


CommandException::~CommandException()
{
}
