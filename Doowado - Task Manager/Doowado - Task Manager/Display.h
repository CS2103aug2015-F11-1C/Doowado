#pragma once
#include "Storage.h"
class Display
{
private:
	vector<string> _commandFeedback;
	vector<Event*> _eventList;
	vector<Task*> _taskList;
public:
	Display();
	~Display();

	void updateCommandFeedback(vector<string>&);

	void updateDisplayEventList(vector<Event*>&);
	void updateDisplayTaskList(vector<Task*>&);
	Event* retrieveEvent(int);
	Task* retrieveTask(int);
};

