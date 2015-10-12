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

public:
	Storage(string saveDir);
	void addEvent(Event* newEvent);
	void addTask(Task* newTask);
	void saveToFile();
	void loadFromFile();
	void displayDefault(vector <Event*> *eventList, vector <Task*> *taskList);				// Display today's event and all uncompleted tasks
	void sortByDate();
};