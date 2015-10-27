#pragma once
#include "Command.h"

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

	void execute(Storage* data, Display* display, History* history);
	bool doesNotExist(Command*);
	void generateFailureFeedback();
};

