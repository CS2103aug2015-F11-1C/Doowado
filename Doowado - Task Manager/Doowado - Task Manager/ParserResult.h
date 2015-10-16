#ifndef PARSER_RESULT_H
#define PARSER_RESULT_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>

using namespace std;

class ParserResult {
private:
	//command & description
	string _userCommand;
	vector<string> _description;
	vector<string> _index;
	vector<string> _entryType;

	//date
	vector<string> _startDate;
	vector<string> _endDate;

	//time
	vector<string> _startTime;
	vector<string> _endTime;

public:
	void setUserCommand();
	void setDescription();
	void setIndex();
	void setEntryType();
	void setStartDate();
	void setEndDate();
	void setStartTime();
	void setEndTime();

	void getUserCommand();
	void getDescription();
	void getIndex();
	void getEntryType();
	void getStartDate();
	void getEndDate();
	void getStartTime();
	void getEndTime();
};
#endif