#include "History.h"

//@@author A0102794E

stack<Command*> History::_commandStack;

History::History()
{
}


History::~History()
{
}

Command * History::getLastCommand()
{
	if (_commandStack.empty()) {
		return nullptr;
	}

	Command* lastReversibleCmd;
	lastReversibleCmd = _commandStack.top();
	_commandStack.pop();
	return lastReversibleCmd;
}

void History::pushCommand(Command* cmd)
{
	_commandStack.push(cmd);
}

void History::empty()
{
	while (!_commandStack.empty()) {
		_commandStack.pop();
	}
}
