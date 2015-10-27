#pragma once
#include<vector>
#include<assert.h>
#include"Command.h"
#include"ParserResult.h"

using namespace std;

const string COMMANDTYPE_ADD = "add";
const string COMMANDTYPE_EDIT = "edit";
const string COMMANDTYPE_DELETE = "delete";
const string COMMANDTYPE_SEARCH = "search";
const string COMMANDTYPE_SHOW = "show";
const string COMMANDTYPE_HELP = "help";
const string COMMANDTYPE_SAVE = "save";

//enum EntryType {event, task, floatingTask};
enum TypeOfEdit {	editTitle,
					editStartDate,
					editStartTime,
					editStartDateAndTime,
					editEndDate,
					editEndTime,
					editEndDateAndTime,
					editStartAndEndDate,
					editStartAndEndTime,
					editDueTime};

class CommandBuilder {
	
	private:
//		EntryType checkEntryType(ParserResult&);
		ptime createPTimeObject(string, string);
		TypeOfEdit checkEditType(vector<string>, vector<string> , vector<string>, vector<string>, vector<string>);
	
		Command* createAddCommand(ParserResult&);
		Command* createEditCommand(ParserResult&);
		Command* createDeleteCommand(ParserResult&);
		Command* createSearchCommand(ParserResult&);
		Command* createShowCommand(ParserResult&);
//		Command* createHelpCommand(ParserResult&);
//		Command* createSaveCommand(ParserResult&);

	public:
		CommandBuilder();
		Command* buildCommand(ParserResult &);

		~CommandBuilder();
};            

