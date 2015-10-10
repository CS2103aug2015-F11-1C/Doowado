#pragma once
#include "Command.h"

class EditTitleCommand : public Command
{
private:
	int _taskID;
	string _newTitle;

public:
	EditTitleCommand(int, string);
	~EditTitleCommand();
	void execute();
};

