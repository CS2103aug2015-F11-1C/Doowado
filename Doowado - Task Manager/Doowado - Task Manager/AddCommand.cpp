#include "AddCommand.h"

const string AddCommand::MESSAGE_ADDED = "Added";


AddCommand::AddCommand(string entryTitle, ptime entryStartTime, ptime entryEndTime)
{
	_entryTitle = entryTitle;
	_entryStartTime = entryStartTime;
	_entryEndTime = entryEndTime;
}


AddCommand::~AddCommand()
{
}

void AddCommand::execute(Storage* data, Display *display) {
	checkValidTitle(_entryTitle);
	
	if (!_entryStartTime.is_not_a_date_time()) {
		//cout << "Event" << endl;
		entryType = type_event;
		_newEntry = new Entry(_entryTitle, _entryStartTime, _entryEndTime);
		data->addEvent(_newEntry);
	}
	else if (!_entryEndTime.is_not_a_date_time()) {
		//cout << "Task" << endl;
		entryType = type_timed_task;
		_newEntry = new Entry(_entryTitle, _entryEndTime);
		data->addTask(_newEntry);
	}
	else {
		//cout << "Floating Task" << endl;
		entryType = type_floating_task;
		_newEntry = new Entry(_entryTitle);
		data->addTask(_newEntry);
	}

	generateFeedback();
	updateDisplay(display, data);
	data->saveToFile();

	History::pushCommand(this);
}

void AddCommand::undo(Storage * data, Display * display)
{
	if (type_event == entryType) {
		data->deleteFromEventList(_newEntry);
	}
	else if (type_timed_task == entryType) {
		data->deleteFromTaskLIst(_newEntry);
	}
	else if (type_floating_task == entryType) {
		data->deleteFromTaskLIst(_newEntry);
	}
	_newEntry = NULL;
	generateUndoFeedback();
	updateDisplay(display, data);
}

void AddCommand::generateFeedback() {
	_feedback.push_back(MESSAGE_ADDED);
	_feedback.push_back(_entryTitle);

	if (type_event == entryType) {
		_feedback.push_back(to_simple_string(_entryStartTime));
		_feedback.push_back(to_simple_string(_entryEndTime));
	} else if (type_timed_task == entryType) {
		_feedback.push_back(to_simple_string(_entryEndTime));
	} else if (type_floating_task == entryType) {

	}

}

void AddCommand::checkValidTitle(string title)
{
	assert(title != "");
}

void AddCommand::updateDisplay(Display* display, Storage* data)
{
	vector<Entry*> relevantEventList;
	vector<Entry*> relevantTaskList;

	if (type_event == entryType) {
		data->retrieveByDate(_entryStartTime, relevantEventList, relevantTaskList);
	}
	else if (type_timed_task == entryType) {
		data->retrieveByDate(_entryEndTime, relevantEventList, relevantTaskList);
	}
	else if (type_floating_task == entryType) {
		ptime currentTime(second_clock::local_time());
		data->retrieveByDate(currentTime, relevantEventList, relevantTaskList);
	}

	display->updateDisplayEventList(relevantEventList);
	display->updateDisplayTaskList(relevantTaskList);

	display->updateCommandFeedback(_feedback);
	display->setLatestUpdatedEntry(_newEntry);
	if (_newEntry != NULL) {
		cout << "latestEntry: " << _newEntry->getTitle() << endl
			;
	}
	else {
		cout << "latestEntry is NULL" << endl;
	}
	
}

void AddCommand::generateUndoFeedback()
{
	vector<string>::iterator front = _feedback.begin();

	_feedback.insert(front, "Undone");
}

