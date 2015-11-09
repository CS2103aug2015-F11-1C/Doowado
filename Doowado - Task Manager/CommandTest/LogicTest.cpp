#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{
	//Tests the overall function of logic with storage, starting with an add command
	// and validating history, storage and display
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

			Entry newEntry = Entry(testName, time1, time2);

			Display displayList;
			Storage testStorage;
			History history;

			vector<Entry*> actualStorageEventList;
			vector<Entry*> actualStorageTaskList;

			vector<Entry*> IdealStorageEventList;
			vector<Entry*> IdealStorageTaskList;
			IdealStorageEventList.push_back(&newEntry);

			vector<string> actualFeedback;
			vector<string> idealFeedback;
			idealFeedback.push_back("Added");
			idealFeedback.push_back(testName);
			idealFeedback.push_back(to_simple_string(time1));
			idealFeedback.push_back(to_simple_string(time2));

			vector<Entry*> actualDisplayEventList;
			vector<Entry*> idealDisplayEventList;
			idealDisplayEventList.push_back(&newEntry);

			vector<Entry*> actualDisplayTaskList;
			vector<Entry*> idealDisplayTaskList;

			AddCommand addCmd(testName, time1, time2);

			addCmd.execute(&testStorage, &displayList);

			// Check storage
			actualStorageEventList = testStorage.getEventList();
			actualStorageTaskList = testStorage.getTaskList();

			Assert::AreEqual(actualStorageEventList.size(), IdealStorageEventList.size());
			Assert::AreEqual(actualStorageTaskList.size(), IdealStorageTaskList.size());


			Assert::IsTrue(areSameList(actualStorageEventList, IdealStorageEventList));
			Assert::IsTrue(areSameList(actualStorageTaskList, IdealStorageTaskList));

			for (int i = 0; i < IdealStorageTaskList.size(); i++) {
				Assert::IsTrue(areEqual(actualStorageTaskList[i], IdealStorageTaskList[i]));
			}

			//Check history
			Assert::AreEqual(History::getSize(), size_t(1));

			//Check display
			actualFeedback = displayList.getCommandFeedback();
			Assert::IsTrue(areSameFeedback(actualFeedback, idealFeedback));

			actualDisplayEventList = displayList.getEventList();
			actualDisplayTaskList = displayList.getTaskList();

			Assert::AreEqual(actualDisplayEventList.size(), idealDisplayEventList.size());
			Assert::AreEqual(actualDisplayTaskList.size(), idealDisplayTaskList.size());

			Assert::IsTrue(areSameList(actualDisplayEventList, idealDisplayEventList));
			Assert::IsTrue(areSameList(actualDisplayTaskList, idealDisplayTaskList));
		}

		/*TEST_METHOD(AddTaskToEmptyStorage)
		{
			//hard-coded task on 29 Oct 2015 due 5
			string testName = "Timed task";

			date testDate = date(2015, Oct, 29);
			ptime time1 = ptime(testDate, hours(5));
			ptime time2;

			Entry newEntry = Entry(testName, time1, time2);

			Display displayList;
			Storage testStorage;
			History history;

			vector<Entry*> actualStorageEventList;
			vector<Entry*> actualStorageTaskList;

			vector<Entry*> IdealStorageEventList;
			vector<Entry*> IdealStorageTaskList;
			IdealStorageTaskList.push_back(&newEntry);

			vector<string> actualFeedback;
			vector<string> idealFeedback;
			idealFeedback.push_back("Added");
			idealFeedback.push_back(testName);
			idealFeedback.push_back(to_simple_string(time1));

			vector<Entry*> actualDisplayEventList;
			vector<Entry*> idealDisplayEventList;

			vector<Entry*> actualDisplayTaskList;
			vector<Entry*> idealDisplayTaskList;
			idealDisplayTaskList.push_back(&newEntry);

			AddCommand addCmd(testName, time1, time2);

			addCmd.execute(&testStorage, &displayList);

			// Check storage
			actualStorageEventList = testStorage.getEventList();
			actualStorageTaskList = testStorage.getTaskList();

			//Assert::AreEqual(actualStorageEventList.size(), IdealStorageEventList.size());
			Assert::AreEqual(actualStorageTaskList.size(), size_t(1));


			Assert::IsTrue(areSameList(actualStorageEventList, IdealStorageEventList));
			Assert::IsTrue(areSameList(actualStorageTaskList, IdealStorageTaskList));

			//Check history
			Assert::AreEqual(History::getSize(), size_t(1));

			//Check display
			actualFeedback = displayList.getCommandFeedback();
			Assert::IsTrue(areSameFeedback(actualFeedback, idealFeedback));

			actualDisplayEventList = displayList.getEventList();
			actualDisplayTaskList = displayList.getTaskList();

			Assert::AreEqual(actualDisplayEventList.size(), idealDisplayEventList.size());
			Assert::AreEqual(actualDisplayTaskList.size(), idealDisplayTaskList.size());

			Assert::IsTrue(areSameList(actualDisplayEventList, idealDisplayEventList));
			Assert::IsTrue(areSameList(actualDisplayTaskList, idealDisplayTaskList));
		}
		*/

		bool areEqual(Entry* entry1, Entry* entry2) {
			return(entry1->getTitle() == entry2->getTitle() 
				&&	entry1->getStartTime() == entry2->getStartTime() 
				&&  entry1->getEndTime() == entry2->getEndTime()
				);
		}

		bool areSameFeedback(vector<string> feedback1, vector<string> feedback2) {
			for (int i = 0; i < feedback2.size(); i++) {
				if (feedback1[i] != feedback2[i]) {
					return false;
				}
			}
			return true;
		}

		bool areSameList(vector<Entry*> list1, vector<Entry*> list2) {
			for (int i = 0; i < list2.size(); i++) {
				if (!areEqual(list1[i], list2[i])) {
					return false;
				}
			}
			return true;
		}
	};
}