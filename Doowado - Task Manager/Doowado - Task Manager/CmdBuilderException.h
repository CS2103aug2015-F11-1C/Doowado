#pragma once
#include <exception>
#include <string>

class CmdBuilderException
{
private:
	std::string _message;
public:
	CmdBuilderException(std::string message);
	std::string getMessage();
	~CmdBuilderException();
};

