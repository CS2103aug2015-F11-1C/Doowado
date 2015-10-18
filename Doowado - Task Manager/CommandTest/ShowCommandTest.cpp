#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandTest
{		
	TEST_CLASS(ShowCommandTest)
	{
	public:
		
		TEST_METHOD(ConstructorTest)
		{
			date testDate(2015,Oct,17);
			ptime t1;
			ptime t2;
			
			ShowCommand* cmd;
			cmd = new ShowCommand(testDate);

			Assert::AreEqual(1,1);
		}

	};
} 