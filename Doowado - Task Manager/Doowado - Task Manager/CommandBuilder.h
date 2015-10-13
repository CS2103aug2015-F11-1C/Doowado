#pragma once
#include<vector>
#include"Command.h"

using namespace std;

const string COMMANDTYPE_ADD = "add";
const string COMMANDTYPE_EDIT_TITLE = "editTitle";
const string COMMANDTYPE_EDIT_TIME = "editTime";
const string COMMANDTYPE_DELETE = "delete";
const string COMMANDTYPE_SEARCH = "search";
const string COMMANDTYPE_SHOW = "show";
const string COMMANDTYPE_HELP = "help";
const string COMMANDTYPE_SAVE = "save";

const int INDEX_COMMANDTYPE = 0;
const int INDEX_ADD_TITLE = 1;
const int INDEX_ADD_TIME_1 = 2;
const int INDEX_ADD_TIME_2 = 3;

const int INDEX_EDIT_ENTRY_TYPE = 1;
const int INDEX_EDIT_DISPLAY_INDEX = 2;
const int INDEX_EDIT_NEW_TITLE =  3;
const int INDEX_EDIT_NEW_START_TIME = 3;
const int INDEX_EDIT_NEW_END_TIME = 4;

const int INDEX_DELETE_DISPLAY_INDEX = 1;

const int VECTOR_SIZE_EVENT = 4;
const int VECTOR_SIZE_TASK = 3;
const int VECTOR_SIZE_FLOATING_TASK = 2;

class CommandBuilder {
	private:
		vector<string> _vInputs;

		bool isEvent();
		bool isTask();
		bool isFloatingTask();

		Command* createAddCommand();
		Command* createEventAddCommand();
		Command* createTaskAddCommand();
		Command* createFTaskAddCommand();
		Command* createEditTitleCommand();
		Command* createEditTimeCommand();
		Command* createDeleteCommand();
		Command* createSearchCommand();
		Command* createShowCommand();
		Command* createHelpCommand();
		Command* createSaveCommand();

	public:
		CommandBuilder(vector<string>&);
		Command* buildCommand();

		~CommandBuilder();
};

