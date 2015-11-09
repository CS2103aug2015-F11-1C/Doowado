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
	std::vector<std::string> vStartDate = parserResult.getStartDate();
	std::vector<std::string> vStartTime = parserResult.getStartTime();
	std::vector<std::string> vEndDate = parserResult.getEndDate();
	std::vector<std::string> vEndTime = parserResult.getEndTime();

	if (description.empty()) {
		throw CmdBuilderException(EXCEPTION_NO_TITLE);
	}
	if (vStartDate.empty() && !vStartTime.empty()) {
		throw CmdBuilderException(EXCEPTION_TIME_NO_DATE);
	}
	if (vEndDate.empty() && !vEndTime.empty()) {
		throw CmdBuilderException(EXCEPTION_TIME_NO_DATE);
	}

	entryTitle = description[0];
	
	if (!vStartDate.empty()) {
		stringStartDate = vStartDate[0];
		date d(from_undelimited_string(stringStartDate));
		entryStartDate = d;
	}

	if (!vStartTime.empty()) {
		stringStartTime = vStartTime[0];
		time_duration td(duration_from_string(stringStartTime));
		entryStartTime = td;
	}

	if (!vEndDate.empty()) {
		stringEndDate = vEndDate[0];
		date d(from_undelimited_string(stringEndDate));
		entryEndDate = d;
	}

	if (!vEndTime.empty()) {
		stringEndTime = vEndTime[0];
		time_duration td(duration_from_string(stringEndTime));
		entryEndTime = td;
	}
	else {
		time_duration td(duration_from_string(STRING_END_TIME_INITIALISE));
		entryEndTime = td;
	}

	ptime entryStartPtime(entryStartDate, entryStartTime);
	ptime entryEndPtime(entryEndDate, entryEndTime);

	if (!entryStartPtime.is_not_a_date_time() && !entryEndPtime.is_not_a_date_time()) {
		if (entryStartPtime > entryEndPtime) {
			LOG(INFO) << "CmdBuilderException startTime > endTime";
			LOG(INFO) << "CmdBuilderException startTime: " << entryStartPtime;
			LOG(INFO) << "CmdBuilderException endTime: " << entryEndPtime;
			throw CmdBuilderException(EXCEPTION_START_TIME_GREATER_END_TIME);
		}
	}

	addCommand = new AddCommand(entryTitle, entryStartPtime, entryEndPtime);

	return addCommand;
}

Command * CommandBuilder::createEditCommand(ParserResult &parserResult)
{
	//exception for entry like edit 1 instead of T1
	Command* editCommand;
	
	EntryType entryType;
	int taskID =0;
	std::string newTitle = "";
	date newStartDate(not_a_date_time);
	time_duration newStartTime(not_a_date_time);
	date newEndDate(not_a_date_time);
	time_duration newEndTime(not_a_date_time);
	 
	std::vector<std::string> vEntryTypes = parserResult.getEntryType();
	
	if (vEntryTypes[0] == "e") {
		entryType = event;
	}
	else if (vEntryTypes[0] == "t") {
		entryType = task;
	}
	//exception if it is not "e" or "t"
	std::vector<int> vTaskIDs = parserResult.getIndex();
	taskID = vTaskIDs[0] - 1;

	std::vector<std::string> vNewTitles = parserResult.getDescription();
	
	if(!vNewTitles.empty()) {
		newTitle = vNewTitles[0];
	}
	
	std::vector<std::string> vNewStartDates = parserResult.getStartDate();
	
	if (!vNewStartDates.empty()) {
		std::string stringStartDate = vNewStartDates[0];
		if (stringStartDate == "null") {
			date d(neg_infin);
			newStartDate = d;
		}
		else {
			date d(from_undelimited_string(stringStartDate));
			newStartDate = d;
		}
	}

	std::vector<std::string> vNewStartTimes = parserResult.getStartTime();
	if (!vNewStartTimes.empty()) {
		std::string stringStartTime = vNewStartTimes[0];
		if (stringStartTime == "null") {
			time_duration td(neg_infin);
			newStartTime = td;
		}
		else {
			time_duration td(duration_from_string(stringStartTime));
			newStartTime = td;
		}
	}
	std::vector<std::string> vNewEndDates = parserResult.getEndDate();
	if (!vNewEndDates.empty()) {
		std::string stringEndDate = vNewEndDates[0];
		if (stringEndDate == "null") {
			date d(neg_infin);
			newEndDate = d;
		}
		else {
			date d(from_undelimited_string(stringEndDate));
			newEndDate = d;
		}
	}
	std::vector<std::string> vNewEndTimes = parserResult.getEndTime();
	if (!vNewEndTimes.empty()) {
		std::string stringEndTime = vNewEndTimes[0];
		if (stringEndTime == "null") {
			time_duration td(neg_infin);
			newEndTime = td;
		}
		else {
			time_duration td(duration_from_string(stringEndTime));
			newEndTime = td;
		}
	}

	LOG(INFO) << "CmdBuilder newStartDate: " << to_simple_string(newStartDate);
	LOG(INFO) << "CmdBuilder newStartTime: " << to_simple_string(newStartTime);
	LOG(INFO) << "CmdBuilder newEndDate: " << to_simple_string(newEndDate);
	LOG(INFO) << "CmdBuilder newEndTime: " << to_simple_string(newEndTime);

	editCommand = new EditCommand(entryType, taskID, newTitle, newStartDate, newStartTime, newEndDate, newEndTime);
	
	return editCommand;
}

Command * CommandBuilder::createDeleteCommand(ParserResult& parserResult)
{
	Command* deleteCommand;

	std::vector<std::string> vEntryTypes = parserResult.getEntryType();
	std::vector<int> vIndices = parserResult.getIndex();

	if (vEntryTypes.empty() || vIndices.empty()) {
		throw CmdBuilderException(EXCEPTION_INVALID_DELETE);
	}

	EntryType entryType;

	if (vEntryTypes[0] == "e") {
		entryType = event;
	}

	else if (vEntryTypes[0] == "t") {
		entryType = task;
	}
	
	else {
		throw CmdBuilderException(EXCEPTION_INVALID_ENTRY_TYPE_AT_INDEX);
	}

	int displayIndex = vIndices[0];

	int taskID = displayIndex - 1;

	deleteCommand = new DeleteCommand(entryType, taskID);
	return deleteCommand;
}

Command * CommandBuilder::createSearchCommand(ParserResult& parserResult)
{
	//create SearchCommand;
	Command* searchCommand;
	
	std::vector<std::string> keywords = parserResult.getDescription();

	if (keywords.empty()) {
		throw CmdBuilderException(EXCEPTION_INVALID_SEARCH);
	}
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
		showType = showByDate;
	}
	else {
		throw CmdBuilderException(EXCEPTION_INVALID_SHOW);
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
		else {
			throw CmdBuilderException(EXCEPTION_INVALID_SHOW_STATUS);
		}
	}
	
	else if (showType == showByDate) {
		stringEndDate = vEndDateRequirement[0];
		date endDate(from_undelimited_string(stringEndDate));
		if (endDate.is_not_a_date()) {
			throw CmdBuilderException(EXCEPTION_INVALID_TIME);
		}
		showCommand = new ShowCommand(endDate);
	}

	else if (showType == showByRangeOfDate) {
		stringStartDate = vStartDateRequirement[0];
		stringEndDate = vEndDateRequirement[0];
		date startDate(from_undelimited_string(stringStartDate));
		date endDate(from_undelimited_string(stringEndDate));
		
		if (startDate.is_not_a_date() || endDate.is_not_a_date()) {
			throw CmdBuilderException(EXCEPTION_INVALID_TIME);
		}
		showCommand = new ShowCommand(startDate, endDate);
	}

	return showCommand;
}

Command * CommandBuilder::createSaveCommand(ParserResult& parserResult)
{
	Command * saveCommand;
	std::vector<std::string> vSaveDirs;
	vSaveDirs = parserResult.getDescription();

	if (vSaveDirs.empty()) {
		throw CmdBuilderException(EXCEPTION_INVALID_SAVE);
	}
	std::string saveDir = vSaveDirs[0];
	saveCommand = new SaveCommand(saveDir);

	return saveCommand;
}

Command * CommandBuilder::createMarkDoneCommand(ParserResult &parserResult)
{
	Command* markDoneCommand;

	std::vector<std::string> vEntryTypes = parserResult.getEntryType();
	std::vector<int> vIndices = parserResult.getIndex();

	if (vEntryTypes.empty() || vIndices.empty()) {
		throw CmdBuilderException(EXCEPTION_INVALID_MARKDONE);
	}
	EntryType entryType;

	if (vEntryTypes[0] == "e") {
		entryType = event;
	}

	else if (vEntryTypes[0] == "t") {
		entryType = task;
	}
	else {
		throw CmdBuilderException(EXCEPTION_INVALID_ENTRY_TYPE_AT_INDEX);
	}

	int displayIndex = vIndices[0];
	int taskID = displayIndex - 1;

	markDoneCommand = new MarkDoneCommand(entryType, taskID);
	return markDoneCommand;
}

Command * CommandBuilder::createUndoCommand(ParserResult & parserResult)
{
	Command * undoCommand;
	undoCommand = new UndoCommand();
	return undoCommand;
}

CommandBuilder::CommandBuilder() {

}

Command* CommandBuilder::buildCommand(ParserResult& parserResult) {
	Command *cmd = nullptr;

	std::string commandType = parserResult.getUserCommand();

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
	else {
		throw CmdBuilderException(EXCEPTION_INVALID_COMMANDTYPE);
	}
	return cmd;
}

CommandBuilder::~CommandBuilder()
{
}

