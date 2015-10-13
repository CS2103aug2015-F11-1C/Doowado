#pragma once
#include "Storage.h"
class Display
{
private:
	vector<Event*> _eventList;
	vector<Task*> _taskList;
public:
	Display();
	~Display();
	void updateDisplayEventList(vector<Event*>&);
	void updateDisplayTaskList(vector<Task*>&);
};

