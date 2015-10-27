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

			cmd->execute(&testStorage, &displayList, &history);

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

			cmd->execute(&testStorage, &displayList, &history);

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
				cmd->execute(&testStorage, &displayList, &history);
				actualFeedback = displayList.getCommandFeedback();

				Assert::AreEqual(actualFeedback.size(), size_t(1));
				Assert::AreEqual(actualFeedback[0], idealFeedback[0]);
			}

		}

	};
}