#pragma once
#include "Display.h"

//@@author A0102794E

class DisplayStub: public Display
{
public:
	DisplayStub();
	~DisplayStub();

	vector<Entry*> getEventsList();
	Entry* retrieveEntry(EntryType, int);
};


