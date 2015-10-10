#pragma once

#include "Entry.h"

class Event: public Entry {
private:
	ptime _startTime;
	ptime _endTime;

public:
	Event(string name, ptime startTime, ptime endTime);
	ptime getStartTime();
	ptime getEndTime();
	void setStartTime(ptime newStartTime);
	void setEndTime(ptime newEndTime);
	void printEvent();
};