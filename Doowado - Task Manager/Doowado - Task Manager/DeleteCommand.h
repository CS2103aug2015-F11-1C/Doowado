#pragma once
#include "Command.h"

class DeleteCommand: public Command {
	private:
		EntryType _entryType;
		int _taskID;
		Event* _eventDeleted;
		Task* _taskDeleted;

	public:
		DeleteCommand(EntryType, int);
		~DeleteCommand();
		void execute(Storage* data, Display* display);
//		void undo(Storage* data, Display* display);
};

