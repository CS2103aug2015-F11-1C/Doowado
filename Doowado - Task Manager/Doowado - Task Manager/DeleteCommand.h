#pragma once
#include "Command.h"

const string MESSAGE_SUCCESSFUL_DELETE = "Successfully deleted!";

class DeleteCommand: public Command {
	private:
		EntryType _entryType;
		int _taskID;
		Entry* _eventDeleted;
		Entry* _taskDeleted;
		vector<string> _feedback;

		void generateFeedback();

	public:
		DeleteCommand(EntryType, int);
		~DeleteCommand();
		EntryType getEntryType();
		int getIndex();

		void execute(Storage* data, Display* display);
//		void undo(Storage* data, Display* display);
};

