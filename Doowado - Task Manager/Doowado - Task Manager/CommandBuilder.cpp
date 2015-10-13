#include "CommandBuilder.h"
#include "Command.h"
#include "AddCommand.h"
#include "EditTitleCommand.h"
#include "EditTimeCommand.h"
#include "DeleteCommand.h"


bool CommandBuilder::isEvent()
{
	if (_vInputs.size() == VECTOR_SIZE_EVENT) {
		return true;
	}
	else {
		return false;
	}
}

bool CommandBuilder::isTask()
{
	if (_vInputs.size() == VECTOR_SIZE_TASK) {
		return true;
	}
	else {
		return false;
	}
}

bool CommandBuilder::isFloatingTask()
{
	if (_vInputs.size() == VECTOR_SIZE_FLOATING_TASK) {
		return true;
	}
	else {
		return false;
	}
}

Command * CommandBuilder::createAddCommand()
{
	Command* newAddCommand = nullptr;
	if (isEvent()) {
		newAddCommand = createEventAddCommand();
	}

	else if (isTask()) {
		newAddCommand = createTaskAddCommand();
	}

	else if (isFloatingTask()) {
		newAddCommand = createFTaskAddCommand();
	}

	return newAddCommand;
}

Command* CommandBuilder::createEventAddCommand()
{
	Command * newAddCommand;
	string entryTitle = _vInputs[INDEX_ADD_TITLE];
	string timeInString1 = _vInputs[INDEX_ADD_TIME_1];
	string timeInString2 = _vInputs[INDEX_ADD_TIME_2];

	ptime time1 = from_iso_string(timeInString1);
	ptime time2 = from_iso_string(timeInString2);

	newAddCommand = new AddCommand(entryTitle, time1, time2);

	return newAddCommand;
}

Command * CommandBuilder::createTaskAddCommand()
{
	Command * newAddCommand;
	string entryTitle = _vInputs[INDEX_ADD_TITLE];
	string timeInString1 = _vInputs[INDEX_ADD_TIME_1];

	ptime time1 = from_iso_string(timeInString1);
	newAddCommand = new AddCommand(entryTitle, time1);

	return newAddCommand;
}

Command * CommandBuilder::createFTaskAddCommand()
{
	Command * newAddCommand;
	string entryTitle = _vInputs[INDEX_ADD_TITLE];

	newAddCommand = new AddCommand(entryTitle);
	return newAddCommand;
}

Command * CommandBuilder::createEditTitleCommand()
{
	Command* newEditTitleCommand;
	string eventType = _vInputs[INDEX_EDIT_ENTRY_TYPE];
	int displayIndex = stoi(_vInputs[INDEX_EDIT_DISPLAY_INDEX]);
	string newTitle = _vInputs[INDEX_EDIT_NEW_TITLE];

	newEditTitleCommand = new EditTitleCommand(eventType, displayIndex, newTitle);
	
	return newEditTitleCommand;
}

Command * CommandBuilder::createEditTimeCommand()
{
	Command* newEditTimeCommand;
	string entryType = _vInputs[INDEX_EDIT_ENTRY_TYPE];
	int displayIndex = stoi(_vInputs[INDEX_EDIT_DISPLAY_INDEX]);
	ptime newStartTime = from_iso_string(_vInputs[INDEX_EDIT_NEW_START_TIME]);
	ptime newEndTime = from_iso_string(_vInputs[INDEX_EDIT_NEW_END_TIME]);

	newEditTimeCommand = new EditTimeCommand(entryType, displayIndex, newStartTime, newEndTime);
	return newEditTimeCommand;
}

Command * CommandBuilder::createDeleteCommand()
{
	Command* newDeleteCommand;
	int displayIndex = stoi(_vInputs[INDEX_DELETE_DISPLAY_INDEX]);
	newDeleteCommand = new DeleteCommand(displayIndex);
	return newDeleteCommand;
}

Command * CommandBuilder::createSearchCommand()
{
	//create SearchCommand;
	return nullptr;
		
}

Command * CommandBuilder::createShowCommand()
{
	//create ShowCommand;
	return nullptr;
}

Command * CommandBuilder::createHelpCommand()
{
	//create HelpCommand;
	return nullptr;
}

Command * CommandBuilder::createSaveCommand()
{
	//create SaveCommand
	return nullptr;
}

CommandBuilder::CommandBuilder(vector<string>& vInputs) {
	_vInputs = vInputs;
}

Command* CommandBuilder::buildCommand()
{
	Command *cmd = nullptr;

	string commandType = _vInputs[INDEX_COMMANDTYPE];

	if (commandType == COMMANDTYPE_ADD) {
		cmd = createAddCommand();
	}
	
	else if (commandType == COMMANDTYPE_EDIT_TITLE) {
		cmd = createEditTimeCommand();
	}

	else if (commandType == COMMANDTYPE_EDIT_TIME) {
		cmd = createEditTimeCommand();
	}

	else if (commandType == COMMANDTYPE_DELETE) {
		cmd = createDeleteCommand();
	}

	else if (commandType == COMMANDTYPE_SEARCH) {
		cmd = createSearchCommand();
	}

	else if (commandType == COMMANDTYPE_SHOW) {
		cmd = createShowCommand();
	}
	
	else if (commandType == COMMANDTYPE_SAVE) {
		cmd = createSaveCommand();
	}

	else if (commandType == COMMANDTYPE_HELP) {
		cmd = createHelpCommand();
	}

	return cmd;
}

CommandBuilder::~CommandBuilder()
{
}

