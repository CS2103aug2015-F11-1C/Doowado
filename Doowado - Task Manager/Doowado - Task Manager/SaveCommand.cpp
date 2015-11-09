#include "SaveCommand.h"

//@@author A0114137R

void SaveCommand::generateFeedback(bool isSuccessful)
{
	string feedback;
	if (isSuccessful) {
		feedback = MESSAGE_SUCCESSFUL_SAVE + _saveDir;
		_feedback.push_back(feedback);
	}
	else {
		feedback = MESSAGE_UNSUCCESSFUL_SAVE + _saveDir;
		_feedback.push_back(feedback);
	}
}

SaveCommand::SaveCommand(string saveDirectory)
{
	_saveDir = saveDirectory;
}


SaveCommand::~SaveCommand()
{
}

void SaveCommand::execute(Storage * data, Display * display)
{
	bool isSuccessful = true;
	data->changeSaveDirectory(_saveDir);
	
	generateFeedback(isSuccessful);

	display->updateCommandFeedback(_feedback);
	display->setLatestUpdatedEntry(NULL);
	data->saveToFile();
}
