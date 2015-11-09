#include "Display.h"
#include "Assert.h"

//@@author A0102794E

Display::Display(){}


Display::~Display(){}

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

//@@author 

Entry * Display::retrieveEntry(EntryType entryType, int taskID)
{
	Entry* entryToRetrieve = nullptr;
	
	if (entryType == event) {
		if (taskID < _eventList.size()) {
			entryToRetrieve = _eventList[taskID];
		}
		else {
			entryToRetrieve = nullptr;
		}
	}
	else if (entryType == task) {
		if (taskID < _taskList.size()) {
			entryToRetrieve = _taskList[taskID];
		}
		else {
			entryToRetrieve = nullptr;
		}
	}
	return entryToRetrieve;
}
/*
Entry * Display::retrieveTask(int taskID)
{
	Entry* taskToRetrieve;

	return taskToRetrieve;
}
*/

//@@author A0102794E
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


//@@author 

void Display::setEventDisplayState(string eventDisplayState)
{
	_eventDisplayState = eventDisplayState;
}

void Display::setTaskDisplayState(string taskDisplayState)
{
	_taskDisplayState = taskDisplayState;
}

string Display::getEventDisplayState()
{
	return _eventDisplayState;
}

string Display::getTaskDisplayState()
{
	return _taskDisplayState;
}

void Display::deleteEntry(EntryType entryType, int taskID)
{
	if (entryType == event) {
		_eventList.erase(_eventList.begin() + taskID);
	}
	else if (entryType == task) {
		_taskList.erase(_taskList.begin() + taskID);
	}
}

void Display::deleteEntry(Entry * entryToDelete)
{
	assert(entryToDelete != NULL);

	vector<Entry*>::iterator it = _eventList.begin();

	while (it != _eventList.end()) {
		if (*it == entryToDelete) {
			_eventList.erase(it);
			//LOG(INFO) << "Deleted from EventList for edit; " << (*it)->getTitle();
			break;
		}
		it++;
	}

	it = _taskList.begin();

	while (it != _taskList.end()) {
		if (*it == entryToDelete) {
			_taskList.erase(it);
			//LOG(INFO) << "Deleted from TaskList for edit; " << (*it)->getTitle();
			break;
		}
		it++;
	}

}

void Display::setLatestUpdatedEntry(Entry * latestEntry)
{
	_lastUpdatedEntry = latestEntry;
}

Entry * Display::retrieveLastUpdatedEntry(){
	return _lastUpdatedEntry;
}
