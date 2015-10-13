#include "EditTitleCommand.h"


EditTitleCommand::EditTitleCommand(string entryType, int displayIndex, string newTitle)
{
	string _entryType = entryType;
	int _taskId = displayIndex;
	string _newTitle = newTitle;
}


EditTitleCommand::~EditTitleCommand()
{
}

void EditTitleCommand::execute(Storage* data, Display *display)
{
	//edit displayedText
}
