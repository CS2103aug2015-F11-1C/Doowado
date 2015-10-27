#pragma once
class Command;
#include <stack>
using namespace std;

class History
{
private:
	static stack<Command*> _commandStack;
public:
	History();
	~History();

	static Command* getLastCommand();
	static void pushCommand(Command* cmd);
};

