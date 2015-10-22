#include "UserInterface.h"

string UserInterface::getCommand() {
	string userCommand;
	getline(cin, userCommand);
	return userCommand;
}

void UserInterface::printWelcome() {
	cout << MESSAGE_WELCOME_1 << endl << MESSAGE_WELCOME_2 << endl;
}

void UserInterface::updateDisplay(Display &display)
{
	vector<Event*> eventList;
	vector<Task*> taskList;

	eventList = display.getEventList();
	taskList = display.getTaskList();

	generateEventStringList(eventList);
	generateTaskStringList(taskList);

	getFeedbackDisplay(display);

	displayEventList();
	displayTaskList();

	displayFeedback();
}

void UserInterface::generateEventStringList(vector<Event*>& eventList)
{
	_eventStringList.clear();
	for (int i = 0; i < eventList.size(); i++) {
		_eventStringList.push_back(eventList[i]->toString());
	}
}

void UserInterface::generateTaskStringList(vector<Task*>& taskList)
{
	_taskStringList.clear();
	for (int i = 0; i < taskList.size(); i++) {
		_taskStringList.push_back(taskList[i]->toString());
	}
}

void UserInterface::getFeedbackDisplay(Display &display)
{
	_feedback = display.getCommandFeedback();
}

void UserInterface::displayEventList()
{
	displayStringsByIndex(EVENT_IDENTIFIER,_eventStringList);
}

void UserInterface::displayTaskList()
{
	displayStringsByIndex(TASK_IDENTIFIER, _taskStringList);
}

void UserInterface::displayFeedback()
{
	cout << endl;
	for (int i = 0; i < _feedback.size(); i++) {
		cout << _feedback[i] << endl;
	}
	cout << endl;
}

void UserInterface::displayStringsByIndex(string identifier, vector<string>& stringList)
{
	cout << endl;
	for (int index = 0; index < stringList.size(); index++) {
		cout << identifier << index+1 << INDEX_SEPARATOR << stringList[index] << endl;
	}
	cout << endl;
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
void UserInterface::printList(Display& display) {
	vector<Event*> eventList = display.getEventList();
	vector<Task*> taskList = display.getTaskList();

	if (!eventList.empty()) {
		cout << endl;
		cout << EVENT_LIST << endl;
		for (int i = 0; i < eventList.size(); i++) {
			cout << "E" << i + 1 << ": ";
			eventList[i]->printEvent();
			cout << endl;
		}
	}
	if (!taskList.empty()) {
		cout << endl;
		cout << TASK_LIST << endl;
		for (int i = 0; i < taskList.size(); i++) {
			cout << "T" << i + 1 << ": "; 
			taskList[i]->printTask();
			cout << endl;
		}
	}
	
	if (eventList.empty() && taskList.empty()) {
		cout << MESSAGE_FOUNDNOTHING << endl;
	}
}
/*
int UserInterface::convertCharToInt(char input) {
	return input - '0';
}


void UserInterface::updateDefaultDisplay(Storage *LocalData) {
	LocalData->displayDefault(&EventList, &TaskList);
}
*/