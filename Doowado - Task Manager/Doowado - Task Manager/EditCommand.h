#pragma once
#include "Command.h"
#include "CommandException.h"
#include "easylogging++.h"

const int INDEX_LOWER_LIMIT = 0;
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

	void generateFeedback(Entry * editedEntry);
	void generateUndoFeedBack(Entry * undoneEntry);
	void updateDisplay(Display * display, Storage * storage, Entry * editedEntry);
	void setBeforeEditEntry(Entry * beforeEditEntry);
	void setEditedEntry(Entry * editedEntry);
	TypeOfTimeEdit checkTimeEditStart();
	TypeOfTimeEdit checkTimeEditEnd();
	bool isOutOfRangeIndex(EntryType entryType, Display * display);
	void processEditTimeEvent(Storage * data, Display * display, Entry * editedEntry, TypeOfTimeEdit typeEditStart, TypeOfTimeEdit typeEditEnd);
	void processEditTimeTask(Storage * data, Entry * editedEntry, TypeOfTimeEdit typeEditStart, TypeOfTimeEdit typeEditEnd);
	bool isInvalidTime(Entry * editedEntry);

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

