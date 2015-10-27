#include "UndoCommand.h"



UndoCommand::UndoCommand()
{
}


UndoCommand::~UndoCommand()
{
}

void UndoCommand::execute(Storage * data, Display * display, History * history)
{
	Command* lastReversibleCmd;
	lastReversibleCmd =  history->getLastCommand();
}
