#include "DisplayController.h"

const string EVENT_SEARCH_FEEDBACK = "Showing Events with: ";
const string TASK_SEARCH_FEEDBACK = "Showing Tasks with: ";
const string EVENT_SHOW_DATE_FEEDBACK = "Showing Events on ";
const string TASK_SHOW_DATE_FEEDBACK = "Showing Tasks on ";
const string TASK_INCOMPLETE_OVERDUE_FEEDBACK = "Showing Tasks: ";
const char DOUBLE_QUOTE_CHARACTER = (char)34;
const string TASK_OVERDUE = "overdue";
const string TASK_INCOMPLETE = "incomplete";
const string TASK_COMPLETED = "completed";
const string EMPTY_STRING = "";
const string EVENT_DEFAULT_FEEDBACK = "today";
const string TASK_DEFAULT_FEEDBACK = "incomplete";
const string DEFAULT_ERROR_MESSAGE = "This input is not supported";

System::String^ convertToSystemString(std::string inputString) {
	return gcnew System::String(inputString.c_str());
}

std::string convertToStdString(System::String^ inputString) {
	return msclr::interop::marshal_as< std::string >(inputString);
}

void changeItemTitleFont(System::Windows::Forms::ListViewItem^ newListViewItem, Entry* currentEntry, Entry* lastUpdatedEntry) {
	if (currentEntry == lastUpdatedEntry) {
		newListViewItem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
	}
	else {
		newListViewItem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel));
	}
}

void changeItemDateFont(System::Windows::Forms::ListViewItem ^ newListViewItem, Entry * currentEntry, Entry* lastUpdatedEntry){
	if (currentEntry == lastUpdatedEntry) {
		newListViewItem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Pixel));
	}
	else {
		newListViewItem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel));
	}
}

void changeEventColourByStatus(System::Windows::Forms::ListViewItem ^ newListViewItem, Entry * currentEvent){
	if (currentEvent->isDone()) {
		newListViewItem->ForeColor = System::Drawing::Color::Gray;
	}
	else if (currentEvent->isClash()) {
		newListViewItem->ForeColor = System::Drawing::Color::Orange;
	}
}

void changeTaskColourByStatus(System::Windows::Forms::ListViewItem ^ newListViewItem, Entry * currentTask)
{
	if (currentTask->isDone()) {
		newListViewItem->ForeColor = System::Drawing::Color::Gray;
	}
	else if (currentTask->isOverdue()) {
		newListViewItem->ForeColor = System::Drawing::Color::DarkRed;
	}
}

DisplayController::DisplayController(){
	_logic = new Logic;
}

DisplayController::~DisplayController() {
	delete _logic;
}

void DisplayController::initialiseProgram() {
	_logic->initialiseProgram();
}

void DisplayController::processInput(System::String^ inputString){
	std::string stdInput = convertToStdString(inputString);

	try {
		_logic->processCommand(stdInput);
	}
	catch (std::exception &e) {
		System::String^ errorMessage = convertToSystemString(e.what());

		throw (errorMessage);
	}
	catch (CmdBuilderException &e) {
		System::String^ errorMessage = convertToSystemString(e.getMessage());

		throw (errorMessage);
	}
	catch (CommandException &e) {
		System::String^ errorMessage = convertToSystemString(e.getMessage());

		throw (errorMessage);
	}
	catch (StorageException &e) {
		System::String^ errorMessage = convertToSystemString(e.getMessage());

		throw (errorMessage);
	}
	catch (...) {
		throw (DEFAULT_ERROR_MESSAGE);
	}
}

int DisplayController::getEventListSize() {
	return _logic->getDisplay()->getEventList().size();
}

int DisplayController::getTaskListSize() {
	return _logic->getDisplay()->getTaskList().size();
}

int DisplayController::getFeedbackListSize() {
	return _logic->getDisplay()->getCommandFeedback().size();
}

System::String ^ DisplayController::retrieveLastFeedback(){
	string lastFeedback;

	for (int i = 0; i < _logic->getDisplay()->getCommandFeedback().size(); i++) {
		lastFeedback += _logic->getDisplay()->getCommandFeedback().at(i);
		lastFeedback += " ";
	}

	System::String^ systemFeedback = convertToSystemString(lastFeedback);
	
	return systemFeedback;
}

System::String ^ DisplayController::retrieveEventListFeedback(){
	std::string feedback = _logic->getDisplay()->getEventDisplayState();

	if (feedback == EMPTY_STRING) {
		feedback = EVENT_DEFAULT_FEEDBACK;
	}
	
	//if start with quote its a search
	if (feedback[0] == DOUBLE_QUOTE_CHARACTER) {
		return convertToSystemString(EVENT_SEARCH_FEEDBACK + feedback);
	}
	else {
		return convertToSystemString(EVENT_SHOW_DATE_FEEDBACK + feedback);
	}
	
}

System::String ^ DisplayController::retrieveTaskListFeedback(){
	std::string feedback = _logic->getDisplay()->getTaskDisplayState();

	if (feedback == EMPTY_STRING) {
		feedback = TASK_DEFAULT_FEEDBACK;
	}

	//if start with quote its a search
	if (feedback[0] == DOUBLE_QUOTE_CHARACTER) {
		return convertToSystemString(TASK_SEARCH_FEEDBACK + feedback);
	}
	else if (feedback == TASK_OVERDUE || feedback == TASK_INCOMPLETE || feedback == TASK_COMPLETED){
		return convertToSystemString(TASK_INCOMPLETE_OVERDUE_FEEDBACK + feedback);
	}
	else {
		return convertToSystemString(TASK_SHOW_DATE_FEEDBACK + feedback);
	}
}

System::Windows::Forms::ListViewItem ^ DisplayController::retrieveEventNameFromList(int index){
	System::String^ eventID;
	System::String^ eventDetails;
	System::Windows::Forms::ListViewItem^ newListViewItem;

	Entry* currentEvent;

	currentEvent = _logic->getDisplay()->retrieveEntry(event, index);

	//process eventID
	eventID = convertToSystemString("E" + to_string(index + 1));

	//process eventTitle
	std::string title = currentEvent->getTitle();
	eventDetails = convertToSystemString(title);

	newListViewItem = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^>(2) { eventID, eventDetails }, -1));
	
	changeItemTitleFont(newListViewItem, currentEvent, _logic->getDisplay()->retrieveLastUpdatedEntry());

	changeEventColourByStatus(newListViewItem, currentEvent);
	
	return newListViewItem;
}

System::Windows::Forms::ListViewItem ^ DisplayController::retrieveEventStartFromList(int index){
	System::String^ eventID;
	System::String^ eventDetails;
	System::Windows::Forms::ListViewItem^ newListViewItem;

	Entry* currentEvent;

	currentEvent = _logic->getDisplay()->retrieveEntry(event, index);

	//process eventID
	eventID = convertToSystemString("");

	//process start time
	std::string startTime = to_simple_string(currentEvent->getStartTime());
	eventDetails = convertToSystemString("Start at: " + startTime);

	newListViewItem = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^>(2) { eventID, eventDetails }, -1));
	
	changeItemDateFont(newListViewItem, currentEvent, _logic->getDisplay()->retrieveLastUpdatedEntry());

	changeEventColourByStatus(newListViewItem, currentEvent);

	return newListViewItem;
}

System::Windows::Forms::ListViewItem ^ DisplayController::retrieveEventEndFromList(int index){
	System::String^ eventID;
	System::String^ eventDetails;
	System::Windows::Forms::ListViewItem^ newListViewItem;

	Entry* currentEvent;

	currentEvent = _logic->getDisplay()->retrieveEntry(event, index);

	//process eventID
	eventID = convertToSystemString("");

	//process end Time
	std::string endTime = to_simple_string(currentEvent->getEndTime());
	eventDetails = convertToSystemString("End at: "+ endTime);

	newListViewItem = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^>(2) { eventID, eventDetails }, -1));
	
	changeItemDateFont(newListViewItem, currentEvent, _logic->getDisplay()->retrieveLastUpdatedEntry());

	changeEventColourByStatus(newListViewItem, currentEvent);

	return newListViewItem;
}

System::Windows::Forms::ListViewItem ^ DisplayController::retrieveTaskNameFromList(int index){
	System::String^ taskID;
	System::String^ taskDetails;
	System::Windows::Forms::ListViewItem^ newListViewItem;

	Entry* currentTask;

	currentTask = _logic->getDisplay()->retrieveEntry(task, index);

	//process taskID
	taskID = convertToSystemString("T" + to_string(index + 1));

	//process taskTitle
	std::string title = currentTask->getTitle();
	taskDetails = convertToSystemString(title);

	newListViewItem = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^>(2) { taskID, taskDetails }, -1));

	changeItemTitleFont(newListViewItem, currentTask, _logic->getDisplay()->retrieveLastUpdatedEntry());

	changeTaskColourByStatus(newListViewItem, currentTask);

	return newListViewItem;
}

System::Windows::Forms::ListViewItem ^ DisplayController::retrieveTaskDueFromList(int index){
	System::String^ taskID;
	System::String^ taskDetails;
	System::Windows::Forms::ListViewItem^ newListViewItem;

	Entry* currentTask;

	currentTask = _logic->getDisplay()->retrieveEntry(task, index);

	//process eventID
	taskID = convertToSystemString("");

	//process end Time
	if (currentTask->getEndTime().is_not_a_date_time()) {
		return (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^>(1) { taskID }, -1));
	}
	else {
		std::string endTime = to_simple_string(currentTask->getEndTime());
		taskDetails = convertToSystemString("Due by: " + endTime);
		newListViewItem = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^>(2) { taskID, taskDetails }, -1));

		changeItemDateFont(newListViewItem, currentTask, _logic->getDisplay()->retrieveLastUpdatedEntry());

		changeTaskColourByStatus(newListViewItem, currentTask);

		return newListViewItem;
	}

}

