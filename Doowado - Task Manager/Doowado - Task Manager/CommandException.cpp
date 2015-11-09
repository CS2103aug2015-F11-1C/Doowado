#include "CommandException.h"

//@@author A0114137R

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
