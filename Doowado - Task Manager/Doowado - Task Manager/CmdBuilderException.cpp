#include "CmdBuilderException.h"

//@@author A0114137R

CmdBuilderException::CmdBuilderException(std::string message)
{
	_message = message;
}

std::string CmdBuilderException::getMessage()
{
	return _message;
}


CmdBuilderException::~CmdBuilderException()
{
}
