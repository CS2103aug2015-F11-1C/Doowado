#include "CommandBuilder.h"
#include "Command.h"
#include "AddCommand.h"
#include "EditCommand.h"
#include "EditTimeCommand.h"
#include "DeleteCommand.h"
#include "ShowCommand.h"
#include "SearchCommand.h"
#include "SaveCommand.h"


/*
EntryType CommandBuilder::checkEntryType(ParserResult &parserResult)
{
	if (parserResult.getEndDate.empty() && parserResult.getEndTime.empty()) {
		//can replace with exception because with no end date and time, there shouldn't be any start date 
		if (parserResult.getStartDate.empty() && parserResult.getStartTime.empty()) {
			return floatingTask;
		}
		//else throw exceptions
	}
	else {
		if (parserResult.getStartDate.empty() && parserResult.getStartTime.empty()) {
			return task;
		}
		else {
			return event;
		}
	}
}
*/

ptime CommandBuilder::createPTimeObject(string date, string time)
{
	string isoString;
	ptime dateTime;

	isoString = date + "T" + time;
	dateTime = from_iso_string(isoString);

	return dateTime;
}

TypeOfEdit CommandBuilder::checkEditType(vector<string> vNewTitles, vector<string> vNewStartDates, vector<string> vNewStartTimes, vector<string> vNewEndDates, vector<string> vNewEndTimes)
{
	if (!vNewTitles.empty()) {
		return editTitle;
	}
	else if (!vNewStartDates.empty()) {
		if (!vNewStartTimes.empty()) {
			return editStartDateAndTime;
		}
		return editStartDate;
	}
	else if (!vNewStartTimes.empty()) {
		return editStartTime;
	}
	else if (!vNewEndDates.empty()) {
		if (!vNewEndTimes.empty()) {
			return editEndDateAndTime;
		}
	}
	else if (!vNewEndTimes.empty()) {

	}
	return TypeOfEdit();
}

Command * CommandBuilder::createAddCommand(ParserResult& parserResult)
{
	Command * addCommand;
	string entryTitle;
	ptime entryStartPtime;
	ptime entryEndPtime;
	ptime entryDuePtime;

	vector<string> description = parserResult.getDescription();
	vector<string> startDate = parserResult.getStartDate();
	vector<string> startTime = parserResult.getStartTime();
	vector<string> endDate = parserResult.getEndDate();
	vector<string> endTime = parserResult.getEndTime();

	entryTitle = description[0];

	//assert(startDate.size() == startTime.size());
	//assert(endDate.size() == endTime.size());

	if (!startDate.empty() && !startTime.empty()) {
		assert(!endDate.empty() && !endTime.empty());

		string entryStartDate = startDate[0];
		string entryStartTime = startTime[0];
		string entryISOStartTime = entryStartDate + "T" + entryStartTime;
		entryStartPtime = from_iso_string(entryISOStartTime);

		string entryEndDate = endDate[0];
		string entryEndTime = endTime[0];
		string entryISOEndTime = entryEndDate + "T" + entryEndTime;
		entryEndPtime = from_iso_string(entryISOEndTime);
	}

	else if (!endDate.empty() && !endTime.empty()) {
		string entryEndDate = endDate[0];
		string entryEndTime = endTime[0];
		string entryISOEndTime = entryEndDate + "T" + entryEndTime;
		entryDuePtime = from_iso_string(entryISOEndTime);
	}

	addCommand = new AddCommand(entryTitle, entryStartPtime, entryEndPtime, entryDuePtime);

	return addCommand;
}

Command * CommandBuilder::createEditCommand(ParserResult &parserResult)
{
	Command* editCommand;
	
	EntryType entryType;
	int taskID = 0;
	string newTitle = "";
	ptime newStartDate;
	ptime newStartTime;
	ptime newEndDate;
	ptime newEndTime;
	ptime newDueTime;

	vector<string> vEntryTypes = parserResult.getEntryType();
	vector<int> vTaskIDs = parserResult.getIndex();
	vector<string> vNewTitles = parserResult.getDescription();
	vector<string> vNewStartDates = parserResult.getStartDate();
	vector<string> vNewStartTimes = parserResult.getStartTime();
	vector<string> vNewEndDates = parserResult.getEndDate();
	vector<string> vNewEndTimes = parserResult.getEndTime();

	assert(vNewTitles.size() <= 1);
	assert(!vTaskIDs.empty());

	if (vEntryTypes[0] == "e") {
		entryType = event;
	}
	else if (vEntryTypes[0] == "t") {
		entryType = task;
	}

	taskID = vTaskIDs[0];
	
	if (!vNewTitles.empty()) {
		newTitle = vNewTitles[0];
	}
	if (!vNewStartDates.empty()) {
		newStartDate = createPTimeObject(vNewStartDates[0], "000000");
	}
	if (!vNewStartTimes.empty()) {
		newStartTime = createPTimeObject("00000000", vNewStartTimes[0]);
	}
	if (!vNewEndDates.empty()) {
		newEndDate = createPTimeObject(vNewEndDates[0], "000000");
	}
	if (!vNewEndTimes.empty()) {
		newEndTime = createPTimeObject("00000000", vNewEndTimes[0]);
	}

	editCommand = new EditCommand(entryType, taskID, newTitle, newStartDate, newStartTime, newEndDate, newEndTime);
	
	return editCommand;
}

Command * CommandBuilder::createDeleteCommand(ParserResult& parserResult)
{
	Command* deleteCommand;

	vector<string> vEntryTypes = parserResult.getEntryType();
	vector<int> vIndices = parserResult.getIndex();

	EntryType entryType;

	if (vEntryTypes[0] == "e") {
		entryType = event;
	}

	else if (vEntryTypes[0] == "t") {
		entryType = task;
	}

	int displayIndex = vIndices[0];

	deleteCommand = new DeleteCommand(entryType, displayIndex);
	return deleteCommand;
}

Command * CommandBuilder::createSearchCommand(ParserResult& parserResult)
{
	//create SearchCommand;
	Command* searchCommand;
	
	vector<string> keywords = parserResult.getDescription();
	searchCommand = new SearchCommand(keywords);
	return searchCommand;
		
}

Command * CommandBuilder::createShowCommand(ParserResult& parserResult)
{
	//create ShowCommand;
	Command * showCommand;
	ptime dateRequirement;

	string date;
	string time;

	vector<string> vDateRequirement = parserResult.getEndDate();
	vector<string> vTimeRequirement = parserResult.getEndTime();
	
	assert(!vDateRequirement.empty() || !vTimeRequirement.empty());

	if (vDateRequirement.empty()) {
		date = "000000000";
	}
	else {
		date = vDateRequirement[0];
	}

	if (vTimeRequirement.empty()) {
		time = "000000";
	}
	else {
		time = vTimeRequirement[0];
	}

	dateRequirement= createPTimeObject(date, time);
	showCommand = new ShowCommand(dateRequirement);
	
	return showCommand;
}
/*
Command * CommandBuilder::createHelpCommand(ParserResult& parserResult)
{
	//create HelpCommand;
	return nullptr;
}
*/
Command * CommandBuilder::createSaveCommand(ParserResult& parserResult)
{
	Command * saveCommand;
	vector<string> vSaveDirs;
	vSaveDirs = parserResult.getDescription();

	string saveDir = vSaveDirs[0];
	saveCommand = new SaveCommand(saveDir);

	return saveCommand;
}

CommandBuilder::CommandBuilder() {

}

Command* CommandBuilder::buildCommand(ParserResult& parserResult) {
	Command *cmd = nullptr;

	string commandType = parserResult.getUserCommand();

	if (commandType == COMMANDTYPE_ADD) {
		cmd = createAddCommand(parserResult);
	}
	
	else if (commandType == COMMANDTYPE_EDIT) {
		cmd = createEditCommand(parserResult);
	}

	else if (commandType == COMMANDTYPE_DELETE) {
		cmd = createDeleteCommand(parserResult);
	}

	else if (commandType == COMMANDTYPE_SEARCH) {
		cmd = createSearchCommand(parserResult);
	}

	else if (commandType == COMMANDTYPE_SHOW) {
		cmd = createShowCommand(parserResult);
	}
	
	else if (commandType == COMMANDTYPE_SAVE) {
		cmd = createSaveCommand(parserResult);
	}
/*
	else if (commandType == COMMANDTYPE_HELP) {
		cmd = createHelpCommand(parserResult);
	}
*/
	return cmd;
}

CommandBuilder::~CommandBuilder()
{
}

