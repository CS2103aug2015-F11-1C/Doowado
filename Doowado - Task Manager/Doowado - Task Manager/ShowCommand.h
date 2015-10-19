#pragma once
#include "Command.h"

class ShowCommand
{
#ifndef TESTMODE
private:
#else 
public: 
#endif
	vector<Event*> _requestedEventList;
	date _requestedDate;

	vector<Task*> _requestedTaskList;

	vector<string> _feedback;

public:
	ShowCommand(date);
	~ShowCommand();

	void execute(Storage* data, Display* display);
	void generateFeedback();
};

