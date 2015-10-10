//Parser.h

#ifndef PARSER_H
#define PARSER_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>
#include <time.h> 

using namespace std;

//constants
string const DATE_TIME_DELIMITER(",");
int const DATE_KEYWORDS_SIZE = 43;
int const MONTH_KEYWORD_SIZE = 24;
int const DATE_KEYWORD_START_POS = 24;


string const DATE_KEYWORDS[] = { "january", "jan", "february", "feb", "march", "mar", "april", "apr",
"may", "may", "june", "jun", "july", "jul", "august", "aug", "september", "sep", "october", "oct",
"november", "nov", "december", "dec", "monday", "mon", "tuesday", "tue", "wednesday", "wed", "thursday",
"thu", "friday", "fri", "saturday", "sat", "sunday", "sun", "today", "tomorrow", "tmr", "yesterday", "yest" };

class Parser {
private:
	string _command;
	string _description;
	string _index;
	string _startDate;
	string _endDate;
	string _startTime;
	string _endTime;
	string _outputStartDateAndTime;
	string _outputEndtDateAndTime;

public:
	Parser::Parser();

	void setCommand(string &input);

	void setDescription(string &input);

	void setIndex();

	void setTime(string &input);

	void resetTime();

	int convertAlphabetMonthToNumber(string input);

	int convertAlphabetDateToNumber(string input);

	string getDateInfo(string &input);	//also change to int type and set global variables instead of returing a string?

	int getTimeInfo(string &input);

	string calculateDate(string weekdays);

	string currentTime();

	bool isYearValid(string input);

	string isMonthValid(string input);

	bool isDayValid(string input);

	bool isNumber(string input);

	int convertStringNumberToInt(string input);

	bool isTimeKeywordsFound(string &input);

	bool isTimeKeywordsValid(string input);

	bool isLeapYear(int input);

	int numberOfDaysInMonth(int year, int month);

	void solveDayOverFlow(int& year, int& month, int& day);

	void solveNextWeekDays(int& year, int& month, int& day);

	void parse(string input, vector<string> &output);
};
#endif