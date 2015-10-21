#pragma once
#include "Storage.h"
class Display
{
protected:
	vector<string> _commandFeedback;
	vector<Event*> _eventList;
	vector<Task*> _taskList;
public:
	Display();
	~Display();
	
	//updateDefault
	void updateCommandFeedback(vector<string>&);
	void updateDisplayEventList(vector<Event*>&);
	void updateDisplayTaskList(vector<Task*>&);
	Event* retrieveEvent(int);
	Task* retrieveTask(int);

	void checkValidFeedback(vector<string>&);

	vector<Event*>& getEventList();
	vector<Task*>& getTaskList();
	vector<string>& getCommandFeedback();
};

