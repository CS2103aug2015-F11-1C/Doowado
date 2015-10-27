#pragma once
#include "Command.h"
class SearchCommand : public Command
{
private:
	vector<string> _keywords;
//	void _generateFeedback();

public:
	SearchCommand(vector<string>&);
	~SearchCommand();
	void execute(Storage* storage, Display* display);

};

