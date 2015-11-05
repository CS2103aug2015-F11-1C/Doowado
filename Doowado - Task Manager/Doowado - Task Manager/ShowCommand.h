#pragma once
#include "Command.h"

class ShowCommand : public Command
{
#ifndef TESTMODE
private:
#else 
public: 
#endif
	vector<Entry*> _requestedEventList;
	ptime _requestedDate;

	vector<Entry*> _requestedTaskList;

	vector<string> _feedback;
	string generateDisplayState(date startDate, date endDate);

public:
	ShowCommand(ptime);
	~ShowCommand();

	void execute(Storage* data, Display* display);
	void generateFeedback();
};

