#include "EditTimeCommand.h"


EditTimeCommand::EditTimeCommand(string entryType, int displayIndex, ptime newStartTime, ptime newEndTime) {
	_entryType = entryType;
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
