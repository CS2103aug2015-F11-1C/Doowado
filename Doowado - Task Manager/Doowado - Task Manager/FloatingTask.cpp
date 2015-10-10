#include "FloatingTask.h"

FloatingTask::FloatingTask(string name, bool isCompleted){
	_name = name;
	_isCompleted = isCompleted;
}

FloatingTask::FloatingTask(string name) {
	_name = name;
	_isCompleted = false;
}

bool FloatingTask::getCompleted(){
	return _isCompleted;
}

void FloatingTask::setCompleted(){
	if (!_isCompleted) {
		_isCompleted = true;
	} else {
		_isCompleted = false;
	}
}

void FloatingTask::printFTask(){
	cout << setw(20) << left << _name << endl;
}
