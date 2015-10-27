#include "Event.h"

Event::Event(string title, ptime startTime, ptime endTime){
	_title = title;
	_startTime = startTime;
	_endTime = endTime;
}

ptime Event::getStartTime(){
	return _startTime;
}

ptime Event::getEndTime(){
	return _endTime;
}

void Event::setStartTime(ptime newStartTime){
	_startTime = newStartTime;
}

void Event::setEndTime(ptime newEndTime){
	_endTime = newEndTime;
}

void Event::printEvent(){
	cout << setw(20) << left << _title;
	cout << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
}

string Event::toString()
{
	ostringstream eventSummary;
	eventSummary << setw(20) << left << _title;
	eventSummary << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
	return eventSummary.str();
}
