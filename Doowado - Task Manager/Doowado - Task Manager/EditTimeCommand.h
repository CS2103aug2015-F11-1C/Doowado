#pragma once
#include "Command.h"


class EditTimeCommand: public Command {
	private:
		string _entryType;
		int _taskID;
		ptime _newStartTime;
		ptime _newEndTime;

	public:
		EditTimeCommand(string, int, ptime, ptime);
		~EditTimeCommand();
		void execute(Storage* data, Display* display);
};