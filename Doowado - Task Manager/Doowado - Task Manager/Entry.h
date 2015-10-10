#pragma once

#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iomanip>

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

class Entry {
protected:
	string _name;

public:
	Entry();
	Entry(string name);
	virtual string getName();
	virtual void setName(string newName);
};