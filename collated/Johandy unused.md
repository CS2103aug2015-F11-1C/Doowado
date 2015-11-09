# Johandy unused
###### Doowado - Task Manager\Entry.cpp
``` cpp

void Entry::printEvent()
{
	cout << setw(20) << left << _title;
	cout << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
}

void Entry::printTask()
{
	cout << setw(20) << left << _title;
	cout << " Due: " << setw(20) << to_simple_string(_endTime) << endl;
}

string Entry::toStringEvent()
{
	ostringstream eventSummary;
	eventSummary << setw(20) << left << _title;
	eventSummary << " Start: " << to_simple_string(_startTime) << " End: " << to_simple_string(_endTime) << endl;
	return eventSummary.str();
}

string Entry::toStringTask()
{
	ostringstream taskSummary;
	taskSummary << setw(20) << left << _title;
	taskSummary << " Due: " << setw(20) << to_simple_string(_endTime) << endl;
	return taskSummary.str();
}
```
