#pragma once

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iomanip>
#include "CommandBuilder.h"
#include "Storage.h"
#include "Parser.h"
#include "UserInterface.h"
#include "Display.h"


class Controller {
private:
	UserInterface* UI;
	Storage* LocalStorage;
	Command* cmd = nullptr;
	Parser* parser;
	Display* displayList;
	CommandBuilder* builder = new CommandBuilder();


public:
	Controller(void);
	~Controller(void);
	
	
	string _input;

	void executeCommand(string input);

	void getDisplayList(vector<Event>&,vector<Task>&);

	void getFeedback();

};