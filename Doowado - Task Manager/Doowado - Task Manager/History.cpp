#include "History.h"



History::History()
{
}


History::~History()
{
}

Command * History::getLastCommand()
{
	return nullptr;
}

void History::pushCommand(Command* cmd)
{
	_commandStack.push(cmd);
}
