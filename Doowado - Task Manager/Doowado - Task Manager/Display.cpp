#include "Display.h"
#include "Assert.h"


Display::Display()
{
}


Display::~Display()
{
}

void Display::updateCommandFeedback(vector<string>& feedback)
{
	checkValidFeedback(feedback);
	_commandFeedback = feedback;
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
	Event* eventToDelete;
	if (taskID <= _eventList.size()) {
		eventToDelete = _eventList[taskID-1];
	}
	else {
		eventToDelete = nullptr;
	}
	
	return eventToDelete;
}

Task * Display::retrieveTask(int taskID)
{
	Task* task;
	if (taskID <= _taskList.size()) {
		task = _taskList[taskID-1];
	}
	else {
		task = nullptr;
	}
	return task;
}

void Display::checkValidFeedback(vector<string>& feedback)
{
	assert(feedback.size() != 0);
}

vector<Event*>& Display::getEventList()
{
	return _eventList;
}

vector<Task*>& Display::getTaskList()
{
	return _taskList;
}

vector<string>& Display::getCommandFeedback()
{
	return _commandFeedback;
}
