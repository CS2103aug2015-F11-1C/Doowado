#pragma once

#include "Event.h"
#include "Task.h"
#include <vector>
#include <fstream>

class Storage {
private:
	vector <Event*> _eventList;
	vector <Task*> _taskList;
	string _saveDir;
	string _helpDir;

public:
	Storage(string saveDir);

	void addEvent(Event* newEvent);
	void addTask(Task* newTask);

	vector <Event*> searchEventsByName(vector <string> keywords);
	vector <Task*> searchTasksByName(vector <string> keywords);

	void displayDefault(vector <Event*> *eventList, vector <Task*> *taskList);				// Display today's event and all uncompleted tasks
	vector <Event*> displayByDate(ptime timeIndicator);
	vector <Event*> displayByDate(ptime timeIndicator1, ptime timeIndicator2);
	vector <Task*> displayIncompleteTasks();
	vector <Task*> displayCompletedTasks();

	void deleteFromEventList(Event* eventPointer);
	void deleteFromTaskLIst(Task* taskPointer);

	void saveToFile();
	void loadFromFile();
};