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
