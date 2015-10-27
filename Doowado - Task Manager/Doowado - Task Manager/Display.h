#pragma once
#include "Storage.h"
class Display
{
protected:
	vector<string> _commandFeedback;
	vector<Entry*> _eventList;
	vector<Entry*> _taskList;
public:
	Display();
	~Display();
	
	//updateDefault
	void updateCommandFeedback(vector<string>&);
	void updateDisplayEventList(vector<Entry*>&);
	void updateDisplayTaskList(vector<Entry*>&);
	Entry* retrieveEvent(int);
	Entry* retrieveTask(int);

	void checkValidFeedback(vector<string>&);

	vector<Entry*>& getEventList();
	vector<Entry*>& getTaskList();
	vector<string>& getCommandFeedback();
};

