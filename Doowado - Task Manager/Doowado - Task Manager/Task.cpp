#include "Task.h"

Task::Task(string name, ptime dueTime, bool isCompleted, bool isOverdue){
	_name = name;
	_dueTime = dueTime;
	_isCompleted = isCompleted;
	_isOverdue = isOverdue;
}

Task::Task(string name, ptime dueTime) {
	_name = name;
	_dueTime = dueTime;
	_isCompleted = false;
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
	cout << setw(20) << left << _name;
	cout << " Due: " << to_simple_string(_dueTime) << endl;
}
