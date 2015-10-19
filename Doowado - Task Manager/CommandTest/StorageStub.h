#pragma once
#include "Storage.h"
class StorageStub: public Storage
{
public:
	StorageStub(string saveDir);
	~StorageStub();

	void displayByDate(vector<Event*>*, vector<Task*>*, date);
};

