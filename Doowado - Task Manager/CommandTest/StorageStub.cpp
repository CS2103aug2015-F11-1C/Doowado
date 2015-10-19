#include "stdafx.h"
#include "StorageStub.h"


StorageStub::StorageStub(string saveDir): Storage::Storage(saveDir)
{
}


StorageStub::~StorageStub()
{
}

void StorageStub::displayByDate(vector<Event*>* eventList, vector<Task*>* taskList, date)
{
	*eventList = _eventList;
	*taskList = _taskList;
}

vector<Event*> StorageStub::getEventsList()
{
	return _eventList;
}
