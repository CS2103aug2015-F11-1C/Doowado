#pragma once
class Command;
#include <stack>
using namespace std;

class History
{
private:
	stack<Command*> _commandStack;
public:
	History();
	~History();

	Command* getLastCommand();
	void pushCommand(Command* cmd);
};

