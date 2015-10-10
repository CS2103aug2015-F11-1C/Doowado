#include "Entry.h"

Entry::Entry() {
	_name = "";
}

Entry::Entry(string name){
	_name = name;
}

string Entry::getName(){
	return _name;
}

void Entry::setName(string newName){
	_name = newName;
}