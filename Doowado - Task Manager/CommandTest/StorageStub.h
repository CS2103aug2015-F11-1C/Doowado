#pragma once
#include "Storage.h"
class StorageStub: public Storage
{
public:
	StorageStub();
	~StorageStub();

	void displayByDate(vector<Event*>*, vector<Task*>*, date);
	vector<Event*> getEventsList();
};

