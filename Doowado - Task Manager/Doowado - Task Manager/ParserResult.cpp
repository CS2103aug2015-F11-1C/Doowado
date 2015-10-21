#include "ParserResult.h"

ParserResult::ParserResult()
{
	//command & description
	_userCommand = "";
	_description.clear();
	_index.clear();
	_entryType.clear();

	//date
	_startDate.clear();
	_endDate.clear();

	//time
	_startTime.clear();
	_endTime.clear();
}

void ParserResult::setUserCommand(string userCommand){
	_userCommand = userCommand;
}

void ParserResult::setDescription(vector<string> description){
	_description = description;
}

void ParserResult::setIndex(vector<int> index){
	_index = index;
}

void ParserResult::setEntryType(vector<string> entryType){
	_entryType = entryType;
}

void ParserResult::setStartDate(vector<int> startYear, vector<int> startMonth, vector<int> startDay){

	if (!startYear.empty() && !startMonth.empty() && !startDay.empty()) {
		for (int i = 0; i < startYear.size(); i++) {
			ostringstream out;
			out << startYear[i];
			if (startMonth[i] < 10) {
				out << "0" << startMonth[i];
			}else {
				out << startMonth[i];
			}

			if (startDay[i] < 10) {
				out << "0" << startDay[i];
			}else {
				out << startDay[i];
			}
			_startDate.push_back(out.str());
		}
	}
}

void ParserResult::setEndDate(vector<int> endYear, vector<int> endMonth, vector<int> endDay){

	if (!endYear.empty() && !endMonth.empty() && !endDay.empty()) {
		for (int i = 0; i < endYear.size(); i++) {
			ostringstream out;
			out << endYear[i];
			if (endMonth[i] < 10) {
				out << "0" << endMonth[i];
			}
			else {
				out << endMonth[i];
			}

			if (endDay[i] < 10) {
				out << "0" << endDay[i];
			}
			else {
				out << endDay[i];
			}
			_endDate.push_back(out.str());
		}
	}
}

void ParserResult::setStartTime(vector<int> startTime){
	
	if (!startTime.empty()) {
		for (int i = 0; i < startTime.size(); i++) {
			ostringstream out;
			if (startTime[i] < 1000) {
				out << "0" << startTime[i];
				_startTime.push_back(out.str());
			}else {
				out << startTime[i];
				_startTime.push_back(out.str());
			}
		}
	}
}

void ParserResult::setEndTime(vector<int> endTime){

	if (!endTime.empty()) {
		for (int i = 0; i < endTime.size(); i++) {
			ostringstream out;
			if (endTime[i] < 1000) {
				out << "0" << endTime[i];
				_endTime.push_back(out.str());
			}else {
				out << endTime[i];
				_endTime.push_back(out.str());
			}
		}
	}
}

string& ParserResult::getUserCommand(){
	return _userCommand;
}

vector<string>& ParserResult::getDescription(){
	return _description;
}

vector<int>& ParserResult::getIndex(){
	return _index;
}

vector<string>& ParserResult::getEntryType(){
	return _entryType;
}

vector<string>& ParserResult::getStartDate(){
	return _startDate;
}

vector<string>& ParserResult::getEndDate(){
	return _endDate;
}

vector<string>& ParserResult::getStartTime(){
	return _startTime;
}

vector<string>& ParserResult::getEndTime(){
	return _endTime;
}

ParserResult::~ParserResult()
{
}
