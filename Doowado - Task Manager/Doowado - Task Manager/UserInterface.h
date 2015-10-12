#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>
#include "Event.h"
#include "Task.h"
#include "Storage.h"

using namespace std;

class UserInterface {
private:
	static const string MESSAGE_ADDED;
	static const string MESSAGE_TIME;
	static const string MESSAGE_WRONG;
	static const string MESSAGE_UPDATED;
	static const string MESSAGE_SAVED;
	static const string TASK_LIST;
	static const string EVENT_LIST;
	static const string MESSAGE_FOUNDNOTHING;
	static const string MESSAGE_DELETED;
	static const string WRONG;
	static const string MESSAGE_WELCOME_1;
	static const string MESSAGE_WELCOME_2;
private:
	string command;
	vector<string> feedback;
	vector<Event*> EventList;
	vector<Task*> TaskList;

private:
	int convertCharToInt(char input);

public:
	void showFeedback(vector<string>&, bool isSuccessful, string _commandType);
	void printList();
	void getCommand(string& command);
	void printWelcome();
	void getEntry(string input, string& output);
	void updateDefaultDisplay(Storage *LocalData);
};

