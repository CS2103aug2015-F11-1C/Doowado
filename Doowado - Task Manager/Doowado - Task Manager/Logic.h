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
	void updateDoneEvent();
	void updateClashEvent();
	bool isOverlapTime(ptime startTime1, ptime endTime1, ptime startTime2, ptime endTime2);

public:

#ifdef TESTMODE
	Storage* getStorage() {
		return _storage;
	}
#endif

	Logic();
	~Logic();
	void processCommand(string);
	void initialiseProgram();
	Display* getDisplay();
};

