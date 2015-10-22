#pragma once
#include "Command.h"

class AddCommand: public Command
{
private:
	static const enum EntryType { type_event, type_timed_task, type_floating_task };
	static const string MESSAGE_ADDED;

	string _entryName;
	ptime _entryStartTime;
	ptime _entryEndTime;
	ptime _entryDueTime;

	vector<string> _feedback;
	
	EntryType entryType;

public:
	AddCommand(string name);
	AddCommand(string name, ptime time1);
	AddCommand(string name, ptime time1, ptime time2);
	AddCommand(string, ptime, ptime, ptime);
	~AddCommand();

	void execute(Storage* data, Display *display);

	void generateFeedback();
	void checkValidName(string);

	void updateDisplay(Display*, Storage*);
};

