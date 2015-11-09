#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//@@author A0102794E

namespace CommandTest
{		
	TEST_CLASS(ShowCommandTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			date testDate(2015,Oct,17);
			
			ShowCommand* cmd;
			cmd = new ShowCommand(testDate);

			Assert::AreEqual(to_simple_string(cmd->_requestedEndDate),to_simple_string(testDate));
		}

		TEST_METHOD(ShowEventByDateTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			ShowCommand* cmd;
			cmd = new ShowCommand(testDate);

			DisplayStub displayList;
			StorageStub testStorage;

			Entry event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Entry*> idealEventsList;
			idealEventsList.push_back(&event1);

			vector<Entry*> actualEventsList;

			cmd->execute(&testStorage, &displayList);
			Assert::AreEqual((cmd->_requestedEventList).size(),size_t(1));
			
		}

	};
} 