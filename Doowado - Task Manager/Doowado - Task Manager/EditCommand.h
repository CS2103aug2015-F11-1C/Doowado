#pragma once
#include "Command.h"

const string eventType = "e";
const string taskType = "t";

class EditCommand : public Command
{
private:
	string _entryType;
	int _taskID;
	string _newTitle;
	ptime _newStartTime;
	ptime _newEndTime;
	ptime _newDueTime;

public:
	EditCommand(string, int, string, ptime, ptime, ptime);
	~EditCommand();
	void execute(Storage* data, Display* display);
};

