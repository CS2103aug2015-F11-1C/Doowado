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
		try {
			logic->processCommand(input);
			displayList = logic->getDisplay();
			UI.updateDisplay(*displayList);
		}
		catch (CmdBuilderException & e) {
			cout << "catch exception in controller: " << e.getMessage() << endl;
		}
		getline(cin, input);
	}
	return 0;
}
