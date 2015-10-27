#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>
#include "Event.h"
#include "Task.h"
#include "Storage.h"
#include "Display.h"

using namespace std;

const string MESSAGE_ADDED = "Added: ";
const string MESSAGE_TIME = "Time: ";
const string MESSAGE_WRONG = "Oops.It seems that something is wrong with your command.";
const string MESSAGE_FOUNDNOTHING = "Sorry. No results were found. Please try again.";
const string MESSAGE_DELETED = "Deleted£º ";
const string MESSAGE_WELCOME_1 = "Welcome to DOOWADO!";
const string MESSAGE_WELCOME_2 = "You have following events and tasks for today: ";
const string MESSAGE_UPDATED = "Updated: ";
const string MESSAGE_SAVED = " File was saved to: ";
const string TASK_LIST = "Tasks: ";
const string EVENT_LIST = "Events: ";
const string WRONG = "wrong";

const string EVENT_IDENTIFIER = "E";
const string TASK_IDENTIFIER = "T";
const string INDEX_SEPARATOR = " . ";

class UserInterface {
private:
	vector<string> _eventStringList;
	vector<string> _taskStringList;
	vector<string> _feedback;

public:
	string getCommand();
	void showFeedback(vector<string>&, bool isSuccessful, string _commandType);
	void printList(Display&);
	
	void printWelcome();
	//void updateDefaultDisplay(Storage *LocalData);
	void updateDisplay(Display&);

	void generateEventStringList(vector<Entry*>&);
	void generateTaskStringList(vector<Entry*>&);

	void getFeedbackDisplay(Display&);

	void displayEventList();
	void displayTaskList();

	void displayFeedback();

	void displayStringsByIndex(string, vector<string>&);
};

