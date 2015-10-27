#pragma once

#include "Event.h"
#include "Task.h"
#include <vector>
#include <fstream>

class Storage {
protected:
	vector <Event*> _eventList;
	vector <Task*> _taskList;
	string _saveDir;
	string _helpDir;

public:
	Storage();

	void addEvent(Event* newEvent);
	void addTask(Task* newTask);

	vector <Event*> searchEventsByTitle(vector <string> keywords);
	vector <Task*> searchTasksByTitle(vector <string> keywords);

	void displayDefault(vector <Event*> *eventList, vector <Task*> *taskList);				// Display today's event and all uncompleted tasks
	vector <Event*> retrieveByDate(ptime timeIndicator);
	void retrieveByDate(ptime timeIndicator, vector<Event*>& eventResult, vector<Task*>& taskResult);
	vector <Event*> retrieveByDate(ptime timeIndicator1, ptime timeIndicator2);
	vector <Task*> retrieveIncompleteTasks();
	vector <Task*> retrieveCompletedTasks();

	void deleteFromEventList(Event* eventPointer);
	void deleteFromTaskLIst(Task* taskPointer);

	void changeSaveDirectory(string newSaveDir);

	void saveToFile();
	void loadFromFile();
};