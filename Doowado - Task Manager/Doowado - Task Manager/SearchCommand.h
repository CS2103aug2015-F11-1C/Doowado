#pragma once
#include "Command.h"

const string MESSAGE_SUCCESSFUL_SEARCH_KEYWORDS = "Showing entries with keyword(s): ";

class SearchCommand : public Command
{
private:
	std::vector<std::string> _keywords;
	std::vector<std::string> _feedback;
	void _generateFeedback();
	std::string _generateDisplayState();

public:
	SearchCommand(std::vector<std::string>&);
	~SearchCommand();
	void execute(Storage* storage, Display* display);
};

