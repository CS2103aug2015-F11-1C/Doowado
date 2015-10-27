#include "SearchCommand.h"



SearchCommand::SearchCommand(vector<string>& keywords)
{
	_keywords = keywords;
}


SearchCommand::~SearchCommand()
{
}

void SearchCommand::execute(Storage * data, Display * display)
{
	vector<Event*> eventSearchResult;
	vector<Task*> taskSearchResult;

	eventSearchResult = data->searchEventsByTitle(_keywords);
	taskSearchResult = data->searchTasksByTitle(_keywords);
	display->updateDisplayEventList(eventSearchResult);
	display->updateDisplayTaskList(taskSearchResult);

	//generateFeedback(display);
}
