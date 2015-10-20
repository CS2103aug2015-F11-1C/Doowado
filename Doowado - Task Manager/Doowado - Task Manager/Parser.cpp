#include "Parser.h"
#include "ParserResult.h"

using namespace std;

//CONSTANTS
string const ERROR_EMPTY_USER_INPUT = "empty input";
string const DATE_DELIMITER[] = { "on","from","by","at" };
string const DATE_SPLITER = "./";
int const DATE_DELIMITER_SIZE = 4;
int const DATE_NOT_FOUND = 43;

Parser::Parser(){}

void Parser::resetDateAndTime() {
	_startYear.clear();
	_startMonth.clear();
	_startDay.clear();
	_startTime.clear();

	_endYear.clear();
	_endMonth.clear();
	_endDay.clear();
	_endTime.clear();
}

//take in full user input
string Parser::removeExtraSpacePadding(string input){
	size_t start = input.find_first_not_of(" ");
	size_t end = input.find_last_not_of(" ");

	if (start != string::npos) {
		return input.substr(start, (end - start + 1));
	}else {
		return "";
	}
}

//take in full user input
//remove command from the user input string
void Parser::setCommand(string& input){
	size_t spacePos = input.find_first_of(" ");
	
	if (spacePos == string::npos) {
		_userCommand = input;
		input = "";
	}else {
		_userCommand = input.substr(0, spacePos);
		input = input.substr(spacePos + 1);
	}
}

//take in only the description
void Parser::setDescription(string input){
	if (input != "") {
		_description.push_back(input);
	}
}

//take in the user input with command removed by setCommand and date & time keywords removed by setDateAndTime
void Parser::setIndex(string& input){
	size_t spacePos = input.find_first_of(" ");

	string entryType = input.substr(0, spacePos);
	entryType = convertStringTolowerCase(entryType);

	string index = entryType.substr(1);
	int indexInt = convertStringToInt(index);
	entryType = entryType.substr(0, 1);

	if ((entryType == "t" || entryType == "e") && indexInt != -1) {
		_entryType.push_back(entryType);
		_index.push_back(indexInt);
		if (spacePos == string::npos) {
			input = "";
		}else {
			input = input.substr(spacePos + 1);
		}	
	}
	//rmb to include case for multiple task or event number.
}

//take in the user input with command removed by setCommand already
//remove date and time keywords from the user input string
void Parser::setDateAndTime(string& input){
	size_t delimiterPos;
	string dateAndTime;
	size_t spacePos;
	vector<string> dateAndTimeFragment;

	delimiterPos = findDateDelimiterPos(input);

	if (delimiterPos != string::npos) {
		dateAndTime = input.substr(delimiterPos);
		spacePos = dateAndTime.find_first_of(" ");
		dateAndTime = dateAndTime.substr(spacePos + 1);

		dateAndTime = convertStringTolowerCase(dateAndTime);
		dateAndTimeFragment = fragmentizeString(dateAndTime);

		dateSetter(dateAndTimeFragment);
		timeSetter(dateAndTimeFragment);

		//to remove the date and time keywords form the user input string
		input = input.substr(0, delimiterPos);
		input = removeExtraSpacePadding(input);
		removeStartOrEndKeyword(input);
	}else {
		resetDateAndTime();
	}
}

//remove the start or end keywords before the on and by time delimiter
void Parser::removeStartOrEndKeyword(string & input){
	size_t spacePos = input.find_last_of(" ");
	string keyword = input.substr(spacePos + 1);
	keyword = convertStringTolowerCase(keyword);

	if (keyword == "start" || keyword == "end") {
		input = input.substr(0, spacePos);
		input = removeExtraSpacePadding(input);
	}
}

//take in fragment of date and time keywords
void Parser::dateSetter(vector<string> input){
	string const START_END_DATE_DELIMITER = "to";
	int toPos=-1;
	bool foundTo = false;
	bool foundStartDate = false;
	bool foundEndDate = false;

	for (int i = 0; i < input.size(); i++) {
		if (input[i] == START_END_DATE_DELIMITER) {
			toPos = i;
			foundTo = true;
			break;
		}
	}

	if (foundTo) {
		//set start date and end date
		vector<int> startYearMonthDay;
		for (int j = 0; j < toPos; j++) {
			startYearMonthDay = extractYearMonthDay(input[j]);
			if (!startYearMonthDay.empty()) {
				//copy day month and year
				//erase vector[j]?
				_startYear.push_back(startYearMonthDay[0]);
				_startMonth.push_back(startYearMonthDay[1]);
				_startDay.push_back(startYearMonthDay[2]);
				foundStartDate = true;
				break;
			}
		}

		vector<int> endYearMonthDay;
		for (int k = toPos + 1; k < input.size(); k++) {
			endYearMonthDay = extractYearMonthDay(input[k]);
			if (!endYearMonthDay.empty()) {
				_endYear.push_back(endYearMonthDay[0]);
				_endMonth.push_back(endYearMonthDay[1]);
				_endDay.push_back(endYearMonthDay[2]);
				foundEndDate = true;
				break;
			}
		}

		//if the end time is not found or invaild, the end time will be set to start time!
		if ((endYearMonthDay.empty()) && (foundStartDate==true)) {
			_endYear.push_back(_startYear.back());
			_endMonth.push_back(_startMonth.back());
			_endDay.push_back(_startDay.back());
		}

		//if the start time is invalid but a end time is found, the start time will be set to end time
		if ((startYearMonthDay.empty()) && (foundEndDate == true)) {
			_startYear.push_back(_endYear.back());
			_startMonth.push_back(_endMonth.back());
			_startDay.push_back(_endDay.back());
		}

//		if ((foundStartDate == false) && (foundEndDate == false)) {
			//wrong user input, show message?
//			return;
//		}

	}else {
		//set end date only
		vector<int> endYearMonthDay;
		for (int z = 0; z < input.size(); z++) {
			endYearMonthDay = extractYearMonthDay(input[z]);
			if (!endYearMonthDay.empty()) {
				_endYear.push_back(endYearMonthDay[0]);
				_endMonth.push_back(endYearMonthDay[1]);
				_endDay.push_back(endYearMonthDay[2]);
				break;
			}
		}
	}
}

//input type e.g. 17/10/2015 or 17.oct or fri
//output type v[0]year v[1}month v[2]day
vector<int> Parser::extractYearMonthDay(string input){
	vector<int> output;
	vector<string> yearMonthDay;

	size_t dateSpliterPos = input.find_last_of(DATE_SPLITER);
	while (dateSpliterPos != string::npos) {
		string temp = input.substr(dateSpliterPos + 1);
		input = input.substr(0, dateSpliterPos);
		yearMonthDay.push_back(temp);
		dateSpliterPos = input.find_last_of(DATE_SPLITER);
	}
	string day = input;		//take in the last fragment of the string
	yearMonthDay.push_back(day);

	if (yearMonthDay.size() == 3) {
		//v[0]year v[1}month v[2]day
		int temp;
		temp = isYearValid(yearMonthDay[0]);
		if (temp != -1) {
			output.push_back(temp);
			temp = isMonthValid(yearMonthDay[1]);
			if (temp != -1) {
				output.push_back(temp);
				temp = isDayValid(yearMonthDay[2]);
				if (temp != -1) {
					output.push_back(temp);
					return output;
				}else {
					output.clear();
					return output;
				}
			}else {
				output.clear();
				return output;
			}
		}else {
			output.clear();
			return output;
		}
	}else if (yearMonthDay.size() == 2) {
		//v[0]month v[1]day
		int temp;
		temp = isMonthValid(yearMonthDay[0]);
		if (temp != -1) {
			vector<int> time = currentTime();
			output.push_back(time[0]);		//get the year from system
			output.push_back(temp);
			temp = isDayValid(yearMonthDay[1]);
			if (temp != -1) {
				output.push_back(temp);
				return output;
			}else {
				output.clear();
				return output;
			}
		}else {
			output.clear();
			return output;
		}
	}else if (yearMonthDay.size() == 1) {
		//v[0] such as fri, tmr, monday...
		if (convertStringWeekdayToInt(yearMonthDay[0]) != -1) {
			output = calculateWeekdayToNearestDay(yearMonthDay[0]);
			return output;
		}else {
			output.clear();
			return output;
		}
	}else {
		output.clear();
		return output;
	}
}

//input type weekday,tmr
//output type v[0]year v[1}month v[2]day
vector<int> Parser::calculateWeekdayToNearestDay(string input){
	vector<int> output;
	vector<int> tineNow = currentTime();
	int currentYear = tineNow[0];
	int currentMonth = tineNow[1];
	int currentDay = tineNow[2];
	int currentWeekday = tineNow[3];
	int userInputWeekday = convertStringWeekdayToInt(input);

	if (userInputWeekday >= 1 && userInputWeekday <= 7) {
		if (userInputWeekday >= currentWeekday) {
			currentDay = currentDay + userInputWeekday - currentWeekday;
		}else {
			currentDay = currentDay + userInputWeekday - currentWeekday + 7;
		}
	}else {
		if (userInputWeekday == 8) {
			currentDay = currentDay;
		}else {
			if (userInputWeekday == 9) {
				currentDay = currentDay + 1;
			}
		}
	}

	solveDayOverFlow(currentYear, currentMonth, currentDay);

	output.push_back(currentYear);
	output.push_back(currentMonth);
	output.push_back(currentDay);
	return output;
}

void Parser::solveDayOverFlow(int & year, int & month, int & day){
	if ((day > 31) && (month == 12)) {
		day = day - 31;
		month = 1;
		year++;
	}

	if (day > numberOfDaysInMonth(year, month)) {
		day = day - numberOfDaysInMonth(year, month);
		month++;
	}
}

int Parser::numberOfDaysInMonth(int year, int month) {
	if ((month < 1) || (month > 12)) {
		return -1;
	}
	else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
		return 30;
	}
	else if (month == 2 && isLeapYear(year)) {
		return 29;
	}
	else if (month == 2 && !isLeapYear(year)) {
		return 28;
	}
	else {
		return 31;
	}
}

bool Parser::isLeapYear(int input){
	return (((input % 400) == 0) || (input % 4) == 0) && (((input % 100) != 0));
}

int Parser::convertStringWeekdayToInt(string input){
	int dateIdx;
	int dateInNumber;

	for (int i = DATE_KEYWORD_START_POS; i < DDATE_KEYWORDS_END_POS; i++) {
		if (DATE_KEYWORDS[i] == input) {
			dateIdx = i;
			break;
		}else {
			dateIdx = DATE_NOT_FOUND;
		}
	}

	switch (dateIdx) {
	case 24:
	case 25:
		dateInNumber = 1;
		break;
	case 26:
	case 27:
		dateInNumber = 2;

		break;
	case 28:
	case 29:
		dateInNumber = 3;
		break;
	case 30:
	case 31:
		dateInNumber = 4;
		break;
	case 32:
	case 33:
		dateInNumber = 5;
		break;
	case 34:
	case 35:
		dateInNumber = 6;
		break;
	case 36:
	case 37:
		dateInNumber = 7;
		break;
	case 38:
		dateInNumber = 8;
		break;
	case 39:
	case 40:
		dateInNumber = 9;
		break;
	case 41:
	case 42:
		dateInNumber = 10;
		break;
	case 43:
		dateInNumber = -1;
		break;
	}

	return dateInNumber;
}

int Parser::convertStringMonthToInt(string input){
	int monthIdx;
	int monthInNumber;
	int const NOTFOUND = 24;

	for (int i = MONTH_KEYWORD_START_POS; i < MONTH_KEYWORD_END_POS; i++) {
		if (DATE_KEYWORDS[i] == input) {
			monthIdx = i;
			break;
		}
		else {
			monthIdx = NOTFOUND;
		}
	}

	switch (monthIdx) {
	case 0:
	case 1:
		monthInNumber = 1;
		break;
	case 2:
	case 3:
		monthInNumber = 2;
		break;
	case 4:
	case 5:
		monthInNumber = 3;
		break;
	case 6:
	case 7:
		monthInNumber = 4;
		break;
	case 8:
	case 9:
		monthInNumber = 5;
		break;
	case 10:
	case 11:
		monthInNumber = 6;
		break;
	case 12:
	case 13:
		monthInNumber = 7;
		break;
	case 14:
	case 15:
		monthInNumber = 8;
		break;
	case 16:
	case 17:
		monthInNumber = 9;
		break;
	case 18:
	case 19:
		monthInNumber = 10;
		break;
	case 20:
	case 21:
		monthInNumber = 11;
		break;
	case 22:
	case 23:
		monthInNumber = 12;
		break;
	case 24:
		monthInNumber = -1;
		break;
	}

	return monthInNumber;
}

int Parser::isDayValid(string input){
	int day;

	day = convertStringToInt(input);
	if (day <= 31 && day >= 1) {
		return day;
	}
	else {
		return day = -1;
	}
}

int Parser::isMonthValid(string input){
	int month;

	month = convertStringToInt(input);
	if (month <= 12 && month >= 1) {
		return month;
	}else {
		month = convertStringMonthToInt(input);
		return month;
	}
}

int Parser::isYearValid(string input){
	int year;

	year = convertStringToInt(input);
	if (year <= 2999 && year >= 2000) {
		return year;
	}else {
		return year = -1;
	}
}

//take in fragment of date and time keywords
void Parser::timeSetter(vector<string> input){
	string const START_END_TIME_DELIMITER = "to";
	int toPos = -1;
	bool foundTo = false;
	bool foundStartTime = false;
	bool foundEndTime = false;

	for (int i = 0; i < input.size(); i++) {
		if (input[i] == START_END_TIME_DELIMITER) {
			toPos = i;
			foundTo = true;
			break;
		}
	}

	if (foundTo) {
		//set start time and end time
		int startTime;
		for (int j = 0; j < toPos; j++) {
			startTime = extractTime(input[j]);
			if (startTime != -1) {
				_startTime.push_back(startTime);
				foundStartTime = true;
				break;
			}
		}

		int endTime;
		for (int k = toPos + 1; k < input.size(); k++) {
			endTime = extractTime(input[k]);
			if (endTime != -1) {
				_endTime.push_back(endTime);
				foundEndTime = true;
				break;
			}
		}

		if (foundStartTime && !foundEndTime) {
			endTime = startTime;
			_endTime.push_back(endTime);
		}

		if (!foundStartTime && foundEndTime) {
			startTime = endTime;
			_startTime.push_back(startTime);
		}

//		if (!foundStartTime && !foundEndTime) {
//			how, what action will be done?
//			return;
//		}

	}else {
		//set end time only
		int endTime;
		for (int z = 0; z < input.size(); z++) {
			endTime = extractTime(input[z]);
			if (endTime != -1) {
				_endTime.push_back(endTime);
				break;
			}
		}
	}
}

//input format 24hr, e.g. 0830.830,1240,2359
//output 0 means 00:00, 1 means 00:01, 59 means 00:59, 100 means 01:00
int Parser::extractTime(string input){
	string hour;
	int hourInt;
	string minute;
	int minuteInt;
	int timeInt;

	size_t dateSpliterPos = input.find_last_of(DATE_SPLITER);
	if (dateSpliterPos == string::npos) {
		if (input.size() <= 4 && input.size() > 0) {
			if (input.size() == 4) {
				hour = input.substr(0, 2);
				minute = input.substr(2, 2);
				hourInt = convertStringToInt(hour);
				minuteInt = convertStringToInt(minute);
				if (isTimeValid(hourInt, minuteInt)) {
					timeInt = hourInt * 100 + minuteInt;
					return timeInt;
				}else {
					return timeInt = -1;
				}
			}
			else if (input.size() == 3) {
				hour = input.substr(0, 1);
				minute = input.substr(1, 2);
				hourInt = convertStringToInt(hour);
				minuteInt = convertStringToInt(minute);
				if (isTimeValid(hourInt, minuteInt)) {
					timeInt = hourInt * 100 + minuteInt;
					return timeInt;
				}else {
					return timeInt = -1;
				}
			}
			else if (input.size() == 2 || input.size() == 1) {
				hour = input;
				hourInt = convertStringToInt(hour);
				minuteInt = 0;
				if (isTimeValid(hourInt, minuteInt)) {
					timeInt = hourInt * 100 + minuteInt;
					return timeInt;
				}else {
					return timeInt = -1;
				}
			}else {
				return timeInt = -1;
			}
		}else {
			return timeInt = -1;
		}
	}else {
		return timeInt = -1;
	}
}

bool Parser::isTimeValid(int hour, int minute){
	if ((hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59)) {
		return true;
	}else {
		return false;
	}
}

vector<string> Parser::fragmentizeString(string input){
	vector<string> dateAndTime;
	string fragment;

	istringstream in(input);
	while (in >> fragment) {
		dateAndTime.push_back(fragment);
	}
	return dateAndTime;
}

//take in full user input
size_t Parser::findDateDelimiterPos(string input){
	string temp;
	string delimiter="";
	size_t foundDelimiter;
	string lowerCaseInput;

	lowerCaseInput = convertStringTolowerCase(input);

	for (int i = 0; i < DATE_DELIMITER_SIZE; i++) {
		foundDelimiter = lowerCaseInput.rfind(DATE_DELIMITER[i]);
		if (foundDelimiter != string::npos) {
			delimiter = DATE_DELIMITER[i];
			break;
		}
	}

	if (foundDelimiter != string::npos && delimiter != "") {
		if (!isDateDelimiterValid(lowerCaseInput, foundDelimiter)) {
			return string::npos;
		}else {
			_userDelimiter = delimiter;		//found which delimeter did the user use.
			return foundDelimiter;
		}
	}else {
		return string::npos;
	}
}

bool Parser::isDateDelimiterValid(string input, size_t pos){
	string temp;
	string keyWord;
	size_t spacePos;
	bool isValid = true;
	
	temp = input.substr(pos);
	spacePos = temp.find_first_of(" ");
	if (spacePos == string::npos) {
		return false;
	}else {
		temp = temp.substr(spacePos + 1);
		istringstream in(temp);
		while (in >> keyWord) {
			if (!isDateOrTimeKeywordValid(keyWord)) {
				isValid = false;
				break;
			}
		}
	}
	return isValid;
}

bool Parser::isDateOrTimeKeywordValid(string input){
	int temp;
	temp = convertStringToInt(input);

	if (temp >= 0) {
		return true;
	}else {
		for (int i = 0; i < DATE_TIME_KEYWORDS_SIZE; i++) {
			if (DATE_KEYWORDS[i] == input) {
				return true;
			}
		}
	}
	return false;
}

int Parser::convertStringToInt(string input){
	stringstream convetor;
	int number;

	convetor << input;
	convetor >> number;

	if (convetor.fail()) {
		return number = -1;		//not a number
	}
	else {
		return number;		//a number
	}
}

string Parser::convertStringTolowerCase(string input){
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	return input;
}

//v[0]year v[1]month v[2]day v[3]weekday in int
vector<int> Parser::currentTime(){
	string year;
	string month;
	string day;
	string weekday;
	vector<int> timeOutput;

	string timeNow;
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	char buffer[128];
	strftime(buffer, 128, "%Y%m%d%A", &timeinfo);
	timeNow = buffer;

	year = timeNow.substr(0, 4);
	month= timeNow.substr(4, 2);
	day= timeNow.substr(6, 2);
	weekday = timeNow.substr(8);

	timeOutput.push_back(convertStringToInt(year));
	timeOutput.push_back(convertStringToInt(month));
	timeOutput.push_back(convertStringToInt(day));
	weekday = convertStringTolowerCase(weekday);
	timeOutput.push_back(convertStringWeekdayToInt(weekday));

	return timeOutput;
}

/*
string Parser::currentTime(){
	string timeNow;
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	char buffer[128];
	strftime(buffer, 128, "%d/%m/%Y/%A", &timeinfo);
	timeNow = buffer;
	return timeNow;
}
*/

ParserResult Parser::parse(string input){
	vector<string> output;
	ParserResult parserResult;
	string userInput = input;

	userInput = removeExtraSpacePadding(userInput);
	setCommand(userInput);
	setDateAndTime(userInput);
	setIndex(userInput);
	setDescription(userInput);

	parserResult.setUserCommand(_userCommand);
	parserResult.setDescription(_description);
	parserResult.setIndex(_index);
	parserResult.setEntryType(_entryType);
	parserResult.setStartDate(_startYear, _startMonth, _startDay);
	parserResult.setStartTime(_startTime);
	parserResult.setEndDate(_endYear, _endMonth, _endDay);
	parserResult.setEndTime(_endTime);
	
	return parserResult;
}
