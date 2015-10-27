#pragma once
#include "Command.h"

class UndoCommand: public Command
{
public:
	UndoCommand();
	~UndoCommand();

	void execute(Storage* data, Display* display, History* history);
};

