#pragma once
#include "Command.h"
class MarkDoneCommand : public Command
{
private:
	EntryType _entryType;
	int _taskID;
	Entry* _eventMarkedDone;
	Entry* _taskMarkedDone;
	vector<string> _feedback;

public:
	MarkDoneCommand(EntryType, int);
	~MarkDoneCommand();

	EntryType getEntryType();
	int getIndex();
	Entry* getEventMarkedDone();
	Entry* getTaskMarkedDone();

	void execute(Storage*, Display*);

};

