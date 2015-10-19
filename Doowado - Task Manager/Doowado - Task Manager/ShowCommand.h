#pragma once
#include "Command.h"

class ShowCommand
{
private:
	date _requestedDate;

	vector<Event*> _requestedEventList;
	vector<Task*> _requestedTaskList;

	vector<string> _feedback;

public:
	ShowCommand(date);
	~ShowCommand();

	void execute(Storage* data, Display* display);
	void generateFeedback();
};

