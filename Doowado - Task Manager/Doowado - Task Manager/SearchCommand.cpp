#include "SearchCommand.h"



void SearchCommand::_generateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_SEARCH_KEYWORDS);
	for (int i = 0; i < _keywords.size(); i++) {
		_feedback.push_back(_keywords[i]);
	}
}

string SearchCommand::_generateDisplayState()
{
	string displayState;

	for (int i = 0; i < _keywords.size(); i++) {
		displayState += "\"" + _keywords[i] + "\"; ";
	}

	return displayState;
}

SearchCommand::SearchCommand(vector<string>& keywords)
{
	_keywords = keywords;
}


SearchCommand::~SearchCommand()
{
}

void SearchCommand::execute(Storage * data, Display * display)
{
	vector<Entry*> eventSearchResult;
	vector<Entry*> taskSearchResult;

	eventSearchResult = data->searchEventsByTitle(_keywords);
	taskSearchResult = data->searchTasksByTitle(_keywords);
	display->updateDisplayEventList(eventSearchResult);
	display->updateDisplayTaskList(taskSearchResult);

	_generateFeedback();
	display->updateCommandFeedback(_feedback);

	string displayState = _generateDisplayState();
	display->setEventDisplayState(displayState);
	display->setTaskDisplayState(displayState);
}
