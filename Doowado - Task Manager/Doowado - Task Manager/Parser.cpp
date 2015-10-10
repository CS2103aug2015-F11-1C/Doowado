//Parser.cpp
//Expected input format
//The input can be uppercase or lower case
//add meeting,2015/12/15 1200-1400, add meeting,2015/jan/15 1200-1400, add meeting,feb/15 1200-1400, add meeting,tmr 1200-1400, add meeting,friday 1200-1400
//add meeting,2015/12/15 1200 to 1400, add project deadline,2015/12/15 by 1400
//edit 1.,2015/12/15 1200-1400	edit time case, intended index followed by . to indicate index and followed by , to indicate new time 
//edit 1. new name, edit name case
//search searchKeywords
//undo 1.
//delete 2.
//Expected output format
//vector passed by reference
//For add task:
//_command followed by _description followed by _outputStartDateAndTime followed by _outputEndtDateAndTime;
//For add deadline:
//_command followed by _description followed by _outputEndtDateAndTime;
//For other commands:
//_command followed by _description



#include "Parser.h"
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>
#include <time.h> 

using namespace std;

Parser::Parser() {}

void Parser::setCommand(string & input){	//input type "add meeting,2015/12/15 1400-1500"
	string cmd;
	_command.clear();

	cmd = input.substr(0, input.find_first_of(' '));
	_command = cmd;
}

void Parser::setDescription(string & input){	//input type "add meeting,2015/12/15 1400-1500"
	string temp;
	_description.clear();

	if (input.find_first_of(" ") != string::npos) {		//in case for show, just one word input.
		if (isTimeKeywordsFound(input) == true) {
			temp = input.substr(input.find_first_of(' ') + 1);
			_description = temp.substr(0, temp.rfind(DATE_TIME_DELIMITER));
		}
		else {
			_description = input.substr(input.find_first_of(' ') + 1);
		}
	}
}

void Parser::setIndex(){	//input type "1. add meeting"
	string tempIndex;

	_index.clear();

	if (_description.find_first_of(".") != string::npos) {
		tempIndex = _description.substr(0, _description.find_first_of("."));
		if (isNumber(tempIndex) == true) {
			_index = tempIndex;
			_description = _description.substr(_description.find_first_of(".") + 1);	//remove 1.
			if (!_description.empty()) {
				_description = _description.substr(_description.find_first_not_of(" "));	//remove extra space, if there are any
			}	
		}
	}
}

void Parser::setTime(string & input){	//input type "add meeting,2015/12/15 1400-1500"
	string tempTimeKeyword;
	string date;
	int timeType;

	resetTime();

	if (isTimeKeywordsFound(input) == true) {
		tempTimeKeyword = input.substr(input.rfind(DATE_TIME_DELIMITER) + 1);
		date=getDateInfo(tempTimeKeyword);
		timeType=getTimeInfo(tempTimeKeyword);

		if (timeType == 1 && date!="invalid input") {
			_outputStartDateAndTime = date + "T" + _startTime;
			_outputEndtDateAndTime = date + "T" + _endTime;
		}
		else {
			if (timeType == 2 && date != "invalid input") {
				_outputEndtDateAndTime = date + "T" + _endTime;
			}
			else {
				if (timeType == 3 && date != "invalid input") {
					//also deadline?
				}
				else {
					//invalid input
				}
			}
		}
	}
}

void Parser::resetTime(){
	_startDate.clear();
	_endDate.clear();
	_startTime.clear();
	_endTime.clear();
	_outputStartDateAndTime.clear();
	_outputEndtDateAndTime.clear();
}

int Parser::convertAlphabetMonthToNumber(string input){
	int monthIdx;
	int monthInNumber;
	int const NOTFOUND = 24;

//	transform(input.begin(), input.end(), input.begin(), ::tolower);	//since we tolower input in the caller function.

	for (int i = 0; i < MONTH_KEYWORD_SIZE; i++) {
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

int Parser::convertAlphabetDateToNumber(string input) {
	int dateIdx;
	int dateInNumber;
	int const NOTFOUND = 43;

//	transform(input.begin(), input.end(), input.begin(), ::tolower);	//since we tolower input in the caller function.

	for (int i = DATE_KEYWORD_START_POS; i < DATE_KEYWORDS_SIZE; i++) {
		if (DATE_KEYWORDS[i] == input) {
			dateIdx = i;
			break;
		}
		else {
			dateIdx = NOTFOUND;
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

string Parser::getDateInfo(string & input){		//input format "2015/12/15 1400-1500"
	string timeNow;
	string dateKeyword;
	string firstKeyword;
	string secondKeyword;
	string thirdKeyword;
	string year;
	string month;
	string day;
	string output;
	bool invalidInput=false;

	dateKeyword = input.substr(0, input.find_first_of(" "));
	transform(dateKeyword.begin(), dateKeyword.end(), dateKeyword.begin(), ::tolower);

	if (dateKeyword.find("/") == string::npos) {
		//keywords like tody friday tmr. tmr 1200-1400
		firstKeyword = dateKeyword;
		if (convertAlphabetDateToNumber(firstKeyword) == -1) {   //invalid date, refector this or use a int const Invalid.
			invalidInput = true;
		}
		else {
			day = firstKeyword;
			output = calculateDate(day);
		}
	}
	else {
		firstKeyword = dateKeyword.substr(0, input.find_first_of("/"));
		dateKeyword = dateKeyword.substr(dateKeyword.find_first_of("/") + 1);	//removed first keyword and / from dateKeyword.

		if (dateKeyword.find("/") == string::npos) {
			// jan/13 1200-1400
			if (isMonthValid(firstKeyword) == "invalid") {
				invalidInput = true;
			}
			else {
				month = isMonthValid(firstKeyword);
				secondKeyword = dateKeyword;
				if (isDayValid(secondKeyword) == true) {
					day = secondKeyword;
					thirdKeyword = currentTime();
					year = thirdKeyword.substr(0, 4);

					if (month.size() == 1) {	//delete this part! think a better way! adding 0 to the single digit num such as 3
						month = "0" + month;
					}
					if (day.size() == 1) {		//delete this part! think a better way! adding 0 to the single digit num such as 3
						day = "0" + day;
					}

					output = year + month + day;
				}
				else {
					invalidInput = true;
				}
			}
		}
		else {
			//2015/12/15 1400-1500 or 2015/jan/15
			if (isYearValid(firstKeyword) == true) {
				year = firstKeyword;
				secondKeyword = dateKeyword.substr(0, dateKeyword.find_first_of("/"));
				dateKeyword = dateKeyword.substr(dateKeyword.find_first_of("/") + 1); //removed second keyword and / from dateKeyword.
				thirdKeyword = dateKeyword;

				if (isMonthValid(secondKeyword) == "invalid") {
					invalidInput = true;
				}
				else {
					month = isMonthValid(secondKeyword);	//check this one,may contain error,check the validity of the month keyword and convert it to number form if necessay.
					if (isDayValid(thirdKeyword) == true) {
						day = thirdKeyword;

						if (month.size() == 1) {	//delete this part! think a better way! adding 0 to the single digit num such as 3
							month = "0" + month;
						}
						if (day.size() == 1) {		//delete this part! think a better way! adding 0 to the single digit num such as 3
							day = "0" + day;
						}

						output = year  + month + day;
					}
					else {
						invalidInput = true;
					}
				}
			}
			else {
				invalidInput = true;
			}
		}
	}

	if (invalidInput == true) {
		output = "invalid input";
		return output;
	}
	else {
		return output;
	}
}

int Parser::getTimeInfo(string & input){		//input format "2015/12/15 1400-1500"

	string const TIME_DELIMITER_1("-");
	string const TIME_DELIMITER_2("to");
	string const TIME_DELIMITER_3("by");
	string timeKeyword;
	int output;
	bool invalidInput = false;

	timeKeyword = input.substr(input.find_first_of(" ") + 1);	//to remove the date info
	transform(timeKeyword.begin(), timeKeyword.end(), timeKeyword.begin(), ::tolower);

	if (timeKeyword.find(TIME_DELIMITER_1) != string::npos) {
		//1200-1500
		_startTime = timeKeyword.substr(0, timeKeyword.find_first_of(TIME_DELIMITER_1));
		_endTime = timeKeyword.substr(timeKeyword.find_first_of(TIME_DELIMITER_1) + 1);
		output = 1; //event

	}else if (timeKeyword.find(TIME_DELIMITER_2) != string::npos) {
		//1200 to 1500
		_startTime = timeKeyword.substr(0, timeKeyword.find_first_of(" "));
		_endTime = timeKeyword.substr(timeKeyword.find(TIME_DELIMITER_2) + 3);
		output = 1; //event
	}else if(timeKeyword.find(TIME_DELIMITER_3) != string::npos){
		//by 1300
		_endTime = timeKeyword.substr(timeKeyword.find(TIME_DELIMITER_3) + 3);
		output = 2; //deadline
	}else {
		invalidInput = true;
	}

	if (invalidInput == true) {
		output = 3; //invalid
		return output;
	}
	else {
		return output;
	}
}

string Parser::calculateDate(string weekdays){
	ostringstream output;
	int currentYear;
	int currentMonth;
	int currentDay;
	int currentWeekday;
	int userInputWeekday;
	string timeNow;

	timeNow = currentTime();
	currentYear = convertStringNumberToInt(timeNow.substr(0,4));
	currentMonth = convertStringNumberToInt(timeNow.substr(5, 2));
	currentDay = convertStringNumberToInt(timeNow.substr(8, 2));
	currentWeekday = convertAlphabetDateToNumber(timeNow.substr(11));
	userInputWeekday = convertAlphabetDateToNumber(weekdays);

	if (userInputWeekday >= 1 && userInputWeekday <= 7) {
		if (userInputWeekday >= currentWeekday) {
			currentDay = currentDay + userInputWeekday - currentWeekday;
		}
		else {
			currentDay = currentDay + userInputWeekday - currentWeekday + 7;
		}
	}
	else {
		if (userInputWeekday == 8) {
			currentDay = currentDay;
		}
		else {
			if (userInputWeekday == 9) {
				currentDay = currentDay + 1;
			}
		}
	}

	solveDayOverFlow(currentYear, currentMonth, currentDay);

	if (currentDay < 10 && currentMonth < 10) {		//delete this part! think a better way! adding 0 to the single digit num such as 3
		output << currentYear << "0" << currentMonth << "0" << currentDay;
	}
	else {
		if (currentDay < 10 && currentMonth >= 10) {
			output << currentYear << currentMonth << "0" << currentDay;
		}
		else {
			if (currentDay >= 10 && currentMonth < 10) {
				output << currentYear << "0" << currentMonth <<  currentDay;
			}
			else {
				output << currentYear << currentMonth << currentDay;
			}
		}	
	}		//delete this part! think a better way! adding 0 to the single digit num such as 3
	
	return output.str();
}

string Parser::currentTime()
{
	string timeNow;
	time_t rawtime;
	time(&rawtime);
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	char buffer[128];
	strftime(buffer, 128, "%Y/%m/%d %A", &timeinfo);
	timeNow = buffer;
	return timeNow;
}

bool Parser::isYearValid(string input){
	stringstream convetor;
	int number;

	convetor << input;
	convetor >> number;

	if (number <= 2999 && number >= 2000) {
		return true;
	}
	else {
		return false;
	}
}

string Parser::isMonthValid(string input){
	int const NOTFOUND = -1;
	string const ERROR = "invalid";

	stringstream monthConvetor;
	ostringstream output;
	int monthInNumber=NOTFOUND;
	
	monthConvetor << input;
	monthConvetor >> monthInNumber;

	if (monthConvetor.fail()) {
		monthInNumber = convertAlphabetMonthToNumber(input);
		if (monthInNumber == NOTFOUND) {
			return ERROR;
		}
		else {
			output << monthInNumber;
			return output.str();
		}
	}
	else {
		if (monthInNumber <= 12 && monthInNumber >= 1) {
			output << monthInNumber;			
			return output.str();
		}
		else {
			return ERROR;
		}
	}
}

bool Parser::isDayValid(string input){
	stringstream convetor;
	int number;

	convetor << input;
	convetor >> number;

	if (number <= 31 && number >= 1) {
		return true;
	}
	else {
		return false;
	}
}

bool Parser::isNumber(string input){
	stringstream convetor;
	int number;
	
	convetor << input;
	convetor >> number;

	if (convetor.fail()) {
		return false;		//not a number
	}
	else {
		return true;		//a number
	}
}

int Parser::convertStringNumberToInt(string input){
	stringstream convetor;
	int number;

	convetor << input;
	convetor >> number;

	return number;
}

bool Parser::isTimeKeywordsFound(string & input){
	string timekeyword;
	int const SKIP_NEXT = 5;
	string const NEXT("next");
	string temp;

	transform(input.begin(), input.end(), input.begin(), ::tolower);	//change position, optimaize this one?
	size_t found = input.rfind(DATE_TIME_DELIMITER);

	if (found != string::npos) {
		temp = input.substr(found + 1);
		timekeyword = temp.substr(0, temp.find_first_of(" "));

		if (timekeyword == NEXT) {
			temp = input.substr(input.rfind(NEXT) + SKIP_NEXT);
			timekeyword = temp.substr(0, temp.find_first_of(" "));

			if (isTimeKeywordsValid(timekeyword) == true) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			if (isTimeKeywordsValid(timekeyword) == true) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else {
		return false;
	}
}

bool Parser::isTimeKeywordsValid(string input){
	stringstream yearConvetor;
	int year;
	yearConvetor << input;
	yearConvetor >> year;

	if (yearConvetor.fail()) {
		for (int i = 0; i < DATE_KEYWORDS_SIZE; i++) {
			if (DATE_KEYWORDS[i] == input) {
				return true;
			}
		}
		return false;
	}
	else {
		if (year <= 2999 && year >= 2000) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Parser::isLeapYear(int input){
	return (((input % 400) == 0) || (input % 4) == 0) && (((input % 100) != 0));
}

int Parser::numberOfDaysInMonth(int year, int month){
	if ((month <= 0) || (month > 12)) {
		return 0;
	}
	else {
		if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
			return 30;
		}
		else {
			if (month == 2 && isLeapYear(year)) {
				return 29;
			}
			else {
				if (month == 2 && !isLeapYear(year)) {
					return 28;
				}
				else {
					return 31;
				}
			}
		}
	}
}

void Parser::solveDayOverFlow(int & year, int & month, int & day){
	if ((day > 31) && (month == 12)) {
		day -= 31;
		month = 1;
		year++;
	}

	if (day > numberOfDaysInMonth(year, month)) {
		day -= numberOfDaysInMonth(year, month);
		month++;
	}
}

void Parser::solveNextWeekDays(int & year, int & month, int & day){

}

void Parser::parse(string input, vector<string> &output){
	setCommand(input);
	setDescription(input);
	setTime(input);
	setIndex();

	if (_outputStartDateAndTime.empty() && _outputEndtDateAndTime.empty()) {
		//editName
		if (!_description.empty() && !_index.empty()) {
			_command = _command + "Name";
			output.push_back(_command);
			output.push_back(_index);
			output.push_back(_description);
		}
		else {
			//show
			if (_description.empty() && _index.empty()) {
				output.push_back(_command);
				
			}
			else {
				//search
				if (_index.empty()) {
					output.push_back(_command);
					output.push_back(_description);
				}
				else {
					//done,delete
					if (_description.empty()) {
						output.push_back(_command);
						output.push_back(_index);
					}
				}
			}
		}
	}
	else {
		//editTime
		if (_description.empty()) {
			_command = _command + "Time";
			output.push_back(_command);
			output.push_back(_index);
			output.push_back(_outputStartDateAndTime);
			output.push_back(_outputEndtDateAndTime);
		}
		else {
			//add deadline
			if (_outputStartDateAndTime.empty()) {
				output.push_back(_command);
				output.push_back(_description);
				output.push_back(_outputEndtDateAndTime);
			}
			else {
				//add task
				output.push_back(_command);
				output.push_back(_description);
				output.push_back(_outputStartDateAndTime);
				output.push_back(_outputEndtDateAndTime);
			}
		}
	}
	return;
}