#include "Display.h"


Display::Display()
{
}


Display::~Display()
{
}

void Display::updateDisplayEventList(vector<Event*>& updatedEventList)
{
	_eventList = updatedEventList;
}

void Display::updateDisplayTaskList(vector<Task*>& updatedTaskList)
{
	_taskList = updatedTaskList;
}

Event * Display::retrieveEvent(int taskID)
{
	Event* event;
	if (taskID < _eventList.size()) {
		event = _eventList[taskID];
	}
	else {
		event = nullptr;
	}
	
	return event;
}

Task * Display::retrieveTask(int taskID)
{
	Task* task;
	if (taskID < _taskList.size()) {
		task = _taskList[taskID];
	}
	else {
		task = nullptr;
	}
	return task;
}
