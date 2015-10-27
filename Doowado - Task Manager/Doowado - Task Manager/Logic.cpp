/*#include "Logic.h"

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
	_storage->saveToFile();
}

void Logic::initialiseProgram()
{
	_storage->loadFromFile();
	_storage->saveToFile();
}

Display * Logic::getDisplay()
{
	return _display;
}
*/