#pragma once
#include<vector>
#include"Command.h"

using namespace std;

const string COMMANDTYPE_ADD = "add";
const string COMMANDTYPE_EDIT_TITLE = "editTitle";
const string COMMANDTYPE_EDIT_TIME = "editTime";
const string COMMANDTYPE_DELETE = "delete";
const string COMMANDTYPE_SAVE = "save";

const int INDEX_COMMANDTYPE = 0;
const int INDEX_TITLE = 1;
const int INDEX_TIME_1 = 2;
const int INDEX_TIME_2 = 3;

const int VECTOR_SIZE_EVENT = 4;
const int VECTOR_SIZE_TASK = 3;
const int VECTOR_SIZE_FLOATING_TASK = 2;

class CommandBuilder {
	private:
		vector<string> _vInputs;

	public:
		CommandBuilder(vector<string>&);
		Command* buildCommand();
		~CommandBuilder();
};

