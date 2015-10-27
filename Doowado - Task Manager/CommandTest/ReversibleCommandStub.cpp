#include "stdafx.h"
#include "ReversibleCommandStub.h"


ReversibleCommandStub::ReversibleCommandStub()
{
}


ReversibleCommandStub::~ReversibleCommandStub()
{
}

void ReversibleCommandStub::undo(Storage *storage, Display *display)
{
	vector<string> hardCodedFeedback;
	hardCodedFeedback.push_back("Undo Complete");
	display->updateCommandFeedback(hardCodedFeedback);
}