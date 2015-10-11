#include "Storage.h"

const string EVENT_ENTRY = "Event";
const string TASK_ENTRY = "Task";
const string FTASK_ENTRY = "FTask";
const string TASK_COMPLETED = "Completed";
const string TASK_NOT_COMPLETED = "Not Completed";
const string TASK_OVERDUE = "Overdue";
const string TASK_NOT_OVERDUE = "Not Overdue";

Storage::Storage(string saveDir){
	_saveDir = saveDir;
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
	if (_taskList.empty()) {
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

void Storage::addFloatingTask(FloatingTask * newFTask){
	_floatingTaskList.push_back(newFTask);
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
		output << TASK_ENTRY << endl;
		output << _taskList[i]->getName() << endl;
		output << to_iso_string(_taskList[i]->getDueTime()) << endl;
		
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

	for (int i = 0; i < _floatingTaskList.size(); i++) {
		output << FTASK_ENTRY << endl;
		output << _floatingTaskList[i]->getName() << endl;

		if (_floatingTaskList[i]->getCompleted()) {
			output << TASK_COMPLETED << endl;
		} else {
			output << TASK_NOT_COMPLETED << endl;
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

			bool isCompleted;
			string completed;
			getline(input, completed);
			if (completed == TASK_COMPLETED) {
				isCompleted = true;
			}
			else {
				isCompleted = false;
			}

			FloatingTask *newFTask;
			newFTask = new FloatingTask(name, isCompleted);
			_floatingTaskList.push_back(newFTask);
		}
	}

	input.close();
}

void Storage::displayDefault(vector <Event*> *eventDisplay, vector <Task*> *taskDisplay, vector <FloatingTask*> *FTaskDisplay) {
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
		if (!_taskList[i]->getCompleted()) {
			if (*itT != nullptr) {
				*itT = _taskList[i];
				itT++;
			} else {
				taskDisplay->push_back(_taskList[i]);
				itT = taskDisplay->end();
			}
		}
	}

	vector <FloatingTask*>::iterator itFT = FTaskDisplay->begin();

	for (int i = 0; i < _floatingTaskList.size(); i++) {
		if (!_floatingTaskList[i]->getCompleted()) {
			if (*itFT != nullptr) {
				*itFT = _floatingTaskList[i];
				itFT++;
			} else {
				FTaskDisplay->push_back(_floatingTaskList[i]);
				itFT = FTaskDisplay->end();
			}
		}
	}
}

void Storage::sortByDate(){

}
