#pragma once
#include "Command.h"

const string MESSAGE_SUCCESSFUL_SEARCH_KEYWORDS = "Showing entries with keyword: ";

class SearchCommand : public Command
{
private:
	vector<string> _keywords;
	vector<string> _feedback;
	void _generateFeedback();

public:
	SearchCommand(vector<string>&);
	~SearchCommand();
	void execute(Storage* storage, Display* display);
};

