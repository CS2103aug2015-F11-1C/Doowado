#pragma once
#include "Command.h"
#include "CommandException.h"

const string MESSAGE_SUCCESSFUL_MARK_DONE = "Marked as done: ";

class MarkDoneCommand : public Command
{
private:
	EntryType _entryType;
	int _taskID;
	Entry* _eventMarkedDone;
	Entry* _taskMarkedDone;
	vector<string> _feedback;

	void _generateFeedback();

public:
	MarkDoneCommand(EntryType, int);
	~MarkDoneCommand();

	EntryType getEntryType();
	int getIndex();
	Entry* getEventMarkedDone();
	Entry* getTaskMarkedDone();

	void execute(Storage*, Display*);
	//void undo(Storage * data, Display * display);

};

