#pragma once
#include "Command.h"

//@@author A0114137R

const string MESSAGE_SUCCESSFUL_SAVE = "File is successfully saved to ";
const string MESSAGE_UNSUCCESSFUL_SAVE = "Unsuccessful save to ";

class SaveCommand : public Command
{
private:
	string _saveDir;
	vector<string> _feedback;

	void generateFeedback(bool);

public:
	SaveCommand(string);
	~SaveCommand();
	void execute(Storage*, Display*);
};

