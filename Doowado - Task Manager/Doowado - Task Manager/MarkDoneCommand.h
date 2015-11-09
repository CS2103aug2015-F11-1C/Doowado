#pragma once
#include "Command.h"
#include "CommandException.h"

//@@author A0114137R

const std::string MESSAGE_SUCCESSFUL_MARK_DONE = "Marked as done: ";

class MarkDoneCommand : public Command
{
private:
	EntryType _entryType;
	int _taskID;
	Entry* _taskMarkedDone;
	std::vector<std::string> _feedback;

	void generateFeedback();

public:
	MarkDoneCommand(EntryType, int);
	~MarkDoneCommand();

	EntryType getEntryType();
	int getIndex();
	Entry* getTaskMarkedDone();

	void execute(Storage*, Display*);
	//void undo(Storage * data, Display * display);

};

