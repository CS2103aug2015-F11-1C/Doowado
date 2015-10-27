#pragma once

#include "Entry.h"
#include <vector>
#include <fstream>

class Storage {
protected:
	vector <Entry*> _eventList;
	vector <Entry*> _taskList;
	string _saveDir;
	string _helpDir;

public:
	Storage();

	void addEvent(Entry* newEvent);
	void addTask(Entry* newTask);

	vector <Entry*> searchEventsByTitle(vector <string> keywords);
	vector <Entry*> searchTasksByTitle(vector <string> keywords);

	void displayDefault(vector <Entry*> *eventList, vector <Entry*> *taskList);				// Display today's event and all uncompleted tasks
//	vector <Entry*> retrieveByDate(ptime timeIndicator);
	void retrieveByDate(ptime timeIndicator, vector<Entry*>& eventResult, vector<Entry*>& taskResult);
	void retrieveByDate(ptime timeIndicator1, ptime timeIndicator2, vector<Entry*>& eventResult, vector<Entry*>& taskResult);
	vector <Entry*> retrieveIncompleteTasks();
	vector <Entry*> retrieveCompletedTasks();

	vector<Entry*> retrieveEventByDone(bool doneStatus);
	vector<Entry*> retrieveTaskByDone(bool doneStatus);
	void deleteFromEventList(Entry* eventPointer);
	void deleteFromTaskLIst(Entry* taskPointer);

	void changeSaveDirectory(string newSaveDir);

	void saveToFile();
	void loadFromFile();
};