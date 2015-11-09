#include "Entry.h"

//@@author A0114137R

Entry::Entry() {
	_title = "";
}

Entry::Entry(string title, ptime endTime)
{
	_title = title;
	_endTime = endTime;
	_isDone = false;
	_isClash = false;
	_isOverdue = false;
}

Entry::Entry(string title, ptime startTime, ptime endTime)
{
	_title = title;
	_startTime = startTime;
	_endTime = endTime;
	_isDone = false;
	_isClash = false;
	_isOverdue = false;
}

Entry::Entry(string title){
	_title = title;
	_isDone = false;
	_isClash = false;
	_isOverdue = false;
}

string Entry::getTitle(){
	return _title;
}

ptime Entry::getStartTime()
{
	return _startTime;
}

ptime Entry::getEndTime()
{
	return _endTime;
}

bool Entry::isDone()
{
	return _isDone;
}

bool Entry::isClash()
{
	return _isClash;
}

bool Entry::isOverdue()
{
	return _isOverdue;
}

void Entry::setTitle(string newTitle)
{
	_title = newTitle;
}

void Entry::setStartTime(ptime startTime)
{
	_startTime = startTime;
}

void Entry::setEndTime(ptime endTime)
{
	_endTime = endTime;
}

void Entry::setDone(bool doneStatus)
{
	_isDone = doneStatus;
}

void Entry::setClash(bool clashStatus)
{
	_isClash = clashStatus;
}

void Entry::setOverdue(bool overdueStatus)
{
	_isOverdue = overdueStatus;
}

//@@author Johandy -unused

void Entry::printEvent()
{
	cout << setw(20) << left << _title;
	cout << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
}

void Entry::printTask()
{
	cout << setw(20) << left << _title;
	cout << " Due: " << setw(20) << to_simple_string(_endTime) << endl;
}

string Entry::toStringEvent()
{
	ostringstream eventSummary;
	eventSummary << setw(20) << left << _title;
	eventSummary << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
	return eventSummary.str();
}

string Entry::toStringTask()
{
	ostringstream taskSummary;
	taskSummary << setw(20) << left << _title;
	taskSummary << " Due: " << setw(20) << to_simple_string(_endTime) << endl;
	return taskSummary.str();
}
