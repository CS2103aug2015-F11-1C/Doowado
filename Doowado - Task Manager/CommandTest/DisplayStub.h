#pragma once
#include "Display.h"

class DisplayStub: public Display
{
public:
	DisplayStub();
	~DisplayStub();

	vector<Entry*> getEventsList();
	Entry* retrieveEntry(EntryType, int);
};


