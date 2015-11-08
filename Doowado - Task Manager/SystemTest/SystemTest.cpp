#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTest
{		
	TEST_CLASS(AddSingleTaskTest)
	{
		
	public:
		
		string taskName = "house cleaning";
		date d1 = date(2015, Nov, 10);
		ptime t1;
		ptime t2 = ptime(d1, hours(7));
		Entry testTask = Entry(taskName,t1, t2);

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

		TEST_METHOD(AddTasktoNonEmptyStorageTest)
		{			
			Logic logic;
			Display actualDisplay;
			Display idealDisplay;

			string userCommand = "add house cleaning on 10/11/2015 7";
			initializeHardcodedStorage(&logic);

			generateHardcodedDisplay(&idealDisplay);

			logic.initialiseProgram();
			logic.processCommand(userCommand);

			actualDisplay = *(logic.getDisplay());

			validateDisplay(actualDisplay, idealDisplay);
		}

		void initializeHardcodedStorage(Logic* logic) {
			Storage* storage = logic->getStorage();
			vector<Entry*> hardcodedEventList;
			vector<Entry*> hardcodedTaskList;
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
			idealCmdFeedback.push_back(to_simple_string(t2));

			idealDisplayTaskList.push_back(&testTask);

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