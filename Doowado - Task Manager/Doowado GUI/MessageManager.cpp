
#include "MessageManager.h"
#include <iostream>

MessageManager::MessageManager(void) {
	Doowado = new Controller;
	_eventList = new vector<Event>;
	_taskList = new vector<Task>;
	userInput = "";
	_eventListMessage = "";
	_taskListMessage = "";
}


Void MessageManager::generateOutput(String^ textFromUser) {

	Doowado->executeCommand(convertToStdString(textFromUser));
	Doowado->getDisplayList(*_eventList, *_taskList);
	_eventListMessage = convertEventToString(_eventList);
	_taskListMessage = convertTaskToString(_taskList);
}

String^ MessageManager::convertEventToString (vector<Event>* EventVector){
	ostringstream oss;
	vector<string> startTime;
	vector<string> endTime;
	for (unsigned int i = 0; i < EventVector->size(); i++) {
		startTime[i] = to_simple_string(EventVector->at[i]._getStartTime);
		endTime[i] = to_simple_string(EventVector->at[i]._getEndTime);
	}
	// output index, name, start date, end date, start time, end time accordingly
	for (unsigned int i = 0; i < EventVector->size(); i++) {
		oss << "E"<< to_string(i) << " ";
		oss << EventVector->at(i).getName << " ";
		oss << startTime[i].substr(0,11)<< " ";
		oss << endTime[i].substr(0,11)<< " ";
		oss << startTime[i].substr(12, 5) << " ";
		oss << startTime[i].substr(12, 5) << endl;
	}
	return convertToSystemString(oss.str());

}
	


String^ MessageManager::convertTaskToString(vector<Task>* TaskVector) {
	ostringstream oss;
	vector<string> dueTime;
	for (unsigned int i = 0; i < TaskVector->size(); i++) {
		if (TaskVector->at[i].isFloatingTask) dueTime[i] = " ";
		else dueTime[i] = to_simple_string(TaskVector->at[i].getDueTime);
	}
	for (unsigned int i = 0; i < TaskVector->size(); i++) {
		oss << "T" << to_string(i) << " ";
		oss << TaskVector->at(i).getName << " ";
		if (dueTime[i] != " ") {
			oss << dueTime[i].substr(0, 11) << " ";
			oss << dueTime[i].substr(12, 5) << endl;
		}
		else oss << endl;
	}
	return convertToSystemString(oss.str());
}

String^ MessageManager::convertToSystemString(string inputString) {
	return gcnew String(inputString.c_str());
}

string MessageManager::convertToStdString(String^ inputString) {
	return msclr::interop::marshal_as< std::string >(inputString);
}


String^ MessageManager::getEventListMessage() {
	return _eventListMessage;
}

String^ MessageManager::getTaskListMessage() {
	return _taskListMessage;
}
