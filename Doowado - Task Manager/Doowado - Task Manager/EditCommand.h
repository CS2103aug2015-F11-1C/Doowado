#pragma once
#include "Command.h"

const string eventType = "e";
const string taskType = "t";

class EditCommand : public Command
{
private:
	EntryType _entryType;
	int _taskID;
	string _newTitle;
	ptime _newStartDate;
	ptime _newStartTime;
	ptime _newEndDate;
	ptime _newEndTime;

public:
	EditCommand(EntryType, int, string, ptime, ptime, ptime, ptime);
	~EditCommand();
	void execute(Storage* data, Display* display);
};

