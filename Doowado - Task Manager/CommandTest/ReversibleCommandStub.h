#pragma once
#include "Command.h"

//@@author A0102794E

class ReversibleCommandStub: public Command
{
public:
	ReversibleCommandStub();
	~ReversibleCommandStub();

	void undo(Storage*, Display*);
};

