#include "Event.h"

Event::Event(string name, ptime startTime, ptime endTime){
	_name = name;
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
	cout << setw(20) << left << _name;
	cout << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
}

string Event::toString()
{
	ostringstream eventSummary;
	eventSummary << setw(20) << left << _name;
	eventSummary << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
	return eventSummary.str();
}
