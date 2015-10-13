#pragma once
#include<vector>
#include<string>

using namespace std;

class CommandResult
{
public:
	CommandResult();
	~CommandResult();
	virtual vector<string>* getFeedback();
};

