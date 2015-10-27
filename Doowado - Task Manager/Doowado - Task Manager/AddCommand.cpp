#include "AddCommand.h"

const string AddCommand::MESSAGE_ADDED = "Added";

AddCommand::AddCommand(string title) {
	_entryTitle = title;
}

AddCommand::AddCommand(string title, ptime time1) {
	_entryTitle = title;
	_entryDueTime = time1;
}

AddCommand::AddCommand(string title, ptime time1, ptime time2) {
	_entryTitle = title;
	_entryStartTime = time1;
	_entryEndTime = time2;
}

AddCommand::AddCommand(string entryTitle, ptime entryStartTime, ptime entryEndTime, ptime entryDueTime)
{
	_entryTitle = entryTitle;
	_entryStartTime = entryStartTime;
	_entryEndTime = entryEndTime;
	_entryDueTime = entryDueTime;
}


AddCommand::~AddCommand()
{
}

void AddCommand::execute(Storage* data, Display *display) {
	checkValidTitle(_entryTitle);

	if (!_entryStartTime.is_not_a_date_time()) {
		//cout << "Event" << endl;
		entryType = type_event;
		Event* newEvent = new Event(_entryTitle, _entryStartTime, _entryEndTime);
		data->addEvent(newEvent);
	}
	else if (!_entryDueTime.is_not_a_date_time()) {
		//cout << "Task" << endl;
		entryType = type_timed_task;
		Task* newTask = new Task(_entryTitle, _entryDueTime);
		data->addTask(newTask);
	}
	else {
		//cout << "Floating Task" << endl;
		entryType = type_floating_task;
		Task* newFloatingTask = new Task(_entryTitle);
		data->addTask(newFloatingTask);
	}

	generateFeedback();
	updateDisplay(display, data);
	data->saveToFile();
}

void AddCommand::generateFeedback() {
	_feedback.push_back(MESSAGE_ADDED);
	_feedback.push_back(_entryTitle);

	if (type_event == entryType) {
		_feedback.push_back(to_simple_string(_entryStartTime));
		_feedback.push_back(to_simple_string(_entryEndTime));
	} else if (type_timed_task == entryType) {
		_feedback.push_back(to_simple_string(_entryDueTime));
	} else if (type_floating_task == entryType) {

	}

}

void AddCommand::checkValidTitle(string title)
{
	assert(title != "");
}

void AddCommand::updateDisplay(Display* display, Storage* data)
{
	vector<Event*> relevantEventList;
	vector<Task*> relevantTaskList;

	if (type_event == entryType) {
		data->retrieveByDate(_entryStartTime, relevantEventList, relevantTaskList);
	}
	else if (type_timed_task == entryType) {
		data->retrieveByDate(_entryDueTime, relevantEventList, relevantTaskList);
	}
	else if (type_floating_task == entryType) {
		ptime currentTime(second_clock::local_time());
		data->retrieveByDate(currentTime, relevantEventList, relevantTaskList);
	}

	display->updateDisplayEventList(relevantEventList);
	display->updateDisplayTaskList(relevantTaskList);

	display->updateCommandFeedback(_feedback);
}

