#include "CmdBuilderException.h"



CmdBuilderException::CmdBuilderException(std::string message)
{
	_message = message;
}

inline std::string CmdBuilderException::getMessage()
{
	return _message;
}


CmdBuilderException::~CmdBuilderException()
{
}
