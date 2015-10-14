#include "EditTitleCommand.h"


EditTitleCommand::EditTitleCommand(int displayIndex, string newTitle)
{
	int _taskId = displayIndex;
	string _newTitle = newTitle;
}


EditTitleCommand::~EditTitleCommand()
{
}

vector<string> EditTitleCommand::execute(Storage* data, Display *display)
{
	vector<string> feedback;
	return feedback;
	//edit displayedText
}
