#pragma once
#include <exception>
#include <string>

//@@author A0114137R

class CmdBuilderException
{
private:
	std::string _message;
public:
	CmdBuilderException(std::string message);
	std::string getMessage();
	~CmdBuilderException();
};

