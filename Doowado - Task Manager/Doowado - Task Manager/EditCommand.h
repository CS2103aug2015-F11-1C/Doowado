#pragma once
#include "Command.h"

const string eventType = "e";
const string taskType = "t";

class EditCommand : public Command
{
private:
	EntryType _entryType;
	int _taskID;
	string _newTitle;
	date _newStartDate;
	time_duration _newStartTime;
	date _newEndDate;
	time_duration _newEndTime;

public:
	EditCommand(EntryType entryType,
				int taskID,
				string newTitle,
				date newStartDate,
				time_duration newStartTime,
				date newEndDate,
				time_duration newEndTime);

	~EditCommand();
	void execute(Storage* data, Display* display);
};

