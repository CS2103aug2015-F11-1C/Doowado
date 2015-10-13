#pragma once
#include <string>
#include <vector>
#include "CommandResult.h"

using namespace std;

class AddCommandResult :
	public CommandResult
{
private:
	string _commandType;
	vector<string>* _commandFeedback;

public:
	AddCommandResult();
	~AddCommandResult();
	vector<string>* getFeedback();
};

