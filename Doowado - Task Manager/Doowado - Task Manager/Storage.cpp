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

Storage::Storage(string saveDir){
	_saveDir = saveDir;
	_helpDir = HELP_DIRECTORY;
}

void Storage::addEvent(Event * newEvent){
	if (_eventList.empty()) {
		_eventList.push_back(newEvent);
	} else {
		vector <Event*>::iterator it = _eventList.begin();

		while (it != _eventList.end() && newEvent->getStartTime() > (*it)->getStartTime()) {
			it++;
		}

		if (it == _eventList.end()) {
			_eventList.push_back(newEvent);
		} else {
			_eventList.insert(it, newEvent);
		}
	}
}

void Storage::addTask(Task * newTask){
	if (_taskList.empty() || newTask->isFloatingTask()) {
		_taskList.push_back(newTask);
	} else {
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

vector <Entry*> Storage::searchName(string keyword) {
	vector <Entry*> result;

	for (int i = 0; i < _eventList.size(); i++) {
		size_t found = _eventList[i]->getName().find(keyword);
		if (found != string::npos) {
			result.push_back(_eventList[i]);
		}
	}

	for (int i = 0; i < _taskList.size(); i++) {
		size_t found = _taskList[i]->getName().find(keyword);
		if (found != string::npos) {
			result.push_back(_taskList[i]);
		}
	}

	return result;
}

// Saves to txt file in the following format:
// Entry Type
// Attribute 1 of that Entry type
// Attribute 2 of that Entry type
// Attribute 3 of that Entry type (if any)
// Attribute 4 of that Entry type (if any)
// Attribute 5 of that Entry type (if any)
void Storage::saveToFile(){
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
		} else {
			output << TASK_NOT_COMPLETED << endl;
		}

		if (_taskList[i]->getOverdue()) {
			output << TASK_OVERDUE << endl;
		} else {
			output << TASK_NOT_OVERDUE << endl;
		}
	}
	output.close();
}

void Storage::loadFromFile(){
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
		} else if (entryType == TASK_ENTRY) {
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
			} else {
				isCompleted = false;
			}

			bool isOverdue;
			string overdue;
			getline(input, overdue);
			if (overdue == TASK_OVERDUE) {
				isOverdue = true;
			} else {
				isOverdue = false;
			}

			Task *newTask;
			newTask = new Task(name, dueTime, isCompleted, isOverdue);
			_taskList.push_back(newTask);
		} else if (entryType == FTASK_ENTRY) {
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
			} else {
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
			} else {
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

vector <Event*> Storage::displayByDate(string timeIndicator) {
	vector <Event*> eventResult;

	date dateRequired;

	if (timeIndicator == TODAY_INDICATOR) {
		dateRequired = day_clock::local_day();
	} else if (timeIndicator == TOMORROW_INDICATOR) {
		date currentDate(day_clock::local_day());
		date_duration dayDiff(1);
		dateRequired = currentDate + dayDiff;
	} else {
		dateRequired = from_undelimited_string(timeIndicator);
	}

	for (int i = 0; i < _eventList.size(); i++) {
		if (_eventList[i]->getStartTime().date() == dateRequired) {
			eventResult.push_back(_eventList[i]);
		}
	}

	return eventResult;
}

vector<Task*> Storage::displayIncompleteTasks(){
	vector<Task*> taskResult;

	for (int i = 0; i < _taskList.size(); i++) {
		if (!_taskList[i]->getCompleted()) {
			taskResult.push_back(_taskList[i]);
		}
	}

	return taskResult;
}

vector<Task*> Storage::displayCompletedTasks(){
	vector <Task*> taskResult;
	
	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->getCompleted()) {
			taskResult.push_back(_taskList[i]);
		}
	}

	return taskResult;
}