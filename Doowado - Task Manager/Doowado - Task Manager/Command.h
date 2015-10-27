#pragma once

#include <vector>
#include <string> 
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Storage.h"
#include "Display.h"
#include <assert.h>
#include "History.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;

enum EntryType { event, task };

class Command
{
public:
	Command();
	virtual ~Command();

	virtual void execute(Storage* data, Display* display);
	virtual void undo(Storage* data, Display* display);
};

