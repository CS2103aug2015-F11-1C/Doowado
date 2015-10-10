#pragma once

#include "Entry.h"

class FloatingTask : public Entry {
private:
	bool _isCompleted;

public:
	FloatingTask(string name, bool isCompleted);
	FloatingTask(string name);
	bool getCompleted();
	void setCompleted();
	void printFTask();
};