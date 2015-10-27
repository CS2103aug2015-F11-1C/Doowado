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

void Display::updateDisplayEventList(vector<Entry*>& updatedEventList)
{
	_eventList = updatedEventList;
}

void Display::updateDisplayTaskList(vector<Entry*>& updatedTaskList)
{
	_taskList = updatedTaskList;
}

Entry * Display::retrieveEvent(int taskID)
{
	Entry* eventToRetrieve;
	if (taskID <= _eventList.size()) {
		eventToRetrieve = _eventList[taskID-1];
	}
	else {
		eventToRetrieve = nullptr;
	}
	
	return eventToRetrieve;
}

Entry * Display::retrieveTask(int taskID)
{
	Entry* taskToRetrieve;
	if (taskID <= _taskList.size()) {
		taskToRetrieve = _taskList[taskID-1];
	}
	else {
		taskToRetrieve = nullptr;
	}
	return taskToRetrieve;
}

void Display::checkValidFeedback(vector<string>& feedback)
{
	assert(feedback.size() != 0);
}

vector<Entry*>& Display::getEventList()
{
	return _eventList;
}

vector<Entry*>& Display::getTaskList()
{
	return _taskList;
}

vector<string>& Display::getCommandFeedback()
{
	return _commandFeedback;
}
