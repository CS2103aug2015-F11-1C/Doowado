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
			UndoCommand* cmd;
			cmd = new UndoCommand();

			DisplayStub displayList;
			StorageStub testStorage;
			HistoryStub history;

			cmd->execute(&testStorage, &displayList, &history);

			Assert::AreEqual((displayList.getCommandFeedback()).size(), size_t(1));
		}


	};
}