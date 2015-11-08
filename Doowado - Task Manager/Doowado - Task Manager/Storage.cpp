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

void removeDuplicateEvents(vector<Entry*> Result) {
	vector <Entry*>::iterator it1;
	vector <Entry*>::iterator it2;
	
	for (it1 = Result.begin(); it1 != Result.end(); it1++) {
		for (it2 = it1 + 1; it2 != Result.end(); it2++) {
			if ((*it1) == (*it2)) {
				Result.erase(it2);
			}
		}
	}
}

void removeDuplicateTasks(vector<Entry*> Result) {
	vector <Entry*>::iterator it1;
	vector <Entry*>::iterator it2;

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

void Storage::addEvent(Entry * newEvent) {
	if (_eventList.empty()) {
		_eventList.push_back(newEvent);
	}
	else {
		vector <Entry*>::iterator it = _eventList.begin();

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

void Storage::addTask(Entry * newTask) {
	if (_taskList.empty() || newTask->getEndTime().is_not_a_date_time()) {
		_taskList.push_back(newTask);
	}
	else {
		vector <Entry*>::iterator it = _taskList.begin();

		while (it != _taskList.end() && newTask->getEndTime() > (*it)->getEndTime()) {
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

vector <Entry*> Storage::searchEventsByTitle(vector <string> keywords) {
	vector <Entry*> result;

	for (int i = 0; i < keywords.size(); i++) {
		string keyword = keywords[i];
		for (int j = 0; j < _eventList.size(); j++) {
			size_t found = _eventList[j]->getTitle().find(keyword);
			if (found != string::npos) {
				result.push_back(_eventList[j]);
			}
		}
	}
	
	removeDuplicateEvents(result);
	return result;
}

vector <Entry*> Storage::searchTasksByTitle(vector <string> keywords) {
	vector <Entry*> result;

	for (int i = 0; i < keywords.size(); i++) {
		string keyword = keywords[i];
		for (int j = 0; j < _taskList.size(); j++) {
			size_t found = _taskList[j]->getTitle().find(keyword);
			if (found != string::npos) {
				result.push_back(_taskList[j]);
			}
		}
	}

	removeDuplicateTasks(result);
	return result;
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
		output << _eventList[i]->getTitle() << endl;
		output << to_iso_string(_eventList[i]->getStartTime()) << endl;
		output << to_iso_string(_eventList[i]->getEndTime()) << endl;
	}

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->getEndTime().is_not_a_date_time()) {
			output << FTASK_ENTRY << endl;
		}
		else {
			output << TASK_ENTRY << endl;
		}
		output << _taskList[i]->getTitle() << endl;

		if (!_taskList[i]->getEndTime().is_not_a_date_time()) {
			output << to_iso_string(_taskList[i]->getEndTime()) << endl;
		}

		if (_taskList[i]->isDone()) {
			output << TASK_COMPLETED << endl;
		}
		else {
			output << TASK_NOT_COMPLETED << endl;
		}

		if (_taskList[i]->isOverdue()) {
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
			string title;
			getline(input, title);

			string time;
			getline(input, time);
			ptime startTime(from_iso_string(time));
			getline(input, time);
			ptime endTime(from_iso_string(time));

			Entry *newEvent;
			newEvent = new Entry(title, startTime, endTime);

			_eventList.push_back(newEvent);
		}
		else if (entryType == TASK_ENTRY) {
			string title;
			getline(input, title);

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

			Entry *newTask;
			newTask = new Entry(title, dueTime);
			newTask->setDone(isCompleted);
			newTask->setOverdue(isOverdue);
			_taskList.push_back(newTask);
		}
		else if (entryType == FTASK_ENTRY) {
			string title;
			getline(input, title);

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

			Entry *newFTask;
			newFTask = new Entry(title);
			newFTask->setDone(isCompleted);
			newFTask->setOverdue(isOverdue);
			_taskList.push_back(newFTask);
		}
	}

	input.close();
}

std::vector<Entry*> Storage::retrieveEventList()
{
	return _eventList;
}

std::vector<Entry*> Storage::retrieveTaskList()
{
	return _taskList;
}

void Storage::displayDefault(vector <Entry*> *eventDisplay, vector <Entry*> *taskDisplay) {
	ptime currentTime(second_clock::local_time());

	vector <Entry*>::iterator itE = eventDisplay->begin();

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

	vector <Entry*>::iterator itT = taskDisplay->begin();

	for (int i = 0; i < _taskList.size(); i++) {
		if (!_taskList[i]->isDone() && !_taskList[i]->getEndTime().is_not_a_date_time()) {
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
		if (_taskList[i]->getEndTime().is_not_a_date_time() && !_taskList[i]->isDone()) {
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

void Storage::retrieveByDate(ptime timeIndicator, vector <Entry*>& eventResult, vector <Entry*>& taskResult) {
	
	eventResult.clear();
	taskResult.clear();

	for (int i = 0; i < _eventList.size(); i++) {
		if (_eventList[i]->getStartTime().date() <= timeIndicator.date() && _eventList[i]->getEndTime().date() >= timeIndicator.date()) {
			eventResult.push_back(_eventList[i]);
		}
	}

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->getEndTime().date() == timeIndicator.date() || _taskList[i]->getEndTime().is_not_a_date_time()) {
			taskResult.push_back(_taskList[i]);
		}
	}
}


void Storage::retrieveByDate(ptime timeIndicator1, ptime timeIndicator2, vector<Entry*>& eventResult, vector<Entry*>& taskResult) {
	eventResult.clear();
	taskResult.clear();

	for (int i = 0; i < _eventList.size(); i++) {
		if (_eventList[i]->getEndTime().date() >= timeIndicator1.date() || _eventList[i]->getStartTime().date() >= timeIndicator2.date()) {
			eventResult.push_back(_eventList[i]);
		}
	}
	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->getEndTime().date() >= timeIndicator1.date() && _taskList[i]->getEndTime().date() <= timeIndicator2.date()) {
			taskResult.push_back(_taskList[i]);
		}
	}
}

vector<Entry*> Storage::retrieveEventByDone(bool doneStatus)
{
	vector <Entry*> eventResult;

	for (int i = 0; i < _eventList.size(); i++) {
		if (_eventList[i]->isDone() == doneStatus) {
			eventResult.push_back(_eventList[i]);
		}
	}

	return eventResult;
}

vector<Entry*> Storage::retrieveTaskByDone(bool doneStatus)
{
	vector<Entry*> taskResult;

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->isDone() == doneStatus) {
			taskResult.push_back(_taskList[i]);
		}
	}
	return taskResult;
}

vector<Entry*> Storage::retrieveTaskByOverdue(bool overdueStatus){
	vector <Entry*> taskResult;

	for (int i = 0; i < _taskList.size(); i++) {
		if (_taskList[i]->isOverdue() == overdueStatus) {
			taskResult.push_back(_taskList[i]);
		}
	}

	return taskResult;
}

void Storage::deleteFromEventList(Entry * eventPointer) {
	assert(eventPointer != NULL);

	vector<Entry*>::iterator it = _eventList.begin();

	while (*it != eventPointer) {
		it++;
	}

	_eventList.erase(it);
}

void Storage::deleteFromTaskLIst(Entry * taskPointer) {
	assert(taskPointer != NULL);

	vector<Entry*>::iterator it = _taskList.begin();

	while (*it != taskPointer) {
		it++;
	}

	_taskList.erase(it);
}

void Storage::changeSaveDirectory(string newSaveDir) {
	_saveDir = newSaveDir;
}
