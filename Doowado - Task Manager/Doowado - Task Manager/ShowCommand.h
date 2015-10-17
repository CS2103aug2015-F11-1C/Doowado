#pragma once
#include "Command.h"

class ShowCommand
{
private:
	date _requestedDate;
public:
	ShowCommand();
	~ShowCommand();

	void execute(Storage* data, Display* display);
};

