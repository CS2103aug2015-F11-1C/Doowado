#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandTest
{		
	TEST_CLASS(ShowCommandTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			date testDate(2015,Oct,17);
			ptime t1;
			ptime t2;
			
			ShowCommand* cmd;
			cmd = new ShowCommand(testDate);

			Assert::AreEqual(1,1);
		}

		TEST_METHOD(ShowEventTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			ShowCommand* cmd;
			cmd = new ShowCommand(testDate);

			DisplayStub displayList;
			StorageStub testStorage("TestFile.txt");

			Event event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Event*> idealEventsList;
			idealEventsList.push_back(&event1);

			vector<Event*> actualEventsList;

			cmd->execute(&testStorage, &displayList);
			
			actualEventsList = displayList.getEventsList();

			Assert::AreEqual(idealEventsList.size(), actualEventsList.size());
			
		}

	};
} 