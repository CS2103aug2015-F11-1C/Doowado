#include "Task.h"

Task::Task(string title, ptime dueTime, bool isCompleted, bool isOverdue){
	_title = title;
	_dueTime = dueTime;
	_isCompleted = isCompleted;
	_isOverdue = isOverdue;
}

Task::Task(string title, ptime dueTime) {
	_title = title;
	_dueTime = dueTime;
	_isCompleted = false;
	_isOverdue = false;
}

Task::Task(string title) {
	_title = title;
	_isCompleted = false;
	_isOverdue = false;
}

ptime Task::getDueTime(){
	return _dueTime;
}

bool Task::getCompleted(){
	return _isCompleted;
}

bool Task::getOverdue(){
	return _isOverdue;
}

bool Task::isFloatingTask() {
	if (_dueTime.is_not_a_date_time()) {
		return true;
	} else {
		return false;
	}
}

void Task::setDueTime(ptime newDueTime) {
	_dueTime = newDueTime;
}

void Task::setCompleted(){
	if (!_isCompleted) {
		_isCompleted = true;
	} else {
		_isCompleted = false;
	}
}

void Task::setOverdue(){
	_isOverdue = true;
}

void Task::printTask(){
	cout << setw(20) << left << _title;
	cout << " Due: " << setw(20) << to_simple_string(_dueTime) << endl;
}

string Task::toString()
{
	ostringstream taskSummary;
	taskSummary << setw(20) << left << _title;
	taskSummary << " Due: " << setw(20) << to_simple_string(_dueTime) << endl;
	return taskSummary.str();
}
