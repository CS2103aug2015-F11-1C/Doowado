#include "AddCommand.h"

//@@author A0102794E

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

	std::string dateDisplayState = generateDateDisplayState();

	display->updateDisplayEventList(relevantEventList);
	display->updateDisplayTaskList(relevantTaskList);

	display->updateCommandFeedback(_feedback);
	display->setLatestUpdatedEntry(_newEntry);

	display->setEventDisplayState(dateDisplayState);
	display->setTaskDisplayState(dateDisplayState);
}

void AddCommand::generateUndoFeedback()
{
	vector<string>::iterator front = _feedback.begin();

	_feedback.insert(front, "Undone");
}

std::string AddCommand::generateDateDisplayState()
{
	std::string displayState;

	if (_entryStartTime.is_not_a_date_time()) {
		date endDate = _entryStartTime.date();

		int endDay = endDate.day();
		int endMonth = endDate.month();
		int endYear = endDate.year();
		int intEndDayOfWeek = endDate.day_of_week();
		std::string endDayOfWeek;

		switch (intEndDayOfWeek)
		{
		case 0:
			endDayOfWeek = "Sunday";
			break;
		case 1:
			endDayOfWeek = "Monday";
			break;
		case 2:
			endDayOfWeek = "Tuesday";
			break;
		case 3:
			endDayOfWeek = "Wednesday";
			break;
		case 4:
			endDayOfWeek = "Thursday";
			break;
		case 5:
			endDayOfWeek = "Friday";
			break;
		case 6:
			endDayOfWeek = "Saturday";
			break;
		default:
			break;
		}

		displayState = endDayOfWeek + ", " + to_string(endDay) + "/" + to_string(endMonth) + "/" + to_string(endYear);
	}
	else {
		date startDate = _entryStartTime.date();

		int startDay = startDate.day();
		int startMonth = startDate.month();
		int startYear = startDate.year();
		int intStartDayOfWeek = startDate.day_of_week();

		std::string startDayOfWeek;

		switch (intStartDayOfWeek)
		{
		case 0:
			startDayOfWeek = "Sunday";
			break;
		case 1:
			startDayOfWeek = "Monday";
			break;
		case 2:
			startDayOfWeek = "Tuesday";
			break;
		case 3:
			startDayOfWeek = "Wednesday";
			break;
		case 4:
			startDayOfWeek = "Thursday";
			break;
		case 5:
			startDayOfWeek = "Friday";
			break;
		case 6:
			startDayOfWeek = "Saturday";
			break;
		default:
			break;
		}

		displayState += startDayOfWeek + ", " + to_string(startDay) + "/" + to_string(startMonth) + "/" + to_string(startYear);
	}

	return displayState;
}
