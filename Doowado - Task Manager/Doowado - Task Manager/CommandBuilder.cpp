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
	
	date entryStartDate;
	time_duration entryStartTime;
	date entryEndDate;
	time_duration entryEndTime;

	std::string stringStartDate;
	std::string stringStartTime;
	std::string stringEndDate;
	std::string stringEndTime;

	std::vector<std::string> description = parserResult.getDescription();
	entryTitle = description[0];

	std::vector<std::string> vStartDate = parserResult.getStartDate();
	if (!vStartDate.empty()) {
		stringStartDate = vStartDate[0];
		date d(from_undelimited_string(stringStartDate));
		entryStartDate = d;
	}
	
	std::vector<std::string> vStartTime = parserResult.getStartTime();
	if (!vStartTime.empty()) {
		stringStartTime = vStartTime[0];
		time_duration td(duration_from_string(stringStartTime));
		entryStartTime = td;
	}

	std::vector<std::string> vEndDate = parserResult.getEndDate();
	if (!vEndDate.empty()) {
		stringEndDate = vEndDate[0];
		date d(from_undelimited_string(stringEndDate));
		entryEndDate = d;
	}

	std::vector<std::string> vEndTime = parserResult.getEndTime();
	if (!vEndTime.empty()) {
		stringEndTime = vEndTime[0];
		time_duration td(duration_from_string(stringEndTime));
		entryEndTime = td;
	}


	//assert(startDate.size() == startTime.size());
	//assert(endDate.size() == endTime.size());

	ptime entryStartPtime(entryStartDate, entryStartTime);
	ptime entryEndPtime(entryEndDate, entryEndTime);
	addCommand = new AddCommand(entryTitle, entryStartPtime, entryEndPtime);

	return addCommand;
}

Command * CommandBuilder::createEditCommand(ParserResult &parserResult)
{
	//exception for entry like edit 1 instead of T1
	Command* editCommand;
	
	EntryType entryType;
	int taskID =0;
	string newTitle = "";
	date newStartDate(not_a_date_time);
	time_duration newStartTime(not_a_date_time);
	date newEndDate(not_a_date_time);
	time_duration newEndTime(not_a_date_time);
	 
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

	cout << "newStartDate: " << to_simple_string(newStartDate);
	cout << "newStartTime: " << to_simple_string(newStartTime);
	cout << "newEndDate: " << to_simple_string(newEndDate);
	cout << "newEndTime: " << to_simple_string(newEndTime);

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
	Command * showCommand = NULL;
	showType showType;

	date dateRequirement;
	std::string stringEntryStatus;

	std::string stringStartDate;
	std::string stringEndDate;
	
	std::vector<std::string> vStartDateRequirement = parserResult.getStartDate();
	std::vector<std::string> vEndDateRequirement = parserResult.getEndDate();
	std::vector<std::string> vEntryStatus = parserResult.getDescription();

	if (!vEntryStatus.empty()) {
		showType = showByStatus;
	}
	else if (!vStartDateRequirement.empty() && !vEndDateRequirement.empty()) {
		showType = showByRangeOfDate;
	}
	else if (!vEndDateRequirement.empty()) {
		showType = showByRangeOfDate;
	}

	if (showType == showByStatus) {
		stringEntryStatus = vEntryStatus[0];

		if (stringEntryStatus == ENTRY_STATUS_COMPLETED) {
			showCommand = new ShowCommand(completed);
		}
		else if (stringEntryStatus == ENTRY_STATUS_INCOMPLETE) {
			showCommand = new ShowCommand(incomplete);
		}
		else if (stringEntryStatus == ENTRY_STATUS_OVERDUE) {
			showCommand = new ShowCommand(overdue);
		}
		else if (stringEntryStatus == ENTRY_STATUS_INTIME) {
			showCommand = new ShowCommand(intime);
		}
	}
	
	else if (showType == showByDate) {
		stringEndDate = vEndDateRequirement[0];
		date endDate(from_undelimited_string(stringEndDate));
		showCommand = new ShowCommand(endDate);
	}

	else if (showType == showByRangeOfDate) {
		stringStartDate = vStartDateRequirement[0];
		stringEndDate = vEndDateRequirement[0];
		date startDate(from_undelimited_string(stringStartDate));
		date endDate(from_undelimited_string(stringEndDate));
		showCommand = new ShowCommand(startDate, endDate);
	}

	return showCommand;
}

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

	int taskIndex = vIndices[0] - 1;

	markDoneCommand = new MarkDoneCommand(entryType, taskIndex);
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

	else if (commandType == COMMANDTYPE_MARK_DONE) {
		cmd = createMarkDoneCommand(parserResult);
	}
	return cmd;
}

CommandBuilder::~CommandBuilder()
{
}

