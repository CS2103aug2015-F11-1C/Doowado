#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DeleteCommandTest
{		
	TEST_CLASS(DeleteCommandTest)
	{
	public:
		
		//test for 
		TEST_METHOD(ConstructorTest)
		{
			// TODO: Your test code here
			EntryType entryType = event;
			int index = 1;

			DeleteCommand* cmd;
			cmd = new DeleteCommand(event, 1);

			Assert::IsTrue(entryType == cmd->getEntryType());
//			Assert::AreSame(index == cmd->getIndex());

		}

		//Test
		TEST_METHOD(ExecuteTest)
		{
			DeleteCommand* cmd = new DeleteCommand(event, 1);
			StorageStub* storageStub;
			DisplayStub* displayStub;
			cmd->execute(storageStub, displayStub);

			Event* eventEntry;
			string eventName = "Meeting";
			date date(2015, 10, 25);
			ptime startTime(date, hours(10));
			ptime endTime(date, hours(12) +minutes(30));

			eventEntry = new Event(eventName, startTime, endTime);
			storageStub->addEvent(eventEntry);
			
			vector<Event*> hardcodedEventList;
			hardcodedEventList.push_back(eventEntry);
			displayStub->updateDisplayEventList(hardcodedEventList);

			cmd->execute(storageStub, displayStub);

			Assert::IsTrue(eventEntry, cmd->getDeletedTask);
		}

	};
}