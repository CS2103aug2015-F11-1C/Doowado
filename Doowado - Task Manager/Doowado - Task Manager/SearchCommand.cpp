#include "SearchCommand.h"

//@@author A0114137R

void SearchCommand::generateFeedback()
{
	_feedback.push_back(MESSAGE_SUCCESSFUL_SEARCH_KEYWORDS);
	for (int i = 0; i < _keywords.size(); i++) {
		_feedback.push_back(_keywords[i]);
	}
}

string SearchCommand::generateDisplayState()
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
	int size = _keywords.size();
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

	generateFeedback();
	display->updateCommandFeedback(_feedback);

	string displayState = generateDisplayState();
	display->setEventDisplayState(displayState);
	display->setTaskDisplayState(displayState);
	display->setLatestUpdatedEntry(NULL);
}
