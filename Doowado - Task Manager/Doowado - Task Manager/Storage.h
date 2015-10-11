#pragma once

#include "Event.h"
#include "Task.h"
#include "FloatingTask.h"
#include <vector>
#include <fstream>

class Storage {
private:
	vector <Event*> _eventList;
	vector <Task*> _taskList;
	vector <FloatingTask*> _floatingTaskList;
	string _saveDir;

public:
	Storage(string saveDir);
	void addEvent(Event* newEvent);
	void addTask(Task* newTask);
	void addFloatingTask(FloatingTask* newFTask);
	void saveToFile();
	void loadFromFile();
	void displayDefault(vector <Event*> *eventList, vector <Task*> *taskList, vector <FloatingTask*> *FTaskList);				// Display today's event and all uncompleted tasks
	void sortByDate();
};