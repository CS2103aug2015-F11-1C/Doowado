#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//@@author A0102794E
namespace SystemTest
{		
	//Test the execution of an add command from user input string to display
	//Pre-existing data is not read from a text file but directly hardcoded into storage
	TEST_CLASS(AddSingleTaskTest)
	{
	public:
		
		string taskName = "house cleaning";
		date testDate = date(2015, Nov, 10);
		ptime testStartTime;
		ptime testEndTime = ptime(testDate, hours(7));
		Entry testTask = Entry(taskName,testStartTime, testEndTime);

		Entry* sameDayEvent1;
		Entry* sameDayEvent2;
		Entry* futureDayEvent1;
		Entry* futureDayEvent2;

		Entry* sameDayTask1;
		Entry* floatingTask1;
		Entry* futureDayTask1;
		Entry* floatingTask2;

		// add a single task without initializing storage
		// validate the display
		TEST_METHOD(AddTask)
		{
			string userCommand = "add house cleaning on 10/11/2015 7";
			
			Logic logic;
			Display actualDisplay;
			Display idealDisplay;

			generateHardcodedDisplay(&idealDisplay);

			logic.initialiseProgram();
			logic.processCommand(userCommand);
			
			actualDisplay = *(logic.getDisplay());

			validateDisplay(actualDisplay, idealDisplay);
		}

		// initialize storage with a few hard-coded entries
		// add a single task 
		// validate the display
		TEST_METHOD(AddTasktoNonEmptyStorageTest)
		{			
			Logic logic;
			Display actualDisplay;
			Display idealDisplay;

			string userCommand = "add house cleaning on 10/11/2015 7";
			initializeHardcodedStorage(&logic);

			generateHardcodedDisplayForNonEmptyStorage(&idealDisplay);

			logic.processCommand(userCommand);

			actualDisplay = *(logic.getDisplay());

			validateDisplay(actualDisplay, idealDisplay);
		}

		void initializeHardcodedStorage(Logic* logic) {
			Storage* storage = logic->getStorage();
			vector<Entry*> hardcodedEventList;
			vector<Entry*> hardcodedTaskList;

			date futureDate = date(2015, Nov, 12);

			ptime sameDayStartTime1 = ptime(testDate, hours(1));
			ptime sameDayStartTime2 = ptime(testDate, hours(9));

			ptime sameDayEndTime1 = ptime(testDate, hours(2));
			ptime sameDayEndTime2 = ptime(testDate, hours(10));

			ptime futureDayStartTime1 = ptime(futureDate, hours(1));
			ptime futureDayStartTime2 = ptime(futureDate, hours(9));

			ptime futureDayEndTime1 = ptime(futureDate, hours(2));
			ptime futureDayEndTime2 = ptime(futureDate, hours(10));
			
			sameDayEvent1 = new Entry("sameDayEvent1", sameDayStartTime1, sameDayEndTime1);
			sameDayEvent2 = new Entry("sameDayEvent2", sameDayStartTime1, sameDayEndTime1);
			futureDayEvent1 = new Entry("futureDayEvent1", futureDayStartTime1, futureDayEndTime1);
			futureDayEvent2 = new Entry("futureDayEvent2", futureDayStartTime1, futureDayEndTime1);

			sameDayTask1 = new Entry("sameDayEvent1", sameDayEndTime1);
			floatingTask1 = new Entry("floatingTask1");
			futureDayTask1 = new Entry("futureDayEvent1", futureDayEndTime1);
			floatingTask2 = new Entry("floatingTask2");
			
			hardcodedEventList.push_back(sameDayEvent1);
			hardcodedEventList.push_back(sameDayEvent2);
			hardcodedEventList.push_back(futureDayEvent1);
			hardcodedEventList.push_back(futureDayEvent2);

			hardcodedTaskList.push_back(sameDayTask1);
			hardcodedTaskList.push_back(futureDayTask1);
			hardcodedTaskList.push_back(floatingTask1);
			hardcodedTaskList.push_back(floatingTask2);

			storage->setEventList(hardcodedEventList);
			storage->setTaskList(hardcodedTaskList);
		}

		void validateDisplay(Display actualDisplay, Display idealDisplay) {
			validateCmdFeedback(actualDisplay, idealDisplay);
			validateEventList(actualDisplay, idealDisplay);
			validateTaskList(actualDisplay, idealDisplay);
		}

		void generateHardcodedDisplay(Display* idealDisplay) {
			
			vector<string> idealCmdFeedback;
			vector<Entry*> idealDisplayEventList;
			vector<Entry*> idealDisplayTaskList;

			idealCmdFeedback.push_back("Added");
			idealCmdFeedback.push_back(taskName);
			idealCmdFeedback.push_back(to_simple_string(testEndTime));

			idealDisplayTaskList.push_back(&testTask);

			idealDisplay->updateCommandFeedback(idealCmdFeedback);
			idealDisplay->updateDisplayEventList(idealDisplayEventList);
			idealDisplay->updateDisplayTaskList(idealDisplayTaskList);
			return;
		}

		void generateHardcodedDisplayForNonEmptyStorage(Display* idealDisplay) {

			vector<string> idealCmdFeedback;
			vector<Entry*> idealDisplayEventList;
			vector<Entry*> idealDisplayTaskList;

			idealCmdFeedback.push_back("Added");
			idealCmdFeedback.push_back(taskName);
			idealCmdFeedback.push_back(to_simple_string(testEndTime));

			idealDisplayEventList.push_back(sameDayEvent1);
			idealDisplayEventList.push_back(sameDayEvent2);
			
			idealDisplayTaskList.push_back(sameDayTask1);
			idealDisplayTaskList.push_back(&testTask);
			idealDisplayTaskList.push_back(floatingTask1);
			idealDisplayTaskList.push_back(floatingTask2);

			idealDisplay->updateCommandFeedback(idealCmdFeedback);
			idealDisplay->updateDisplayEventList(idealDisplayEventList);
			idealDisplay->updateDisplayTaskList(idealDisplayTaskList);
			return;
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