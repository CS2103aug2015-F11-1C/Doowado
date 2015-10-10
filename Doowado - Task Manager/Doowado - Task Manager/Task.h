#pragma once
#include "Entry.h"

class Task : public Entry {
private:
	ptime _dueTime;
	bool _isCompleted;
	bool _isOverdue;

public:
	Task(string name, ptime dueTime, bool isCompleted, bool isOverdue);
	Task(string name, ptime dueTime);
	ptime getDueTime();
	bool getCompleted();
	bool getOverdue();
	void setCompleted();
	void setOverdue();
	void printTask();
};