#ifndef PARSER_RESULT_H
#define PARSER_RESULT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class ParserResult {
private:
	//command & description
	string _userCommand;
	vector<string> _description;
	vector<int> _index;
	vector<string> _entryType;

	//date
	vector<string> _startDate;
	vector<string> _endDate;

	//time
	vector<string> _startTime;
	vector<string> _endTime;

public:
	void setUserCommand(string userCommand);
	void setDescription(vector<string> description);
	void setIndex(vector<int> index);
	void setEntryType(vector<string> entryType);
	void setStartDate(vector<int> startYear, vector<int> startMonth, vector<int> startDay);
	void setEndDate(vector<int> endYear, vector<int> endMonth, vector<int> endDay);
	void setStartTime(vector<int> startTime);
	void setEndTime(vector<int> endTime);

	string getUserCommand();
	vector<string> getDescription();
	vector<int> getIndex();
	vector<string> getEntryType();
	vector<string> getStartDate();
	vector<string> getEndDate();
	vector<string> getStartTime();
	vector<string> getEndTime();
};
#endif