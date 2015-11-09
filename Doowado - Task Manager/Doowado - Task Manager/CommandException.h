#pragma once
#include <string>

const std::string EXCEPTION_INDEX_OUT_OF_RANGE = "Invalid index: out-of-range.";
const std::string EXCEPTION_TIME_WITH_NO_DATE = "Invalid! Entry has time with no date.";
const std::string EXCEPTION_EVENT_NO_END_TIME = "Invalid! Your event must have an end date.";

class CommandException
{
private:
	std::string _message;
public:
	CommandException(std::string message);
	std::string getMessage();
	~CommandException();
};

