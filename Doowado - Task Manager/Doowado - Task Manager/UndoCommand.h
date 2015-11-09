#pragma once
#include "Command.h"

//@@author A0102794E

class UndoCommand: public Command
{
#ifndef TESTMODE
private:
#else 
public:
#endif
	static const string MSG_NOTHING_TO_UNDO;
	vector<string> _feedback;
public:
	UndoCommand();
	~UndoCommand();

	void execute(Storage* data, Display* display);
	bool doesNotExist(Command*);
	void generateFailureFeedback();
};

