#pragma once
#include "Display.h"

class DisplayStub: public Display
{
public:
	DisplayStub();
	~DisplayStub();

	vector<Event*> getEventsList();
};

