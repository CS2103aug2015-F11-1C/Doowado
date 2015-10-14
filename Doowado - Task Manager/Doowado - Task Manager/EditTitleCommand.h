#pragma once
#include "Command.h"

const string eventType = "e";
const string taskType = "t";

class EditTitleCommand : public Command
{
private:
	string _entryType;
	int _taskID;
	string _newTitle;

public:
	EditTitleCommand(string, int, string);
	~EditTitleCommand();
	void execute(Storage* data, Display* display);
};

