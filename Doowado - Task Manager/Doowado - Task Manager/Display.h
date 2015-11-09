#pragma once
#include "Storage.h"
#include "easylogging++.h"

enum entryStatus { completed, incomplete, overdue, intime };

class Display
{
protected:
	vector<string> _commandFeedback;
	vector<Entry*> _eventList;
	vector<Entry*> _taskList;
	
	string _eventDisplayState;
	string _taskDisplayState;

	Entry* _lastUpdatedEntry;

public:
	Display(void);
	~Display();
	
	//updateDefault
	void updateCommandFeedback(vector<string>&);
	void updateDisplayEventList(vector<Entry*>&);
	void updateDisplayTaskList(vector<Entry*>&);
	
	Entry* retrieveEntry(EntryType, int);
	void checkValidFeedback(vector<string>&);

	vector<Entry*>& getEventList();
	vector<Entry*>& getTaskList();
	vector<string>& getCommandFeedback();

	void setEventDisplayState(string eventDisplayState);
	void setTaskDisplayState(string taskDisplayState);
	string getEventDisplayState();
	string getTaskDisplayState();

	void deleteEntry(EntryType, int);
	void deleteEntry(Entry * entryToDelete);
	void setLatestUpdatedEntry(Entry * latestEntry);
	Entry* retrieveLastUpdatedEntry();
};

