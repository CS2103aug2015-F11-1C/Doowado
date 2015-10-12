#pragma once
#include "Command.h"

class EditTimeCommand: public Command {
	private:
		int _taskID;
		ptime _newStartTime;
		ptime _newEndTime;

	public:
		EditTimeCommand(int, ptime, ptime);
		~EditTimeCommand();
		void execute(Storage* data, Display* display);
};