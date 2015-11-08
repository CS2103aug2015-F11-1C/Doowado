#pragma once
#include "Command.h"
#include "CommandException.h"

const string MESSAGE_SUCCESSFUL_DELETE = "Deleted: ";

class DeleteCommand: public Command {
	private:
		EntryType _entryType;
		int _taskID;
		Entry* _eventDeleted;
		Entry* _taskDeleted;
		vector<string> _feedback;

		void generateFeedback();
		void generateUndoFeedback();

		void updateDisplay(Display *, Storage *);

		ptime getRelevantTime(EntryType _entryType);

	public:
		DeleteCommand(EntryType, int);
		~DeleteCommand();
		EntryType getEntryType();
		int getIndex();

		void execute(Storage* data, Display* display);
		void undo(Storage* data, Display* display);
		void restoreToStorage(Storage *);
};

