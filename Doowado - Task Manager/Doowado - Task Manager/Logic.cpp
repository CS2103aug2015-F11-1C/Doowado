#include "Logic.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP;

void Logic::updateOverdueTask()
{
	std::vector<Entry*> taskList;
	taskList = _storage->retrieveTaskList();

	for (int i = 0; i < taskList.size(); i++) {
		ptime currTime(second_clock::local_time());

		if (currTime > taskList[i]->getEndTime() && !taskList[i]->isDone()) {
			taskList[i]->setOverdue(true);
		}
	}
}

void Logic::updateDoneEvent()
{
	std::vector<Entry*> eventList;
	eventList = _storage->retrieveEventList();

	for (int i = 0; i < eventList.size(); i++) {
		ptime currTime(second_clock::local_time());

		if (currentTime > eventList[i]->getEndTime()) {
			eventList[i]->setDone(true);
		}
	}
}

void Logic::updateClashEvent()
{
	std::vector<Entry*> eventList;
	eventList = _storage->retrieveEventList();

	for (int i = 0; i < eventList.size(); i++) {
		ptime eventStartTime1 = eventList[i]->getStartTime();
		ptime eventEndTime1 = eventList[i]->getEndTime();

		for (int j = i+1; j < eventList.size(); j++) {
			ptime eventStartTime2 = eventList[j]->getStartTime();
			ptime eventEndTime2 = eventList[j]->getEndTime();
			if (isOverlapTime(eventStartTime1, eventEndTime1, eventStartTime2, eventEndTime2)) {
				eventList[i]->setClash(true);
				eventList[j]->setClash(true);
			}
		}
	}
}

bool Logic::isOverlapTime(ptime startTime1, ptime endTime1, ptime startTime2, ptime endTime2)
{
	bool isOverlap;

	if (startTime2 >= startTime1 && startTime2 <= endTime1) {
		isOverlap = true;
	}
	else if (endTime2 >= startTime1 && endTime2 <= endTime1) {
		isOverlap = true;
	}
	else {
		isOverlap = false;
	}
	return isOverlap;
}

Logic::Logic()
{
	//@@author A0114519J
	// Load configuration from file
	el::Configurations conf("Log.conf");
	// Reconfigure single logger
	el::Loggers::reconfigureLogger("default", conf);
	// Actually reconfigure all loggers instead
	el::Loggers::reconfigureAllLoggers(conf);
	// Now all the loggers will use configuration from file

	//@@author
	_storage = new Storage();
	_cmdBuilder = new CommandBuilder();
	_parser = new Parser();
	_display = new Display();
}


Logic::~Logic()
{
}

void Logic::processCommand(string userInput)
{
	
		ParserResult parserResult;
		parserResult = _parser->parse(userInput);

		Command* cmd;

		cmd = _cmdBuilder->buildCommand(parserResult);
		cmd->execute(_storage, _display);

		updateOverdueTask();
		updateDoneEvent();
		updateClashEvent();
		_storage->saveToFile();	
}

void Logic::initialiseProgram()
{
	_storage->loadFromFile();
	updateOverdueTask();
	updateDoneEvent();
	updateClashEvent();
	vector<Entry*> eventDefaultList;
	vector<Entry*> taskDefaultList;

	_storage->retrieveByDate(currentTime, eventDefaultList, taskDefaultList);

	taskDefaultList = _storage->retrieveTaskByDone(false);
	_display->updateDisplayEventList(eventDefaultList);
	_display->updateDisplayTaskList(taskDefaultList);
}

Display * Logic::getDisplay()
{
	return _display;
}

