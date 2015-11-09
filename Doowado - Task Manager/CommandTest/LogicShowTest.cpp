#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicShowTest
{
	//Tests the overall function of logic with storage, starting with a show command
	// and validating display
	TEST_CLASS(LogicShowTest)
	{
		
	//create hard-coded entries on various dates
		date date1 = date(2015, Nov, 1);
		date date2 = date(2015, Nov, 2);
		date date3 = date(2015, Nov, 3);
		date date4 = date(2015, Nov, 4);

		ptime time1OnDate1 = ptime(date1, hours(1));
		ptime time2OnDate1 = ptime(date1, hours(2));
		ptime time3OnDate1 = ptime(date1, hours(3));

		ptime time1OnDate2 = ptime(date2, hours(1));
		ptime time2OnDate2 = ptime(date2, hours(2));
		
		ptime time1OnDate3 = ptime(date3, hours(1));
		ptime time2OnDate3 = ptime(date3, hours(2));
		
		ptime time1OnDate4 = ptime(date4, hours(1));
		ptime time2OnDate4 = ptime(date4, hours(2));

		Entry* earlierEntryOnDate1 = new Entry("earlierEntryOnDate1", time1OnDate1, time2OnDate1);
		Entry* laterEntryOnDate1 = new Entry("laterEntryOnDate1", time2OnDate1, time3OnDate1);
		Entry* entryOnDate2 = new Entry("entryOnDate2", time1OnDate2, time2OnDate2);
		Entry* entryOnDate3 = new Entry("entryOnDate3", time1OnDate3, time2OnDate3);
		Entry* entryOnDate4 = new Entry("entryOnDate4", time1OnDate4, time2OnDate4);

		Entry* earlierTimedTaskOnDate1 = new Entry("earlierTimedTaskOnDate1", time1OnDate1);
		Entry* laterTimedTaskOnDate1 = new Entry("laterTimedTaskOnDate1", time2OnDate1);
		Entry* timedTaskOnDate2 = new Entry("timedTaskOnDate2", time1OnDate2);
		Entry* timedTaskOnDate3 = new Entry("timedTaskOnDate3", time1OnDate3);
		Entry* timedTaskOnDate4 = new Entry("timedTaskOnDate4", time1OnDate4);
		Entry* floatingTask1 = new Entry("floatingTask1");
		Entry* floatingTask2 = new Entry("floatingTask2");


		//ShowByDate tests show for date1
			//all values trated the same way by this function
		//ShowByRangeOfDate tests show for date1 to date 3
			//two test events & tasks on date1 (start of range)
			//one test event & task on date 2 (within range)
			//one test event & task on date 3 (end of range)
			//one test event & task on date 4 (out of range)
			//two floating tasks (always shown in display by dates)
		//ShowCompleted tests display of completed tasks
			// two timed tasks on diff days and one floating task are marked done during initialization
			// checks that the display task list comprises of these three 
	

	public:

		TEST_METHOD(ShowByDate)
		{
			Storage storage;
			Display idealDisplay;
			Display actualDisplay;

			initializeHardcodedStorage(&storage);
			generateIdealDisplayByDate(&idealDisplay);

			ShowCommand showCmd(date1);
			showCmd.execute(&storage, &actualDisplay);

			validateDisplay(actualDisplay, idealDisplay);
		}

		TEST_METHOD(ShowByRangeOfDate)
		{
			Storage storage;
			Display idealDisplay;
			Display actualDisplay;
			initializeHardcodedStorage(&storage);

			generateIdealDisplayByRangeOfDate(&idealDisplay);

			ShowCommand showCmd(date1, date3);
			showCmd.execute(&storage, &actualDisplay);

			validateDisplay(actualDisplay, idealDisplay);
		}

		TEST_METHOD(ShowCompleted)
		{
			Storage storage;
			Display idealDisplay;
			Display actualDisplay;
			initializeHardcodedStorage(&storage);

			generateIdealDisplayByCompleted(&idealDisplay);

			ShowCommand showCmd(completed);
			showCmd.execute(&storage, &actualDisplay);

			validateDisplay(actualDisplay, idealDisplay);
		}

		TEST_METHOD(ShowOverdue)
		{

		}

		void initializeHardcodedStorage(Storage* storage) {
			vector<Entry*> hardcodedEventList;
			vector<Entry*> hardcodedTaskList;

			earlierTimedTaskOnDate1->setDone(true);
			timedTaskOnDate3->setDone(true);
			floatingTask1->setDone(true);

			hardcodedEventList.push_back(earlierEntryOnDate1);
			hardcodedEventList.push_back(laterEntryOnDate1);
			hardcodedEventList.push_back(entryOnDate2);
			hardcodedEventList.push_back(entryOnDate3);
			hardcodedEventList.push_back(entryOnDate4);

			hardcodedTaskList.push_back(earlierTimedTaskOnDate1);
			hardcodedTaskList.push_back(laterTimedTaskOnDate1);
			hardcodedTaskList.push_back(timedTaskOnDate2);
			hardcodedTaskList.push_back(timedTaskOnDate3);
			hardcodedTaskList.push_back(timedTaskOnDate4);
			hardcodedTaskList.push_back(floatingTask1);
			hardcodedTaskList.push_back(floatingTask2);

			storage->setEventList(hardcodedEventList);
			storage->setTaskList(hardcodedTaskList);
		}

		void generateIdealDisplayByDate(Display* idealDisplay) {
			vector<string> idealCmdFeedback;
			vector<Entry*> idealDisplayEventList;
			vector<Entry*> idealDisplayTaskList;

			idealCmdFeedback.push_back("Showing: ");
			idealCmdFeedback.push_back(to_simple_string(date1));

			idealDisplayEventList.push_back(earlierEntryOnDate1);
			idealDisplayEventList.push_back(laterEntryOnDate1);

			idealDisplayTaskList.push_back(earlierTimedTaskOnDate1);
			idealDisplayTaskList.push_back(laterTimedTaskOnDate1);
			idealDisplayTaskList.push_back(floatingTask1);
			idealDisplayTaskList.push_back(floatingTask2);


			idealDisplay->updateCommandFeedback(idealCmdFeedback);
			idealDisplay->updateDisplayEventList(idealDisplayEventList);
			idealDisplay->updateDisplayTaskList(idealDisplayTaskList);
		}

		void generateIdealDisplayByRangeOfDate(Display* idealDisplay) {
			vector<string> idealCmdFeedback;
			vector<Entry*> idealDisplayEventList;
			vector<Entry*> idealDisplayTaskList;

			idealCmdFeedback.push_back("Showing: ");
			idealCmdFeedback.push_back(to_simple_string(date1));
			idealCmdFeedback.push_back(to_simple_string(date3));

			idealDisplayEventList.push_back(earlierEntryOnDate1);
			idealDisplayEventList.push_back(laterEntryOnDate1);
			idealDisplayEventList.push_back(entryOnDate2);
			idealDisplayEventList.push_back(entryOnDate3);

			idealDisplayTaskList.push_back(earlierTimedTaskOnDate1);
			idealDisplayTaskList.push_back(laterTimedTaskOnDate1);
			idealDisplayTaskList.push_back(timedTaskOnDate2);
			idealDisplayTaskList.push_back(timedTaskOnDate3);
			idealDisplayTaskList.push_back(floatingTask1);
			idealDisplayTaskList.push_back(floatingTask2);


			idealDisplay->updateCommandFeedback(idealCmdFeedback);
			idealDisplay->updateDisplayEventList(idealDisplayEventList);
			idealDisplay->updateDisplayTaskList(idealDisplayTaskList);
		}

		void generateIdealDisplayByCompleted(Display* idealDisplay) {

		}

		//methods below are exactly the same as Display validation in SystemTest
		void validateDisplay(Display actualDisplay, Display idealDisplay) {
			//validateCmdFeedback(actualDisplay, idealDisplay);
			//validateEventList(actualDisplay, idealDisplay);
			//validateTaskList(actualDisplay, idealDisplay);
		}

		void validateCmdFeedback(Display actualDisplay, Display idealDisplay) {

			vector<string> actualFeedback = actualDisplay.getCommandFeedback();
			vector<string> idealFeedback = idealDisplay.getCommandFeedback();

			Assert::IsTrue(areSameFeedback(actualFeedback, idealFeedback));

		}

		void validateEventList(Display actualDisplay, Display idealDisplay) {
			vector<Entry*> actualEventList = actualDisplay.getEventList();
			vector<Entry*> idealEventList = idealDisplay.getEventList();

			Assert::AreEqual(actualEventList.size(), idealEventList.size());
			Assert::IsTrue(areSameEntryList(actualEventList, idealEventList, event));
		}

		void validateTaskList(Display actualDisplay, Display idealDisplay) {
			vector<Entry*> actualTaskList = actualDisplay.getTaskList();
			vector<Entry*> idealTaskList = idealDisplay.getTaskList();

			Assert::AreEqual(actualTaskList.size(), idealTaskList.size());
			Assert::IsTrue(areSameEntryList(actualTaskList, idealTaskList, task));
		}

		bool areSameFeedback(vector<string> feedback1, vector<string> feedback2) {
			Assert::AreEqual(feedback1.size(), feedback2.size());

			for (int i = 0; i < feedback2.size(); i++) {
				if (feedback1[i] != feedback2[i]) {
					return false;
				}
			}
			return true;
		}

		bool areSameEntry(Entry* entry1, Entry* entry2, EntryType entryType) {
			if (entryType == event) {
				return(entry1->getTitle() == entry2->getTitle()
					&& entry1->getStartTime() == entry2->getStartTime()
					&& entry1->getEndTime() == entry2->getEndTime());
			}
			if (entryType == task) {
				return(entry1->getTitle() == entry2->getTitle()
					&& entry1->getEndTime() == entry2->getEndTime()
					);
			}
		}

		bool areSameEntryList(vector<Entry*> list1, vector<Entry*> list2, EntryType entryType) {
			for (int i = 0; i < list2.size(); i++) {
				if (!areSameEntry(list1[i], list2[i], entryType)) {
					return false;
				}
			}
			return true;
		}

	};
}