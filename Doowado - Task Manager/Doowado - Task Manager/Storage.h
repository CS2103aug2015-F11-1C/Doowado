#pragma once

#include "Event.h"
#include "Task.h"
#include "FloatingTask.h"
#include "CommandBuilder.h"
#include <vector>
#include <fstream>
#include <stack>

class Storage {
private:
	vector <Event*> _eventList;
	vector <Task*> _taskList;
	vector <FloatingTask*> _floatingTaskList;
	stack <Command*> _undoStack;
	string _saveDir;

public:
	Storage(string saveDir);
	void addEvent(Event* newEvent);
	void addTask(Task* newTask);
	void addFloatingTask(FloatingTask* newFTask);
	void addToUndoStack(Command* nextCommand);
	void displayDefault(vector <Event*> *eventList, vector <Task*> *taskList, vector <FloatingTask*> *FTaskList);				// Display today's event and all uncompleted tasks
	void sortByDate();
	Command* undoAction();
	void changeSaveDir(string newSaveDir);

	void saveToFile();
	void loadFromFile();
};