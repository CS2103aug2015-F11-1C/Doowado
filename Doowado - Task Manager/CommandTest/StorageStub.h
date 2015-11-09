#pragma once
#include "Storage.h"

//@@author A0102794E

class StorageStub: public Storage
{
public:
	StorageStub();
	~StorageStub();

	void displayByDate(vector<Entry*>*, vector<Entry*>*, date);
	vector<Entry*> getEventsList();
	vector<Entry*> getTasksList();
};

