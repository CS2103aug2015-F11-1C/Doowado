#pragma once
#include "Command.h"
#include "CommandException.h"

const string MESSAGE_SUCCESSFUL_EDIT = "Edited";
const string eventType = "e";
const string taskType = "t";

//check casing
enum TypeOfTimeEdit {	editStartDateTime,
						editStartDate,
						editStartTime,
						editNullStart,
						noChangeinStart,
						editEndDateTime,
						editEndDate,
						editEndTime,
						editNullEnd,
						noChangeinEnd
					};

class EditCommand : public Command
{
private:
	EntryType _entryType;
	int _taskID;
	string _newTitle;
	date _newStartDate;
	time_duration _newStartTime;
	date _newEndDate;
	time_duration _newEndTime;

	std::vector<std::string> _feedback;
	Entry * _beforeEditEntry;
	Entry * _editedEntry;

	void _generateFeedback(Entry * editedEntry);
	void _generateUndoFeedBack(Entry * undoneEntry);
	void _updateDisplay(Display * display, Storage * storage, Entry * editedEntry);
	void _setBeforeEditEntry(Entry * beforeEditEntry);
	void _setEditedEntry(Entry * editedEntry);
	TypeOfTimeEdit _checkTimeEditStart();
	TypeOfTimeEdit _checkTimeEditEnd();

public:
	EditCommand(EntryType entryType,
				int taskID,
				string newTitle,
				date newStartDate,
				time_duration newStartTime,
				date newEndDate,
				time_duration newEndTime);

	~EditCommand();
	void execute(Storage* data, Display* display);
	void undo(Storage* data, Display* display);
};

