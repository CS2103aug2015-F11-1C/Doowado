#include "EditTimeCommand.h"


EditTimeCommand::EditTimeCommand(int displayIndex, ptime newStartTime, ptime newEndTime) {
	_taskID = displayIndex;
	_newStartTime = newStartTime;
	_newEndTime = newEndTime;
}


EditTimeCommand::~EditTimeCommand()
{
}

vector<string> EditTimeCommand::execute(Storage* data, Display *display) {
	vector<string> feedback;
	return feedback;
	//edit time
}
