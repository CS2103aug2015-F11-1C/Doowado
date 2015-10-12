#pragma once
#include "Storage.h"
class Display
{
private:
	vector<string> _feedback;
	vector<Event*> _EventList;
	vector<Task*> _TaskList;
public:
	void writeFeedback(vector<string> feedback);
	Display();
	~Display();
};

