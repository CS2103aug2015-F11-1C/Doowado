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

void AddCommand::execute(Storage* data) {
	if (!_entryStartTime.is_not_a_date_time()) {
		cout << "Event" << endl;
		Event* newEvent = new Event(_entryName, _entryStartTime, _entryEndTime);
		data->addEvent(newEvent);
	}
	else if (!_entryDueTime.is_not_a_date_time()) {
		cout << "Task" << endl;
		Task* newTask = new Task(_entryName, _entryDueTime);
		data->addTask(newTask);
	}
	else {
		cout << "Floating Task" << endl;
		Task* newFloatingTask = new Task(_entryName);
		data->addTask(newFloatingTask);
	}

	data->saveToFile();
}
