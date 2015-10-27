#include "UndoCommand.h"

const string UndoCommand::MSG_NOTHING_TO_UNDO = "Nothing to undo";

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

	if (doesNotExist(lastReversibleCmd)) {
		generateFailureFeedback();
		display->updateCommandFeedback(_feedback);
		return;
	}

	lastReversibleCmd->undo(data, display, history);
}

bool UndoCommand::doesNotExist(Command *cmd)
{
	return (NULL == cmd);
}

void UndoCommand::generateFailureFeedback()
{
	_feedback.push_back(MSG_NOTHING_TO_UNDO);
}
