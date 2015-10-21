#ifndef PARSER_H
#define PARSER_H

#include "ParserResult.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <time.h> 

using namespace std;

//constants
int const DATE_TIME_KEYWORDS_SIZE = 46;
int const MONTH_KEYWORD_START_POS = 0;
int const MONTH_KEYWORD_END_POS = 24;
int const DATE_KEYWORD_START_POS = 24;
int const DDATE_KEYWORDS_END_POS = 43;

string const DATE_KEYWORDS[] = { "january", "jan", "february", "feb", "march", "mar", "april", "apr",
"may", "may", "june", "jun", "july", "jul", "august", "aug", "september", "sep", "october", "oct",
"november", "nov", "december", "dec", "monday", "mon", "tuesday", "tue", "wednesday", "wed", "thursday",
"thu", "friday", "fri", "saturday", "sat", "sunday", "sun", "today", "tomorrow", "tmr", "yesterday", "yest",
"to", "am", "pm" };

class Parser {
private:
	string _userDelimiter;

	//command & description
	string _userCommand;
	vector<string> _description;
	vector<int> _index;
	vector<string> _entryType;
	
	//start
	vector<int> _startYear;
	vector<int> _startMonth;
	vector<int> _startDay;
	vector<int> _startTime;

	//end
	vector<int> _endYear;
	vector<int> _endMonth;
	vector<int> _endDay;
	vector<int> _endTime;

private:
	void resetAll();

	void resetDateAndTime();

	string removeExtraSpacePadding(string input);

	void setCommand(string & input);

	void setDescription(string input);

	void setIndex(string & input);

	void setDateAndTime(string & input);

	void removeStartOrEndKeyword(string & input);

	void dateSetter(vector<string> input);

	vector<int> extractYearMonthDay(string input);

	vector<int> calculateWeekdayToNearestDay(string input);

	void solveDayOverFlow(int& year, int& month, int& day);

//	void solveNextWeekday(int& year, int& month, int& day);

	int numberOfDaysInMonth(int year, int month);

	bool isLeapYear(int input);

	int convertStringWeekdayToInt(string input);

	int convertStringMonthToInt(string input);

	int isDayValid(string input);

	int isMonthValid(string input);

	int isYearValid(string input);

	void timeSetter(vector<string> input);

	int extractTime(string input);

	bool isTimeValid(int hour, int minute);

	vector<string> fragmentizeString(string input);

	size_t findDateDelimiterPos(string input);

	bool isDateDelimiterValid(string input, size_t pos);

	bool isDateOrTimeKeywordValid(string input);

	int convertStringToInt(string input);

	string convertStringTolowerCase(string input);

	vector<int> currentTime();

//	string currentTime();

public:
	Parser::Parser();

	ParserResult parse(string input);
};
#endif