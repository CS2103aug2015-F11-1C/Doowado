#pragma once
#include "Storage.h"
class StorageStub: public Storage
{
public:
	StorageStub();
	~StorageStub();

	void displayByDate(vector<Entry*>*, vector<Entry*>*, date);
	vector<Entry*> getEventsList();
	vector<Entry*> getTasksList();
};

