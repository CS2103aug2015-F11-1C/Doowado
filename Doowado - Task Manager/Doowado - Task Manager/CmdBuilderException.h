#pragma once
#include <exception>
#include <string>

const std::string EXCEPTION_INVALID_COMMANDTYPE = "Invalid command type. Please insert add/edit/delete/search/show/help/save/done/undo";
const std::string EXCEPTION_START_TIME_GREATER_END_TIME = "Invalid! Start Time is later than End Time.";
const std::string EXCEPTION_TIME_NO_DATE = "Invalid! Entry has time with no date.";
const std::string EXCEPTION_NO_TITLE = "Invalid! Entry has no title";
const std::string EXCEPTION_INVALID_ENTRY_TYPE_AT_INDEX = "Invalid entry type at index!";
const std::string EXCEPTION_INVALID_DELETE = "Invalid input for delete command!";
const std::string EXCEPTION_INVALID_SEARCH = "Invalid input for search command!";
const std::string EXCEPTION_INVALID_SHOW = "Invalid input for show command!";
const std::string EXCEPTION_INVALID_SHOW_STATUS = "Invalid input for show status!";
const std::string EXCEPTION_INVALID_TIME = "Invalid time input!";
const std::string EXCEPTION_INVALID_SAVE = "Invalid input for save command!";
const std::string EXCEPTION_INVALID_MARKDONE = "Invalid input for mark done command!";

class CmdBuilderException
{
private:
	std::string _message;
public:
	CmdBuilderException(std::string message);
	std::string getMessage();
	~CmdBuilderException();
};

