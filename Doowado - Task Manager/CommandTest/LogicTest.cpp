#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	TEST_CLASS(LogicTest)
	{
	public:

		TEST_METHOD(AddEventToEmptyStorage)
		{
			//hard-coded event on 29 Oct 2015 from 5 to 7
			string testName = "Timed event";

			date testDate = date(2015, Oct, 29);
			ptime time1 = ptime(testDate, hours(5));
			ptime time2 = ptime(testDate, hours(7));
			ptime time3;

			Entry newEntry = Entry(testName, time1, time2);

			Display displayList;
			Storage testStorage;
			History history;

			vector<Entry*> ActualStorageEventList;
			vector<Entry*> ActualStorageTaskList;

			vector<Entry*> IdealStorageEventList;
			vector<Entry*> IdealStorageTaskList;
			IdealStorageEventList.push_back(&newEntry);

			AddCommand addCmd(testName, time1, time2, time3);

			addCmd.execute(&testStorage, &displayList);

			ActualStorageEventList = testStorage.getEventList();
			ActualStorageTaskList = testStorage.getTaskList();

			Assert::AreEqual(ActualStorageEventList.size(), IdealStorageEventList.size());
			Assert::AreEqual(ActualStorageTaskList.size(), IdealStorageTaskList.size());


			for (int i = 0; i < IdealStorageEventList.size(); i++) {
				Assert::IsTrue(areEqual(ActualStorageEventList[i], IdealStorageEventList[i]));
			}

			for (int i = 0; i < IdealStorageTaskList.size(); i++) {
				Assert::IsTrue(areEqual(ActualStorageTaskList[i], IdealStorageTaskList[i]));
			}

		}

		bool areEqual(Entry* entry1, Entry* entry2) {
			return(entry1->getTitle() == entry2->getTitle() 
				&&	entry1->getStartTime() == entry2->getStartTime() 
				&&  entry1->getEndTime() == entry2->getEndTime()
				);
		}
	};
}