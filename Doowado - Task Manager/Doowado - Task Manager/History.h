#pragma once
#include <stack>
#include "Command.h"
class History
{
private:
	stack<Command*> _commandStack;
public:
	History();
	~History();

	Command* getLastCommand();
	void pushCommand();
};

