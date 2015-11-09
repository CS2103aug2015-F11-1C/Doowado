#pragma once
//@@author A0114137R

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Entry {
protected:
	string _title;
	ptime _startTime;
	ptime _endTime;
	bool _isDone;
	bool _isOverdue;
	bool _isClash;

public:
	Entry();
	Entry(string, ptime, ptime);
	Entry(string, ptime);
	Entry(string);
	string getTitle();
	ptime getStartTime();
	ptime getEndTime();
	bool isDone();
	bool isClash();
	bool isOverdue();

	void setTitle(string newTitle);
	void setStartTime(ptime);
	void setEndTime(ptime);
	void setDone(bool);
	void setClash(bool);
	void setOverdue(bool);

	//@@author A0114137R

	void printEvent();
	void printTask();
	string toStringEvent();
	string toStringTask();
};