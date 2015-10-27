#pragma once
#include "Entry.h"

class Task : public Entry {
private:
	ptime _dueTime;
	bool _isCompleted;
	bool _isOverdue;

public:
	Task(string title, ptime dueTime, bool isCompleted, bool isOverdue);
	Task(string title, ptime dueTime);
	Task(string title);
	ptime getDueTime();
	bool getCompleted();
	bool getOverdue();
	bool isFloatingTask();
	void setDueTime(ptime newDueTime);
	void setCompleted();
	void setOverdue();
	void printTask();

	string toString();
};