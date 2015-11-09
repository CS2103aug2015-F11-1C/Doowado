#pragma once


#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include "msclr\marshal_cppstd.h"
#include "Controller.h"
#include "Entry.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class MessageManager {
private:
	Controller* Doowado;
	vector<Event>* _eventList;
	vector<Task>* _taskList;
	String^ userInput;
	String^ _eventListMessage;
	String^ _taskListMessage;


public:

	MessageManager(void);

	Void generateOutput(String^);


	String^ convertEventToString(vector<Event>*);

	String^ convertTaskToString(vector<Task>*);

	String^ getEventListMessage();

	String^ getTaskListMessage();

	String^ convertToSystemString(string);

	string convertToStdString(String^);
	

};
