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
			ptime t1(testDate);
			ptime t2;
			
			ShowCommand* cmd;
			cmd = new ShowCommand(t1);

			Assert::AreEqual(to_simple_string(cmd->_requestedDate),to_simple_string(t1));
		}

		TEST_METHOD(ShowEventTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			ShowCommand* cmd;
			cmd = new ShowCommand(t1);

			DisplayStub displayList;
			StorageStub testStorage;

			Event event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Event*> idealEventsList;
			idealEventsList.push_back(&event1);

			vector<Event*> actualEventsList;

			cmd->execute(&testStorage, &displayList);
			Assert::AreEqual((cmd->_requestedEventList).size(),size_t(1));
	
			
		}


		TEST_METHOD(StorageStubAddEventTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			StorageStub testStorage;

			Event event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Event*> actualEventsList;

			actualEventsList = testStorage.getEventsList();

			Assert::AreEqual(actualEventsList.size(), size_t(1));

		}

		TEST_METHOD(StorageStubDisplayByDateTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			StorageStub testStorage;

			Event event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Event*> actualEventsList;
			vector<Task*> actualTaskList;

			testStorage.displayByDate(&actualEventsList, &actualTaskList, testDate);

			Assert::AreEqual(actualEventsList.size(), size_t(1));

		}


		TEST_METHOD(DisplayStubTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));
			Event event1("Sample event", t1, t2);
			vector<Event*> testEventsList;
			testEventsList.push_back(&event1);
			
			DisplayStub displayList;

			displayList.updateDisplayEventList(testEventsList);

			vector<Event*> actualEventsList;
			actualEventsList = displayList.getEventsList();

			Assert::AreEqual(actualEventsList.size(), size_t(1));
		}
	};
} 