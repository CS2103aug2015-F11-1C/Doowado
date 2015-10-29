#pragma once
#include "Command.h"
class ReversibleCommandStub: public Command
{
public:
	ReversibleCommandStub();
	~ReversibleCommandStub();

	void undo(Storage*, Display*);
};

