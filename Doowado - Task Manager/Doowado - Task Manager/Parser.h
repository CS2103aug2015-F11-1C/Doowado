#ifndef PARSER_H
#define PARSER_H

#include "ParserResult.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <time.h> 
#include <exception>

using namespace std;

//CONSTANTS
int const DATE_TIME_KEYWORDS_SIZE = 46;
int const MONTH_KEYWORD_START_POS = 0;
int const MONTH_KEYWORD_END_POS = 24;
int const DATE_KEYWORD_START_POS = 24;
int const DDATE_KEYWORDS_END_POS = 44;
int const DATE_NOT_FOUND = 44;

string const DATE_KEYWORDS[] = { "january", "jan", "february", "feb", "march", "mar", "april", "apr",
"may", "may", "june", "jun", "july", "jul", "august", "aug", "september", "sep", "october", "oct",
"november", "nov", "december", "dec", "monday", "mon", "tuesday", "tue", "wednesday", "wed", "thursday",
"thu", "friday", "fri", "saturday", "sat", "sunday", "sun", "today", "tomorrow", "tmr", "yesterday", "yest",
"null", "to" };

string const DATE_DELIMITER[] = { "\"", "by","at","start","end","from","ed","st","fr","on" };
int const DATE_DELIMITER_SIZE = 10;
string const DATE_SPLITER = "./";
string const MULTIPLE_DESCRIPTION_KEYWORDS_DELIMITER = "|";
string const START_END_DATE_DELIMITER = "to";
string const START_END_TIME_DELIMITER = "to";

string const ERROR_EMPTY_INPUT = "Empty input";
string const ERROR_INVALID_DATE_TIME_INPUT = "Invalid date or time input";
string const ERROR_INVALID_YEAR = "Invalid year input";
string const ERROR_INVALID_MONTH = "Invalid month input";
string const ERROR_INVALID_DAY = "Invalid day input";
string const ERROR_INVALID_TIME_INPUT = "Invalid time input";

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

public:
	Parser::Parser();

	void resetAll();

	void resetDateAndTime();

	//Take in full  user input string, remove the extra space padding.
	string removeExtraSpacePadding(string input);

	string removeQuotations(string input);

	//Take in full user input string.
	//Set and remove command from the user input string.
	void setCommand(string & input);

	//Take in the user input string without command, date & time keywords and entry type & index.
	//Throw exception of invalid date & time keywords if anything found after the last quotation mark.
	void setDescription(string input);

	//Take in the user input string without command and date & time keywords.
	//Set and remove entry type and index from the user input string.
	void setIndex(string & input);

	bool isIndexVaild(string input);

	//Take in the user input string without command.
	//Set and remove date & time keywords from the user input string.
	void setDateAndTime(string & input);

	//Take in fragmentized vector of string of date & time keywords
	//Find the date keywords and push to start date or end date accordingly, then remove the date found from the vector of string
	void dateSetter(vector<string> & input);

	//Input format 1. 17/10/2015 2. 17.oct 3. fri
	//Output format is in vector of year month and day, v[0]year v[1]month v[2]day
	//Throw exceptions if any of the year month or day is invalid
	vector<int> extractYearMonthDay(string input);

	//Input type fri,tue...,tmr,today
	//Output type v[0]year v[1}month v[2]day
	//If the input day have not passed in current week, the function will return the date accrodingly
	//If the input day have passed in current week, the function will return next week's date accordingly
	vector<int> calculateWeekdayToNearestDay(string input);

	void solveDayOverFlow(int& year, int& month, int& day);

//	void solveNextWeekday(int& year, int& month, int& day);

	int numberOfDaysInMonth(int year, int month);

	bool isLeapYear(int input);

	int convertStringWeekdayToInt(string input);

	int convertStringMonthToInt(string input);

	//Return the day in integer format, return -1 if the input is not a day.
	int isDayValid(int year, int month, string day);

	//Return the month in integer format, return -1 if the input is not a month.
	int isMonthValid(string input);

	//Return the year in integer format, return -1 if the input is not a year.
	int isYearValid(string input);

	//Take in fragmentized vector of string of date & time keywords
	//Find the time keywords and push to start time or end time accordingly, then remove the time found from the vector of string
	void timeSetter(vector<string> & input);

	//Input format is 24hr, e.g. 0830.830,1240,2359
	//Output 0 means 00:00, 1 means 00:01, 59 means 00:59, 100 means 01:00
	int extractTime(string input);

	bool isTimeValid(int hour, int minute);

	//Input a string the function will trim it to each single words, store them in a vector and return the vector.
	vector<string> fragmentizeString(string input);

	//Take in full user input.
	//Return the position if a valid date delimiter is found, return string::npos if not found.
	size_t findDateDelimiterPos(string input);

	//Check every keywords after the date delimiter.
	//If all the keywords after date delimiter are date or time keywords, return true. Otherwise return false.
	bool isDateDelimiterValid(string input, size_t pos);

	//Check the validity of a date or time keyword.
	bool isDateOrTimeKeywordValid(string input);

	//Return -1 if the string is not a number, otherwise return the number in integer format.
	int convertStringToInt(string input);

	string convertStringTolowerCase(string input);

	//Return the current system time in a vector of integer format
	//v[0]year v[1]month v[2]day v[3]weekday in integer format
	vector<int> currentTime();

	//Parser class API
	ParserResult parse(string input);
};
#endif