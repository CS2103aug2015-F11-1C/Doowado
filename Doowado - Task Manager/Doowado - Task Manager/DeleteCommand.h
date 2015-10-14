#pragma once
#include "Command.h"

class DeleteCommand: public Command {
	private:
		int _taskID;

	public:
		DeleteCommand(int);
		~DeleteCommand();
		vector<string> execute(Storage* data, Display* display);
};

