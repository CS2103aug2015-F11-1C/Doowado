#pragma once
#include<vector>
#include<assert.h>
#include<exception>
#include"Command.h"
#include"ParserResult.h"
#include"CmdBuilderException.h"

using namespace std;

const string EXCEPTION_INVALID_COMMANDTYPE = "Invalid command type. Please insert add/edit/delete/search/show/help/save/done/undo";
const string EXCEPTION_START_TIME_GREATER_END_TIME = "Invalid! Start Time is later than End Time.";
const string EXCEPTION_TIME_NO_DATE = "Invalid! Entry has no date.";
const string EXCEPTION_NO_TITLE = "Invalid! Entry has no title";
const string EXCEPTION_INVALID_ENTRY_TYPE_AT_INDEX = "Invalid entry type at index!";
const string EXCEPTION_INVALID_DELETE = "Invalid input for delete command!";
const string EXCEPTION_INVALID_SEARCH = "Invalid input for search command!";
const string EXCEPTION_INVALID_SHOW = "Invalid input for show command!";
const string EXCEPTION_INVALID_SHOW_STATUS = "Invalid input for show status!";
const string EXCEPTION_INVALID_TIME = "Invalid time input!";
const string EXCEPTION_INVALID_SAVE = "Invalid input for save command!";
const string EXCEPTION_INVALID_MARKDONE = "Invalid input for mark done command!";


const string COMMANDTYPE_ADD = "add";
const string COMMANDTYPE_EDIT = "edit";
const string COMMANDTYPE_DELETE = "delete";
const string COMMANDTYPE_SEARCH = "search";
const string COMMANDTYPE_SHOW = "show";
const string COMMANDTYPE_HELP = "help";
const string COMMANDTYPE_SAVE = "save";
const string COMMANDTYPE_MARK_DONE = "done";
const string COMMANDTYPE_UNDO = "undo";


class CommandBuilder {
	
	private:	
		Command* createAddCommand(ParserResult&);
		Command* createEditCommand(ParserResult&);
		Command* createDeleteCommand(ParserResult&);
		Command* createSearchCommand(ParserResult&);
		Command* createShowCommand(ParserResult&);
		Command* createSaveCommand(ParserResult&);
		Command* createMarkDoneCommand(ParserResult&);
		Command* createUndoCommand(ParserResult&);


	public:
		CommandBuilder();
		Command* buildCommand(ParserResult &);

		~CommandBuilder();
};            

