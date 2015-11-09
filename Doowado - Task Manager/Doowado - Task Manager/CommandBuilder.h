//@@author A0114137R

#pragma once
#include<vector>
#include<assert.h>
#include<exception>
#include"Command.h"
#include"ParserResult.h"
#include"CmdBuilderException.h"
#include "easylogging++.h"

using namespace std;

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

		int rebaseToZero(int displayIndex);

	public:
		CommandBuilder();
		Command* buildCommand(ParserResult &);

		~CommandBuilder();
};            

