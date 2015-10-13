//This file acts as a main for the program

#include "CommandBuilder.h"
#include "Storage.h"
#include "Parser.h"
#include "UserInterface.h"
#include "Display.h"

int main(int argc, char* argv[]) {

	UserInterface UI;
	Storage LocalStorage(argv[1]);
	CommandBuilder *builder;
	Command *cmd = nullptr;
	Parser parser;
	string input;
	static ptime currentTime(second_clock::local_time());
	static Display displayList;

	LocalStorage.loadFromFile();
	LocalStorage.saveToFile();
	UI.updateDefaultDisplay(&LocalStorage);
	UI.printWelcome();
	UI.printList();

	getline(cin, input);
	
	while (input != "exit") {

		vector<string> parsedInput;

		parser.parse(input, parsedInput);

		builder = new CommandBuilder(parsedInput);
		cmd = builder->buildCommand();

		cmd->execute(&LocalStorage, &displayList);

		UI.updateDefaultDisplay(&LocalStorage);
		UI.printList();
		getline(cin, input);
	} 

	LocalStorage.saveToFile();

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
>>>>>>> 8cff09cb14f5ee9a33684c91368e4515f86d6425
	return 0;
}
*/