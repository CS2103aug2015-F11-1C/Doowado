#pragma once
#include "Command.h"

class ShowCommand : public Command
{
#ifndef TESTMODE
private:
#else 
public: 
#endif
	vector<Event*> _requestedEventList;
	ptime _requestedDate;

	vector<Task*> _requestedTaskList;

	vector<string> _feedback;

public:
	ShowCommand(ptime);
	~ShowCommand();

	void execute(Storage* data, Display* display);
	void generateFeedback();
};

