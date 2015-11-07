#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandTest
{
	TEST_CLASS(UndoCommandTest)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			UndoCommand* cmd;
			cmd = new UndoCommand();

		}

		/*TEST_METHOD(NoReversibleCommandTest)
		{
			const string MSG_NOTHING_TO_UNDO = "Nothing to undo";

			UndoCommand* cmd;
			cmd = new UndoCommand();

			DisplayStub displayList;
			StorageStub testStorage;
			HistoryStub history;

			vector<string> idealFeedback;
			vector<string> actualFeedback;

			cmd->execute(&testStorage, &displayList);

			actualFeedback = displayList.getCommandFeedback();
			idealFeedback.push_back(MSG_NOTHING_TO_UNDO);

			Assert::AreEqual(actualFeedback.size(), size_t(1));
			Assert::AreEqual(actualFeedback[0], idealFeedback[0]);
			
		}*/

		TEST_METHOD(OneReversibleCommandTest)
		{
			UndoCommand* cmd;
			cmd = new UndoCommand();

			DisplayStub displayList;
			StorageStub testStorage;
			HistoryStub history;
			ReversibleCommandStub reversibleCmd;

			vector<string> idealFeedback;
			vector<string> actualFeedback;

			history.pushCommand(&reversibleCmd);

			cmd->execute(&testStorage, &displayList);

			actualFeedback = displayList.getCommandFeedback();
			idealFeedback.push_back("Undo Complete");

			Assert::AreEqual(actualFeedback.size(), size_t(1));
			Assert::AreEqual(actualFeedback[0], idealFeedback[0]);
		}

		TEST_METHOD(TwoReversibleCommandsTest)
		{
			UndoCommand* cmd;
			cmd = new UndoCommand();

			DisplayStub displayList;
			StorageStub testStorage;
			HistoryStub history;
			ReversibleCommandStub reversibleCmd1;
			ReversibleCommandStub reversibleCmd2;

			vector<string> idealFeedback;
			vector<string> actualFeedback;
		
			history.pushCommand(&reversibleCmd1);
			history.pushCommand(&reversibleCmd2);
			idealFeedback.push_back("Undo Complete");

			for (int i = 0; i < 2; i++) {
				cmd->execute(&testStorage, &displayList);
				actualFeedback = displayList.getCommandFeedback();

				Assert::AreEqual(actualFeedback.size(), size_t(1));
				Assert::AreEqual(actualFeedback[0], idealFeedback[0]);
			}

		}

		TEST_METHOD(UndoAddCommandTest_DeleteEntry)
		{
			string testName = "Untimed task"; 

			ptime time1;
			ptime time2;


			DisplayStub displayList;
			StorageStub testStorage;
			//HistoryStub history;

			vector<Entry*> actualEventsList;
			vector<Entry*> actualTasksList;

			AddCommand addCmd(testName, time1, time2);
			addCmd.execute(&testStorage, &displayList);
			
			actualEventsList = testStorage.getEventsList();
			actualTasksList = testStorage.getTasksList();

			Assert::AreEqual(actualEventsList.size(), size_t(0));
			Assert::AreEqual(actualTasksList.size(), size_t(1));

			UndoCommand undoCmd;
			undoCmd.execute(&testStorage, &displayList);

			actualEventsList = testStorage.getEventsList();
			actualTasksList = testStorage.getTasksList();

			Assert::AreEqual(actualEventsList.size(), size_t(0));
			Assert::AreEqual(actualTasksList.size(), size_t(0));

		}

		TEST_METHOD(UndoAddCommandTest_SendFeedback)
		{
			string testName = "Untimed task";

			ptime time1;
			ptime time2;

			DisplayStub displayList;
			StorageStub testStorage;
			//HistoryStub history;

			vector<Entry*> actualEventsList;
			vector<Entry*> actualTasksList;

			vector<string> actualFeedback;
			vector<string> idealFeedback;

			idealFeedback.push_back("Undone");
			idealFeedback.push_back("Added");
			idealFeedback.push_back(testName);

			AddCommand addCmd(testName, time1, time2);
			addCmd.execute(&testStorage, &displayList);

			UndoCommand undoCmd;
			undoCmd.execute(&testStorage, &displayList);

			actualFeedback = displayList.getCommandFeedback();

			Assert::AreEqual(actualFeedback.size(), idealFeedback.size());
			
			for (int i = 0; i < idealFeedback.size(); i++) {
				Assert::AreEqual(actualFeedback[i], idealFeedback[i]);
			}
		}

		/*TEST_METHOD(UndoEditCommandTest_SendFeedback)
		{
			
			EntryType entryType = event;
			int taskID = 1;
			string newTitle = "New Name";
			ptime newStartDate;
			ptime newStartTime;
			ptime newEndDate;
			ptime newEndTime;
			EditCommand* editCmd = new EditCommand(entryType, taskID, newTitle, newStartDate, newStartTime, newEndDate, newEndTime);
			
			DisplayStub display;
			Entry* testOldEntry;
			string oldName = "Old Name";
			ptime t1;
			ptime t2;
			vector<Entry*> testEventList;

			testOldEntry = new Entry(oldName, t1, t2);
			testEventList.push_back(testOldEntry);
			display.updateDisplayEventList(testEventList);
			
			Storage testStorage;

			
			editCmd->execute(&testStorage, &display);
			//Assert::AreEqual(History::getSize(), size_t(1));
			
		}*/
		/*
		TEST_METHOD(UndoDeleteCommandTest) {
			EntryType entryType = event;
			int taskID = 1;
			DeleteCommand delCmd(entryType, taskID);

			DisplayStub display;
			Entry* testDeleteEntry;
			string name = "Old Name";
			ptime t1;
			ptime t2;
			vector<Entry*> testEventList;

			testDeleteEntry = new Entry(name, t1, t2);
			testEventList.push_back(testDeleteEntry);
			display.updateDisplayEventList(testEventList);
			

			Assert::AreEqual(display.getEventList().size(), size_t(1));
			Entry* actualDisplayEntry = (display.getEventList())[0];
			Assert::AreEqual(actualDisplayEntry->getTitle(), name);
			Entry* actualRetrievedEntry = display.retrieveEntry(entryType, taskID);
			Assert::AreEqual(actualRetrievedEntry->getTitle(), name);

			Storage testStorage;
			testStorage.addEvent(testDeleteEntry);
			
			delCmd.execute(&testStorage, &display);
			
			size_t storageSize = (testStorage.getEventList()).size();
			//Assert::AreEqual(storageSize, size_t(0));
		}
		*/

		TEST_METHOD(UndoDeleteCommandTest2) {
			EntryType entryType = event;
			int taskID = 0;
			DeleteCommand delCmd(entryType, taskID);

			Display display;
			Entry* testDeleteEntry;
			string name = "Old Name";
			ptime t1;
			ptime t2;
			vector<Entry*> testEventList;

			size_t historySize;
			Entry* actualStorageEntryAfterUndo;

			testDeleteEntry = new Entry(name, t1, t2);
			testEventList.push_back(testDeleteEntry);
			display.updateDisplayEventList(testEventList);

			// check that display has and returns the correct entry
			Assert::AreEqual(display.getEventList().size(), size_t(1));
			Entry* actualDisplayEntry = (display.getEventList())[0];
			Assert::AreEqual(actualDisplayEntry->getTitle(), name);
			Entry* actualRetrievedEntry = display.retrieveEntry(entryType, taskID);
			Assert::AreEqual(actualRetrievedEntry->getTitle(), name);

			Storage testStorage;
			testStorage.addEvent(testDeleteEntry);

			History::empty();

			vector<string> actualFeedbackAfterUndo;
			vector<string> idealFeedbackAfterUndo;


			//check storage size is 1, history size is 0
			size_t storageSize = (testStorage.getEventList()).size();
			Assert::AreEqual(storageSize, size_t(1));

			delCmd.execute(&testStorage, &display);

			//check storage size is 0
			storageSize = (testStorage.getEventList()).size();
			Assert::AreEqual(storageSize, size_t(0));

			historySize = History::getSize();
			Assert::AreEqual(historySize, size_t(1));

			idealFeedbackAfterUndo = display.getCommandFeedback();
			vector<string>::iterator front = idealFeedbackAfterUndo.begin();
			idealFeedbackAfterUndo.insert(front, "Undone");

			UndoCommand undoCmd;
			undoCmd.execute(&testStorage, &display);
			Assert::AreEqual(historySize, size_t(1));

			storageSize = (testStorage.getEventList()).size();
			Assert::AreEqual(storageSize, size_t(1));

			actualStorageEntryAfterUndo = (testStorage.getEventList())[0];
			Assert::AreEqual(actualStorageEntryAfterUndo->getTitle(), name);

			actualFeedbackAfterUndo = display.getCommandFeedback();

			Assert::AreEqual(actualFeedbackAfterUndo.size(), idealFeedbackAfterUndo.size());

			for (int i = 0; i < idealFeedbackAfterUndo.size(); i++) {
				Assert::AreEqual(actualFeedbackAfterUndo[i], idealFeedbackAfterUndo[i]);
			}
			
		}

		TEST_METHOD(DisplayRetrieveEntryTest)
		{
			EntryType entryType = event;
			int taskID = 1;
			DisplayStub display;

			Entry* actualOldEntry;
			Entry* idealOldEntry;
			vector<Entry*> testEventList;

			string oldName = "Old Name";
			ptime t1;
			ptime t2;
			
			idealOldEntry = new Entry(oldName, t1, t2);
			testEventList.push_back(idealOldEntry);
			display.updateDisplayEventList(testEventList);

			actualOldEntry = display.retrieveEntry(entryType, taskID);
			
			string entryName = actualOldEntry->getTitle();

			Assert::AreEqual(actualOldEntry->getTitle(), oldName);

			
		}

	};
}