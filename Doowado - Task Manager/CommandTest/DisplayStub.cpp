#include "stdafx.h"
#include "DisplayStub.h"


DisplayStub::DisplayStub()
{
}


DisplayStub::~DisplayStub()
{
}

vector<Entry*> DisplayStub::getEventsList()
{
	return _eventList;
}

Entry * DisplayStub::retrieveEntry(EntryType entryType, int taskID) {
	
	return _eventList[0];
}
