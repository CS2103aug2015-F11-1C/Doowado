#pragma once
#include "Command.h"

const string ENTRY_STATUS_COMPLETED = "completed";
const string ENTRY_STATUS_INCOMPLETE = "incomplete";
const string ENTRY_STATUS_OVERDUE = "overdue";
const string ENTRY_STATUS_INTIME = "intime";
const string MESSAGE_SUCCESSFUL_SHOW = "Showing: "; 

enum showType {showByDate, showByRangeOfDate, showByStatus};

class ShowCommand : public Command
{
#ifndef TESTMODE
private:
#else 
public: 
#endif
	std::vector<Entry*> _requestedEventList;
	std::vector<Entry*> _requestedTaskList;

	date _requestedStartDate;
	date _requestedEndDate;
	entryStatus _entryStatus;
	showType _showType;
	std::vector<std::string> _feedback;

	std::string _generateDateDisplayState();
	std::string _generateStatusDisplayState();
	void _generateDateFeedback();
	void _generateStatusFeedback();


public:
	ShowCommand(date endDate);
	ShowCommand(date startDate, date endDate);
	ShowCommand(entryStatus status);
	~ShowCommand();

	void execute(Storage* data, Display* display);

};

