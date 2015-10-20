#include "AddCommand.h"

const string AddCommand::MESSAGE_ADDED = "Added";

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

AddCommand::AddCommand(string entryName, ptime entryStartTime, ptime entryEndTime, ptime entryDueTime)
{
	_entryName = entryName;
	_entryStartTime = entryStartTime;
	_entryEndTime = entryEndTime;
	_entryDueTime = entryDueTime;
}

AddCommand::~AddCommand()
{
}

void AddCommand::execute(Storage* data, Display *display) {
	checkValidName(_entryName);

	if (!_entryStartTime.is_not_a_date_time()) {
		cout << "Event" << endl;
		entryType = type_event;
		Event* newEvent = new Event(_entryName, _entryStartTime, _entryEndTime);
		data->addEvent(newEvent);
	}
	else if (!_entryDueTime.is_not_a_date_time()) {
		cout << "Task" << endl;
		entryType = type_timed_task;
		Task* newTask = new Task(_entryName, _entryDueTime);
		data->addTask(newTask);
	}
	else {
		cout << "Floating Task" << endl;
		entryType = type_floating_task;
		Task* newFloatingTask = new Task(_entryName);
		data->addTask(newFloatingTask);
	}

	generateFeedback();
	display->updateCommandFeedback(_feedback);
	data->saveToFile();
}

void AddCommand::generateFeedback() {
	_feedback.push_back(MESSAGE_ADDED);
	_feedback.push_back(_entryName);

	if (type_event == entryType) {
		_feedback.push_back(to_simple_string(_entryStartTime));
		_feedback.push_back(to_simple_string(_entryEndTime));
	} else if (type_timed_task == entryType) {
		_feedback.push_back(to_simple_string(_entryDueTime));
	} else if (type_floating_task == entryType) {

	}

}

void AddCommand::checkValidName(string name)
{
	assert(name != "");
}

