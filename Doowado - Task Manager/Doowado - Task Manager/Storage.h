#pragma once

#include "Entry.h"
#include "StorageException.h"
#include <vector>
#include <fstream>

enum EntryType { event, task };

class Storage {
protected:
	vector <Entry*> _eventList;
	vector <Entry*> _taskList;
	string _saveDir;
	string _helpDir;

public:
	Storage();

#ifdef TESTMODE
	vector<Entry*> getEventList() {
		return _eventList;
	}
	vector<Entry*>  getTaskList() {
		return _taskList;
	}
	void setEventList(vector<Entry*> hardcodedList) {
		_eventList = hardcodedList;
	}
	void setTaskList(vector<Entry*> hardcodedList) {
		_taskList = hardcodedList;
	}
#endif

	void addEvent(Entry* newEvent);
	void addTask(Entry* newTask);

	vector <Entry*> searchEventsByTitle(vector <string> keywords);
	vector <Entry*> searchTasksByTitle(vector <string> keywords);

	void displayDefault(vector <Entry*> *eventList, vector <Entry*> *taskList);				// Display today's event and all uncompleted tasks
	void retrieveByDate(ptime timeIndicator, vector<Entry*>& eventResult, vector<Entry*>& taskResult);
	void retrieveByDate(ptime timeIndicator1, ptime timeIndicator2, vector<Entry*>& eventResult, vector<Entry*>& taskResult);
	
	vector<Entry*> retrieveEventByDone(bool doneStatus);
	vector<Entry*> retrieveTaskByDone(bool doneStatus);
	vector<Entry*> retrieveTaskByOverdue(bool overdueStatus);
	void deleteFromEventList(Entry* eventPointer);
	void deleteFromTaskLIst(Entry* taskPointer);

	void changeSaveDirectory(string newSaveDir);

	void saveToFile();
	void loadFromFile();

	std::vector<Entry*> retrieveEventList();
	std::vector<Entry*> retrieveTaskList();
};