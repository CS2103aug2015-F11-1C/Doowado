#include "CommandBuilder.h"
#include "Command.h"
#include "AddCommand.h"
#include "EditTitleCommand.h"
#include "EditTimeCommand.h"
#include "DeleteCommand.h"


CommandBuilder::CommandBuilder(vector<string>& vInputs) {
	_vInputs = vInputs;
}

Command* CommandBuilder::buildCommand()
{
	Command *cmd = nullptr;

	string commandType = _vInputs[INDEX_COMMANDTYPE];

	if (commandType == COMMANDTYPE_ADD) {
		string entryTitle = _vInputs[INDEX_TITLE];

		if (VECTOR_SIZE_EVENT == _vInputs.size()) {
			string timeInString1 = _vInputs[INDEX_TIME_1];
			string timeInString2 = _vInputs[INDEX_TIME_2];

			ptime time1 = from_iso_string(timeInString1);
			ptime time2 = from_iso_string(timeInString2);

			cmd = new AddCommand(entryTitle, time1, time2);

			return cmd;
		}

		else if (VECTOR_SIZE_TASK == _vInputs.size()) {
			string timeInString1 = _vInputs[INDEX_TIME_1];

			ptime time1 = from_iso_string(timeInString1);
			cmd = new AddCommand(entryTitle, time1);

			return cmd;
		}

		else if (VECTOR_SIZE_FLOATING_TASK == _vInputs.size()) {
			cmd = new AddCommand(entryTitle);

			return cmd;
		}
	}
	
	else if (commandType == COMMANDTYPE_EDIT_TITLE) {
		int displayIndex = stoi(_vInputs[1]);
		string newTitle = _vInputs[2];

		cmd = new EditTitleCommand(displayIndex, newTitle);

		return cmd;
	}

	else if (commandType == COMMANDTYPE_EDIT_TIME) {
		int displayIndex = stoi(_vInputs[1]);
		ptime newStartTime = from_iso_string(_vInputs[2]);
		ptime newEndTime = from_iso_string(_vInputs[3]);

		cmd = new EditTimeCommand(displayIndex, newStartTime, newEndTime);

		return cmd;
	}

	else if (commandType == COMMANDTYPE_DELETE) {
		int displayIndex = stoi(_vInputs[1]);

		cmd = new DeleteCommand(displayIndex);

		return cmd;
	}
}

CommandBuilder::~CommandBuilder()
{
}

