#include "DeleteCommand.h"



DeleteCommand::DeleteCommand(int displayIndex) {
	_taskID = displayIndex;
}


DeleteCommand::~DeleteCommand()
{
}

vector<string> DeleteCommand::execute(Storage* data, Display* display) {
	vector<string> feedback;
	return feedback;
	//delete command
}
