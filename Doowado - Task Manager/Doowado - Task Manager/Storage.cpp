#include "Storage.h"

const string EVENT_ENTRY = "Event";
const string TASK_ENTRY = "Task";
const string FTASK_ENTRY = "FTask";
const string TASK_COMPLETED = "Completed";
const string TASK_NOT_COMPLETED = "Not Completed";
const string TASK_OVERDUE = "Overdue";
const string TASK_NOT_OVERDUE = "Not Overdue";
const string TODAY_INDICATOR = "today";
const string TOMORROW_INDICATOR = "tomorrow";
const string HELP_DIRECTORY = "Help.txt";
const string SAVE_PATH_FILE_DIRECTORY = "SaveDir.txt";
const string SEARCH_QUERY_NOT_FOUND = "Phrase not found in database";

void checkEmptyVector(vector<Entry*> Result) {
	if (Result.empty()) {
		throw string(SEARCH_QUERY_NOT_FOUND);
	}
	else {
		return;
	}
}

void removeDuplicateEvents(vector<Event*> Result) {
	vector <Event*>::iterator it1;
	vector <Event*>::iterator it2;
	
	for (it1 = Result.begin(); it1 != Result.end(); it1++) {
		for (it2 = it1 + 1; it2 != Result.end(); it2++) {
			if ((*it1) == (*it2)) {
				Result.erase(it2);
			}
		}
	}
}

void removeDuplicateTasks(vector<Task*> Result) {
	vector <Task*>::iterator it1;
	vector <Task*>::iterator it2;

	for (it1 = Result.begin(); it1 != Result.end(); it1++) {
		for (it2 = it1 + 1; it2 != Result.end(); it2++) {
			if ((*it1) == (*it2)) {
				Result.erase(it2);
			}
		}
	}
}

Storage::Storage() {
	ifstream savePathInput(SAVE_PATH_FILE_DIRECTORY);
	getline(savePathInput, _saveDir);
	savePathInput.close();

	_helpDir = HELP_DIRECTORY;
}

void Storage::addEvent(Event * newEvent) {
	if (_eventList.empty()) {
		_eventList.push_back(newEvent);
	}
	else {
		vector <Event*>::iterator it = _eventList.begin();

		while (it != _eventList.end() && newEvent->getStartTime() > (*it)->getStartTime()) {
			it++;
		}

		if (it == _eventList.end()) {
			_eventList.push_back(newEvent);
		}
		else {
			_eventList.insert(it, newEvent);
		}
	}
}

void Storage::addTask(Task * newTask) {
	if (_taskList.empty() || newTask->isFloatingTask()) {
		_taskList.push_back(newTask);
	}
	else {
		vector <Task*>::iterator it = _taskList.begin();

		while (it != _taskList.end() && newTask->getDueTime() > (*it)->getDueTime()) {
			it++;
		}

		if (it == _taskList.end()) {
			_taskList.push_back(newTask);
		}
		else {
			_taskList.insert(it, newTask);
		}
	}
}

vector <Event*> Storage::searchEventsByName(vector <string> keywords) {
	vector <Event*> result;

	for (int i = 0; i < keywords.size(); i++) {
		string keyword = keywords[i];
		for (int j = 0; j < _eventList.size(); j++) {
			size_t found = _eventList[j]->getName().find(keyword);
			if (found != string::npos) {
				result.push_back(_eventList[j]);
			}
		}
	}
	
	removeDuplicateEvents(result);
}

vector <Task*> Storage::searchTasksByName(vector <string> keywords) {
	vector <Task*> result;

	for (int i = 0; i < keywords.size(); i++) {
		string keyword = keywords[i];
		for (int j = 0; j < _taskList.size(); j++) {
			size_t found = _taskList[j]->getName().find(keyword);
			if (found != string::npos) {
				result.push_back(_taskList[j]);
			}
		}
	}

	removeDuplicateTasks(result);
}


// Saves to txt file in the following format:
// Entry Type
// Attribute 1 of that Entry type
// Attribute 2 of that Entry type
// Attribute 3 of that Entry type (if any)
// Attribute 4 of that Entry type (if any)
// Attribute 5 of that Entry type (if any)
void Storage::saveToFile() {
	ofstream output(_saveDir);

	for (int i = 0; i < _eventList.size(); i++) {
		output << EVENT_ENTRY << endl;
		output << _eventList[i]->getName() << endl;
		output << to_iso_string(_eventList[i]->getStartTime()) << endl;
		output << to_iso_string(_eventList[i]->getEndTime()) << endl;
	}

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->isFloatingTask()) {
			output << FTASK_ENTRY << endl;
		}
		else {
			output << TASK_ENTRY << endl;
		}
		output << _taskList[i]->getName() << endl;

		if (!_taskList[i]->isFloatingTask()) {
			output << to_iso_string(_taskList[i]->getDueTime()) << endl;
		}

		if (_taskList[i]->getCompleted()) {
			output << TASK_COMPLETED << endl;
		}
		else {
			output << TASK_NOT_COMPLETED << endl;
		}

		if (_taskList[i]->getOverdue()) {
			output << TASK_OVERDUE << endl;
		}
		else {
			output << TASK_NOT_OVERDUE << endl;
		}
	}
	output.close();

	//saves the directory of the txt file used to save
	ofstream savedir(SAVE_PATH_FILE_DIRECTORY);
	savedir << _saveDir << endl;
	savedir.close();
}

void Storage::loadFromFile() {
	ifstream input(_saveDir);

	string entryType;

	while (getline(input, entryType)) {
		if (entryType == EVENT_ENTRY) {
			string name;
			getline(input, name);

			string time;
			getline(input, time);
			ptime startTime(from_iso_string(time));
			getline(input, time);
			ptime endTime(from_iso_string(time));

			Event *newEvent;
			newEvent = new Event(name, startTime, endTime);

			_eventList.push_back(newEvent);
		}
		else if (entryType == TASK_ENTRY) {
			string name;
			getline(input, name);

			string time;
			getline(input, time);
			ptime dueTime(from_iso_string(time));

			bool isCompleted;
			string completed;
			getline(input, completed);
			if (completed == TASK_COMPLETED) {
				isCompleted = true;
			}
			else {
				isCompleted = false;
			}

			bool isOverdue;
			string overdue;
			getline(input, overdue);
			if (overdue == TASK_OVERDUE) {
				isOverdue = true;
			}
			else {
				isOverdue = false;
			}

			Task *newTask;
			newTask = new Task(name, dueTime, isCompleted, isOverdue);
			_taskList.push_back(newTask);
		}
		else if (entryType == FTASK_ENTRY) {
			string name;
			getline(input, name);

			ptime dueTime;

			bool isCompleted;
			string completed;
			getline(input, completed);
			if (completed == TASK_COMPLETED) {
				isCompleted = true;
			}
			else {
				isCompleted = false;
			}

			bool isOverdue = false;

			Task *newFTask;
			newFTask = new Task(name, dueTime, isCompleted, isOverdue);
			_taskList.push_back(newFTask);
		}
	}

	input.close();
}

void Storage::displayDefault(vector <Event*> *eventDisplay, vector <Task*> *taskDisplay) {
	ptime currentTime(second_clock::local_time());

	vector <Event*>::iterator itE = eventDisplay->begin();

	for (int i = 0; i < _eventList.size(); i++) {

		ptime eventTime(_eventList[i]->getStartTime());
		if (eventTime.date() == currentTime.date()) {
			if (itE != eventDisplay->end()) {
				*itE = _eventList[i];
				itE++;
			}
			else {
				eventDisplay->push_back(_eventList[i]);
				itE = eventDisplay->end();
			}
		}
	}

	vector <Task*>::iterator itT = taskDisplay->begin();

	for (int i = 0; i < _taskList.size(); i++) {
		if (!_taskList[i]->getCompleted() && !_taskList[i]->isFloatingTask()) {
			if (itT != taskDisplay->end()) {
				*itT = _taskList[i];
				itT++;
			}
			else {
				taskDisplay->push_back(_taskList[i]);
				itT = taskDisplay->end();
			}
		}
	}

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->isFloatingTask() && !_taskList[i]->getCompleted()) {
			if (itT != taskDisplay->end()) {
				*itT = _taskList[i];
				itT++;
			}
			else {
				taskDisplay->push_back(_taskList[i]);
				itT = taskDisplay->end();
			}
		}
	}
}

vector <Event*> Storage::displayByDate(ptime timeIndicator) {
	vector <Event*> eventResult;

	for (int i = 0; i < _eventList.size(); i++) {
		if (_eventList[i]->getStartTime().date() == timeIndicator.date() || _eventList[i]->getEndTime().date() == timeIndicator.date()) {
			eventResult.push_back(_eventList[i]);
		}
	}

	return eventResult;
}

vector <Event*> Storage::displayByDate(ptime timeIndicator1, ptime timeIndicator2) {
	vector <Event*> eventResult;

	for (int i = 0; i < _eventList.size(); i++) {
		if (_eventList[i]->getEndTime().date() >= timeIndicator1.date() || _eventList[i]->getStartTime().date() >= timeIndicator2.date()) {
			eventResult.push_back(_eventList[i]);
		}
	}

	return eventResult;
}

vector<Task*> Storage::displayIncompleteTasks() {
	vector<Task*> taskResult;

	for (int i = 0; i < _taskList.size(); i++) {
		if (!_taskList[i]->getCompleted()) {
			taskResult.push_back(_taskList[i]);
		}
	}

	return taskResult;
}

vector<Task*> Storage::displayCompletedTasks() {
	vector <Task*> taskResult;

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->getCompleted()) {
			taskResult.push_back(_taskList[i]);
		}
	}

	return taskResult;
}

void Storage::deleteFromEventList(Event * eventPointer) {
	assert(eventPointer != NULL);

	vector<Event*>::iterator it = _eventList.begin();

	while (*it != eventPointer) {
		it++;
	}

	_eventList.erase(it);
}

void Storage::deleteFromTaskLIst(Task * taskPointer) {
	assert(taskPointer != NULL);

	vector<Task*>::iterator it = _taskList.begin();

	while (*it != taskPointer) {
		it++;
	}

	_taskList.erase(it);
}
