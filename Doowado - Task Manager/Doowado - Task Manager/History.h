#pragma once

//@@author A0102794E

class Command;
#include <stack>
using namespace std;

class History
{
private:
	static stack<Command*> _commandStack;
public:

#ifdef TESTMODE
	static size_t getSize() {
		return _commandStack.size();
	}
#endif

	History();
	~History();

	static Command* getLastCommand();
	static void pushCommand(Command* cmd);
	static void empty();
};

