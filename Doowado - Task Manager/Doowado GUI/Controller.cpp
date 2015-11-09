//This file acts as a main for the program

#include "CommandBuilder.h"
#include "Storage.h"
#include "Parser.h"
#include "UserInterface.h"
#include "Display.h"
#include "Event.h"
#include "Task.h"
#include "Controller.h"
#include <string>

using namespace std;

Controller::Controller (void){
	UserInterface* UI= new UserInterface;
	Storage* LocalStorage = new Storage;
	Command* cmd = nullptr;
	Parser* parser = new Parser();
	Display* displayList = new Display;
	CommandBuilder* builder = new CommandBuilder();
}


void Controller::executeCommand (string input) {
	while (input != "exit") {
		ParserResult* parserResult = new ParserResult();
		*parserResult = parser->parse(input);
		cmd = builder->buildCommand(*parserResult);
		cmd->execute(LocalStorage, displayList);
	}
}

void Controller::getDisplayList (vector<Event>& EventList, vector<Task>& TaskList) {
	EventList = displayList->getEventList;
	TaskList = displayList->getTaskList;
}



void Controller::getFeedback() {

}
