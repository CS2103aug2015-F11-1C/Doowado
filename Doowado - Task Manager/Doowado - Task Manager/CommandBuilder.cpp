#include "CommandBuilder.h"
#include "Command.h"
#include "AddCommand.h"
#include "EditCommand.h"
#include "DeleteCommand.h"
#include "ShowCommand.h"
#include "SearchCommand.h"
#include "SaveCommand.h"
#include "MarkDoneCommand.h"
#include "UndoCommand.h"

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
		date startDate(from_undelimited_string(entryStartDate));
		time_duration startTime(duration_from_string(entryStartTime));
		ptime s(startDate, startTime);
		entryStartPtime = s;

		string entryEndDate = endDate[0];
		string entryEndTime = endTime[0];
		date endDate(from_undelimited_string(entryEndDate));
		time_duration endTime(duration_from_string(entryEndTime));
		ptime e(endDate, endTime);
		entryEndPtime = e;
	}

	else if (!endDate.empty() && !endTime.empty()) {
		string entryEndDate = endDate[0];
		string entryEndTime = endTime[0];
		date endDate(from_undelimited_string(entryEndDate));
		time_duration endTime(duration_from_string(entryEndTime));
		ptime e(endDate, endTime);
		entryEndPtime = e;
	}

	addCommand = new AddCommand(entryTitle, entryStartPtime, entryEndPtime, entryDuePtime);

	return addCommand;
}

Command * CommandBuilder::createEditCommand(ParserResult &parserResult)
{
	//exception for entry like edit 1 instead of T1
	Command* editCommand;
	
	EntryType entryType;
	int taskID =0;
	string newTitle = "";
	date newStartDate;
	time_duration newStartTime;
	date newEndDate;
	time_duration newEndTime;
	 
	vector<string> vEntryTypes = parserResult.getEntryType();
	
	if (vEntryTypes[0] == "e") {
		entryType = event;
	}
	else if (vEntryTypes[0] == "t") {
		entryType = task;
	}
	//exception if it is not "e" or "t"
	vector<int> vTaskIDs = parserResult.getIndex();
	taskID = vTaskIDs[0] - 1;

	vector<string> vNewTitles = parserResult.getDescription();
	
	if(!vNewTitles.empty()) {
		newTitle = vNewTitles[0];
	}
	
	vector<string> vNewStartDates = parserResult.getStartDate();
	
	if (!vNewStartDates.empty()) {
		string stringStartDate = vNewStartDates[0];
		if (stringStartDate == "null") {
			date d(neg_infin);
			newStartDate = d;
		}
		else {
			date d(from_undelimited_string(stringStartDate));
			newStartDate = d;
		}
	}

	vector<string> vNewStartTimes = parserResult.getStartTime();
	if (!vNewStartTimes.empty()) {
		string stringStartTime = vNewStartTimes[0];
		if (stringStartTime == "null") {
			time_duration td(neg_infin);
			newStartTime = td;
		}
		else {
			time_duration td(duration_from_string(stringStartTime));
			//time_duration td(duration_from_string("01:01"));
			newStartTime = td;
		}
	}
	vector<string> vNewEndDates = parserResult.getEndDate();
	if (!vNewEndDates.empty()) {
		string stringEndDate = vNewEndDates[0];
		if (stringEndDate == "null") {
			date d(neg_infin);
			newEndDate = d;
		}
		else {
			date d(from_undelimited_string(stringEndDate));
			newEndDate = d;
		}
	}
	vector<string> vNewEndTimes = parserResult.getEndTime();
	if (!vNewEndTimes.empty()) {
		string stringEndTime = vNewEndTimes[0];
		if (stringEndTime == "null") {
			time_duration td(neg_infin);
			newEndTime = td;
		}
		else {
			time_duration td(duration_from_string(stringEndTime));
			newEndTime = td;
		}
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

	int displayIndex = vIndices[0] - 1;

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
	date dateRequirement;
	time_duration timeRequirement;

	string stringDate;
	string stringTime;
	
	vector<string> vDateRequirement = parserResult.getEndDate();
	vector<string> vTimeRequirement = parserResult.getEndTime();
	
	assert(!vDateRequirement.empty() || !vTimeRequirement.empty());

	if (vDateRequirement.empty()) {
		//throw exception
	}
	else {
		stringDate = vDateRequirement[0];
		date d(from_undelimited_string(stringDate));
		dateRequirement = d;
	}
	/*
	if (vTimeRequirement.empty()) {
		time_duration td(not_a_date_time);
		timeRequirement =
	}
	else {
		time = vTimeRequirement[0];
	}

	dateRequirement= createPTimeObject(date, time);
	*/
	ptime ptimeRequirement(dateRequirement, timeRequirement);
	showCommand = new ShowCommand(ptimeRequirement);
	
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

Command * CommandBuilder::createMarkDoneCommand(ParserResult &parserResult)
{
	Command* markDoneCommand;

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

	markDoneCommand = new MarkDoneCommand(entryType, displayIndex);
	return markDoneCommand;
}

Command * CommandBuilder::createUndoCommand(ParserResult &)
{
	Command * undoCommand;
	undoCommand = new UndoCommand();
	return undoCommand;
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
	else if (commandType == COMMANDTYPE_UNDO) {
		cmd = createUndoCommand(parserResult);
	}
/*
	else if (commandType == COMMANDTYPE_HELP) {
		cmd = createHelpCommand(parserResult);
	}
*/
	else if (commandType == COMMANDTYPE_MARK_DONE) {
		cmd = createMarkDoneCommand(parserResult);
	}
	return cmd;
}

CommandBuilder::~CommandBuilder()
{
}

