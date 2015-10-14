#include "AddCommand.h"

AddCommand::AddCommand(string name) {
	_entryName = name;
}

AddCommand::AddCommand(string name, ptime time1) {
	_entryName = name;
	_entryDueTime = time1;
}

AddCommand::AddCommand(string name, ptime time1, ptime time2) {
	_entryName = name;
	_entryStartTime = time1;
	_entryEndTime = time2;
}

AddCommand::~AddCommand()
{
}

vector<string> AddCommand::execute(Storage* data, Display* display) {
	vector<string> feedback;
	feedback.push_back("Added");
	feedback.push_back(_entryName);

	if (!_entryStartTime.is_not_a_date_time()) {
		cout << "Event" << endl;
		Event* newEvent = new Event(_entryName, _entryStartTime, _entryEndTime);
		data->addEvent(newEvent);

		feedback.push_back(to_simple_string(_entryStartTime));
		feedback.push_back(to_simple_string(_entryEndTime));
	}
	else if (!_entryDueTime.is_not_a_date_time()) {
		cout << "Task" << endl;
		Task* newTask = new Task(_entryName, _entryDueTime);
		data->addTask(newTask);

		feedback.push_back(to_simple_string(_entryDueTime));
	}
	else {
		cout << "Floating Task" << endl;
		Task* newFloatingTask = new Task(_entryName);
		data->addTask(newFloatingTask);
	}

	data->saveToFile();
	return feedback;
}
