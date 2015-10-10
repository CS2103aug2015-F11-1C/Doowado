#include "UserInterface.h"

const string UserInterface::MESSAGE_ADDED = "Added: ";
const string UserInterface::MESSAGE_TIME = "Time: ";
const string UserInterface::MESSAGE_WRONG = "Oops.It seems that something is wrong with your command.";
const string UserInterface::MESSAGE_FOUNDNOTHING = "Sorry. No results were found. Please try again.";
const string UserInterface::MESSAGE_DELETED = "Deleted£º ";
const string UserInterface::MESSAGE_WELCOME_1 = "Welcome to DOOWADO!";
const string UserInterface::MESSAGE_WELCOME_2 = "You have following events and tasks for today: ";
const string UserInterface::MESSAGE_UPDATED = "Updated: " ;
const string UserInterface::MESSAGE_SAVED = " File was saved to: ";
const string UserInterface::TASK_LIST = "Tasks: ";
const string UserInterface::EVENT_LIST = "Events: ";
const string UserInterface::WRONG = "wrong";

void UserInterface::printWelcome() {
	cout << MESSAGE_WELCOME_1 << endl << MESSAGE_WELCOME_2 << endl;
}

void UserInterface::getCommand(string &command) {
	getline(cin, command);
}

//To print the feedbacks
void UserInterface::showFeedback(vector<string>& feedback, bool isSuccessful, string _commandType) {
	if (!isSuccessful) {
		cout << endl;
		cout << MESSAGE_WRONG << endl;
	}
	else if (_commandType == "add") {
			cout << endl;
			cout << MESSAGE_ADDED << endl << feedback[0] << endl;
			cout << MESSAGE_TIME << feedback[1] << ", " << feedback[2] << endl;
	}
	else if (_commandType == "delete") {
		cout << endl;
		cout << MESSAGE_DELETED << endl << feedback[0] << feedback [1] << endl;
	}
	else if (_commandType == "update") {
		cout << endl;
		cout << MESSAGE_UPDATED << feedback[0] << feedback[1] << endl;
	}
	else if (_commandType == "save") {
		cout << endl;
		cout << MESSAGE_SAVED << feedback[0] << endl;
	}
}

//To print the list of events and tasks
void UserInterface::printList() {
	if (!EventList.empty()) {
		cout << endl;
		cout << EVENT_LIST << endl;
		for (int i = 0; i < EventList.size(); i++) {
			cout << "E" << i + 1 << ": ";
			EventList[i]->printEvent();
			cout << endl;
		}
	}
	if (!TaskList.empty()) {
		cout << endl;
		cout << TASK_LIST << endl;
		for (int i = 0; i < TaskList.size(); i++) {
			cout << "T" << i + 1 << ": "; 
			TaskList[i]->printTask();
			cout << endl;
		}
	}
	if (!FTaskList.empty()) {
		cout << endl;
		cout << TASK_LIST << endl;
		for (int i = 0; i < FTaskList.size(); i++) {
			cout << "T" << TaskList.size() + i + 1 << ": "; 
			FTaskList[i]->printFTask();
			cout << endl;
		}
	}
	if (EventList.empty() && TaskList.empty() && FTaskList.empty()) {
		cout << MESSAGE_FOUNDNOTHING << endl;
	}
}

// For /delete and /update to get the required entry from the screen. 
/*
void UserInterface::getEntry(string input, string& output) {
	if (input[0] == 'E') {
		int index = convertCharToInt(input[1]);
		if (index < EventList.size())
			output = EventList[index];
		else {
			cout << MESSAGE_WRONG;
			output = WRONG;
		}
	}
	else if (input[0] == 'T') {
		int index = convertCharToInt(input[1]);
		if (index < TaskList.size())
			 output = TaskList[index];
		else {
			cout << MESSAGE_WRONG;
			output = WRONG;
		}
	}
	else {
		cout << MESSAGE_WRONG;
		output = WRONG;
	}
}
*/

int UserInterface::convertCharToInt(char input) {
	return input - '0';
}

void UserInterface::updateDefaultDisplay(Storage *LocalData) {
	LocalData->displayDefault(&EventList, &TaskList, &FTaskList);
}