#pragma once

#include "Storage.h"
#include "CommandBuilder.h"
#include "Command.h"
#include "Parser.h"
#include "Display.h"

static ptime currentTime(second_clock::local_time());

using namespace std;

class Logic
{
private:
	Storage* _storage;
	CommandBuilder* _cmdBuilder;
	Parser* _parser;
	Display* _display;
	void updateOverdueTask();

public:
	Logic();
	~Logic();
	void processCommand(string);
	void initialiseProgram();
	Display* getDisplay();
};

