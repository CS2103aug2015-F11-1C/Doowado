#include "Entry.h"

Entry::Entry() {
	_title = "";
}

Entry::Entry(string title, ptime endTime)
{
	_title = title;
	_endTime = endTime;
	_isDone = false;
	_isConfirmed = true;
}

Entry::Entry(string title, ptime startTime, ptime endTime)
{
	_title = title;
	_startTime = startTime;
	_endTime = endTime;
	_isDone = false;
	_isConfirmed = true;
}

Entry::Entry(string title){
	_title = title;
	_isDone = false;
	_isConfirmed = true;
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

bool Entry::isConfirmed()
{
	return _isConfirmed;
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

void Entry::setConfirmed(bool confirmStatus)
{
	_isConfirmed = confirmStatus;
}
