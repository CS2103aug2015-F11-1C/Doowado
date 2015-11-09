#pragma once
#include "Command.h"

//@@author A0102794E

class AddCommand: public Command
{
private:
	static const enum EntryType { type_event, type_timed_task, type_floating_task };
	static const string MESSAGE_ADDED;

	string _entryTitle;
	ptime _entryStartTime;
	ptime _entryEndTime;

	vector<string> _feedback;

	EntryType entryType;
	Entry* _newEntry;

public:
	AddCommand(string entryTitle, ptime entryStartTime, ptime entryEndTime);
	~AddCommand();

	void execute(Storage* data, Display *display);
	void undo(Storage* data, Display* display);

	void generateFeedback();
	void checkValidTitle(string);

	void updateDisplay(Display*, Storage*);

	void generateUndoFeedback();
};

