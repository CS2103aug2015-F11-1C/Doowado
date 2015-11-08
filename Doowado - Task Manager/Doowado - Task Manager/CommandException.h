#pragma once
#include <string>

const std::string EXCEPTION_INDEX_OUT_OF_RANGE = "Invalid index: out-of-range.";

class CommandException
{
private:
	std::string _message;
public:
	CommandException(std::string message);
	std::string getMessage();
	~CommandException();
};

