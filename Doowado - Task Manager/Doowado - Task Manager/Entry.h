#pragma once

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
	bool _isConfirmed;

public:
	Entry();
	Entry(string, ptime, ptime);
	Entry(string, ptime);
	Entry(string);
	string getTitle();
	ptime getStartTime();
	ptime getEndTime();
	bool isDone();
	bool isConfirmed();

	void setTitle(string newTitle);
	void setStartTime(ptime);
	void setEndTime(ptime);
	void setDone(bool);
	void setConfirmed(bool);
};