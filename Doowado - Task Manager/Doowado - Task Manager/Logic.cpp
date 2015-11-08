#include "Logic.h"

void Logic::updateOverdueTask()
{
	std::vector<Entry*> taskList;
	taskList = _storage->retrieveTaskList();

	for (int i = 0; i < taskList.size(); i++) {
		ptime currTime(second_clock::local_time());

		if (currentTime > taskList[i]->getEndTime()) {
			taskList[i]->setOverdue(true);
		}
	}
}

Logic::Logic()
{
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
	_storage->saveToFile();
}

void Logic::initialiseProgram()
{
	_storage->loadFromFile();
	updateOverdueTask();
	vector<Entry*> eventDefaultList;
	vector<Entry*> taskDefaultList;

	_storage->retrieveByDate(currentTime, eventDefaultList, taskDefaultList);
	_display->updateDisplayEventList(eventDefaultList);
	_display->updateDisplayTaskList(taskDefaultList);
}

Display * Logic::getDisplay()
{
	return _display;
}

