#include "EditTimeCommand.h"


EditTimeCommand::EditTimeCommand(int displayIndex, ptime newStartTime, ptime newEndTime) {
	_taskID = displayIndex;
	_newStartTime = newStartTime;
	_newEndTime = newEndTime;
}


EditTimeCommand::~EditTimeCommand()
{
}

void EditTimeCommand::execute(Storage* data, Display *display) {
	//edit time
}
