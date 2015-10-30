//This file acts as a main for the program

#include "CommandBuilder.h"
#include "Storage.h"
#include "Parser.h"
#include "UserInterface.h"
#include "Display.h"
#include "DeleteCommand.h"
#include "Logic.h"
#include "History.h"

int main() {
	Logic * logic = new Logic;
	string input;
	UserInterface UI;

	logic->initialiseProgram();
	Display* displayList = logic->getDisplay();
	UI.updateDisplay(*displayList);

	getline(cin, input);

	while (input != "exit") {
		logic->processCommand(input);
		displayList = logic->getDisplay();
		UI.updateDisplay(*displayList);

		getline(cin, input);
	}

	/*
	UserInterface UI;
	Storage LocalStorage;
	Command *cmd = nullptr;
	Parser* parser = new Parser(); 
	string input; 
	static ptime currentTime(second_clock::local_time());
	Display displayList;
	CommandBuilder* builder = new CommandBuilder();


	LocalStorage.loadFromFile();
	LocalStorage.saveToFile();

	vector<Entry*> eventDefaultList;
	vector<Entry*> taskDefaultList;

	UI.printWelcome();

	LocalStorage.retrieveByDate(currentTime, eventDefaultList, taskDefaultList);
	displayList.updateDisplayEventList(eventDefaultList);
	displayList.updateDisplayTaskList(taskDefaultList);
	
	UI.updateDisplay(displayList);

	//UI.updateDefaultDisplay(&LocalStorage);

	getline(cin, input);

	while (input != "exit") {
		ParserResult parserResult;
		parserResult = parser->parse(input);
		
		cmd = builder->buildCommand(parserResult);
		cmd->execute(&LocalStorage, &displayList);

		//UI.updateDefaultDisplay(&LocalStorage);
		
		//UI.printList(displayList); 
		
		UI.updateDisplay(displayList);
		
		getline(cin, input);

//		delete parserResult;
	} 

	LocalStorage.saveToFile();
*/
	return 0;
}
/*
	date d1(2015,10,4);
	ptime t1(d1, hours(5) + minutes(30));
	ptime t2(d1, hours(6) + minutes(30));
	Storage data;

	Command* cmd;
	Command* cmd2;
	Command* cmd3;

	cmd = new AddCommand("Read Harry Potter");
	cmd2 = new AddCommand("Tea Time", t1);
	cmd3 = new AddCommand("Rest", t1, t2);
	cmd->execute(&data);
	cmd2->execute(&data);
	cmd3->execute(&data);
	return 0;
}
*/