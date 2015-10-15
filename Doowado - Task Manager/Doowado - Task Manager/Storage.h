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
	vector <Entry*> searchName(string keyword);
	void displayDefault(vector <Event*> *eventList, vector <Task*> *taskList);				// Display today's event and all uncompleted tasks
	vector <Event*> displayByDate(string timeIndicator);
	vector <Task*> displayIncompleteTasks();
	vector <Task*> displayCompletedTasks();
	void deleteFromEventList(Event* eventPointer);
	void deleteFromTaskLIst(Task* taskPointer);

	void saveToFile();
	void loadFromFile();
};