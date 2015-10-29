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

		TEST_METHOD(NoReversibleCommandTest)
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
			
		}

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

		TEST_METHOD(UndoAddCommandTest)
		{
			string testName = "Untimed task"; 

			ptime time1;
			ptime time2;
			ptime time3;

			DisplayStub displayList;
			StorageStub testStorage;
			//HistoryStub history;

			vector<Entry*> actualEventsList;
			vector<Entry*> actualTasksList;

			AddCommand addCmd(testName, time1, time2, time3);
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

	};
}