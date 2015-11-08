#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandTest
{
	TEST_CLASS(StubTests)
	{
	public:

		TEST_METHOD(StorageStubAddEventTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			StorageStub testStorage;

			Entry event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Entry*> actualEventsList;

			actualEventsList = testStorage.getEventsList();

			Assert::AreEqual(actualEventsList.size(), size_t(1));

		}

		TEST_METHOD(StorageStubDisplayByDateTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));

			StorageStub testStorage;

			Entry event1("Sample event", t1, t2);
			testStorage.addEvent(&event1);

			vector<Entry*> actualEventsList;
			vector<Entry*> actualTaskList;

			testStorage.displayByDate(&actualEventsList, &actualTaskList, testDate);

			Assert::AreEqual(actualEventsList.size(), size_t(1));

		}


		TEST_METHOD(DisplayStubTest)
		{
			date testDate(2015, Oct, 18);
			ptime t1(testDate, hours(5) + minutes(30));
			ptime t2(testDate, hours(6) + minutes(30));
			Entry event1("Sample event", t1, t2);
			vector<Entry*> testEventsList;
			testEventsList.push_back(&event1);

			DisplayStub displayList;

			displayList.updateDisplayEventList(testEventsList);

			vector<Entry*> actualEventsList;
			actualEventsList = displayList.getEventsList();

			Assert::AreEqual(actualEventsList.size(), size_t(1));
		}
	};
}