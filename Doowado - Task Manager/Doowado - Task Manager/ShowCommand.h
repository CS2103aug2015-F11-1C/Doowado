#pragma once
#include "Command.h"

class ShowCommand
{
private:
	date _requestedDate;

	vector<Event*> _requestedEventList;
	vector<Task*> _requestedTaskList;

public:
	ShowCommand();
	~ShowCommand();

	void execute(Storage* data, Display* display);
};

