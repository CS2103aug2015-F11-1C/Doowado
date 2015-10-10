#pragma once
#include "Command.h"

class DeleteCommand: public Command {
	private:
		int _taskID;

	public:
		DeleteCommand(int);
		~DeleteCommand();
		void execute();
};

