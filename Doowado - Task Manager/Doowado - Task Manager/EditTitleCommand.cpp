#include "EditTitleCommand.h"


EditTitleCommand::EditTitleCommand(int displayIndex, string newTitle)
{
	int _taskId = displayIndex;
	string _newTitle = newTitle;
}


EditTitleCommand::~EditTitleCommand()
{
}

void EditTitleCommand::execute()
{
	//edit displayedText
}
