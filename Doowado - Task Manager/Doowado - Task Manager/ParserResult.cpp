#include "ParserResult.h"

void ParserResult::setUserCommand(string userCommand){
}

void ParserResult::setDescription(vector<string> description){
}

void ParserResult::setIndex(vector<int> index){
}

void ParserResult::setEntryType(vector<string> entryType){
}

void ParserResult::setStartDate(vector<int> startYear, vector<int> startMonth, vector<int> startDay){
}

void ParserResult::setEndDate(vector<int> endYear, vector<int> endMonth, vector<int> endDay){
}

void ParserResult::setStartTime(vector<int> startTime){
}

void ParserResult::setEndTime(vector<int> endTime){
}

string ParserResult::getUserCommand(){
	return _userCommand;
}

vector<string> ParserResult::getDescription(){
	return _description;
}

vector<int> ParserResult::getIndex(){
	return _index;
}

vector<string> ParserResult::getEntryType(){
	return _entryType;
}

vector<string> ParserResult::getStartDate(){
	return _startDate;
}

vector<string> ParserResult::getEndDate(){
	return _endDate;
}

vector<string> ParserResult::getStartTime(){
	return _startTime;
}

vector<string> ParserResult::getEndTime(){
	return _endTime;
}
