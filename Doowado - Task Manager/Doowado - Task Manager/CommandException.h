#pragma once
#include <string>

//@@author A0114137R

const std::string EXCEPTION_INDEX_OUT_OF_RANGE = "Invalid index: out-of-range.";
const std::string EXCEPTION_TIME_WITH_NO_DATE = "Invalid! Entry has time with no date.";
const std::string EXCEPTION_EVENT_NO_END_TIME = "Invalid! Your event must have an end date.";
const std::string EXCEPTION_INVALID_MARK_EVENT = "Invalid! Event cannot be marked as done.";

class CommandException
{
private:
	std::string _message;
public:
	CommandException(std::string message);
	std::string getMessage();
	~CommandException();
};

