#pragma once
#include "Command.h"

class AddCommand: public Command
{
private:
	string _entryName;
	ptime _entryStartTime;
	ptime _entryEndTime;
	ptime _entryDueTime;

public:
	AddCommand(string name);
	AddCommand(string name, ptime time1);
	AddCommand(string name, ptime time1, ptime time2);
	~AddCommand();

	void execute(Storage* data);
};

