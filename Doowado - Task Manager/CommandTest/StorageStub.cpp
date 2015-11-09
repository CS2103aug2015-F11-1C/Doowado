#include "stdafx.h"
#include "StorageStub.h"

//@@author A0102794E

StorageStub::StorageStub()
{
}

StorageStub::~StorageStub()
{
}

void StorageStub::displayByDate(vector<Entry*>* eventList, vector<Entry*>* taskList, date)
{
	*eventList = _eventList;
	*taskList = _taskList;
}

vector<Entry*> StorageStub::getEventsList()
{
	return _eventList;
}

vector<Entry*> StorageStub::getTasksList()
{
	return _taskList;
}
