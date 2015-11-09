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
		Entry* laterEntryOnDate1 = new Entry("laterEntryOnDate1", time1OnDate1, time2OnDate1);
		Entry* entryOnDate2 = new Entry("entryOnDate2", time1OnDate1, time2OnDate1);
		Entry* entryOnDate3 = new Entry("entryOnDate3", time1OnDate1, time2OnDate1);
		Entry* entryOnDate4 = new Entry("entryOnDate4", time1OnDate1, time2OnDate1);

		Entry* earlierTimedTaskOnDate1 = new Entry("earlierTimedTaskOnDate1", time1OnDate1);
		Entry* laterTimedTaskOnDate1 = new Entry("laterTimedTaskOnDate1", time2OnDate1);
		Entry* timedTaskOnDate2 = new Entry("timedTaskOnDate2", time1OnDate2);
		Entry* timedTaskOnDate3 = new Entry("timedTaskOnDate3", time1OnDate3);
		Entry* timedTaskOnDate4 = new Entry("timedTaskOnDate4", time1OnDate4);
		Entry* floatingTask1 = new Entry("floatingTask1");
		Entry* floatingTask2 = new Entry("floatingTask2");

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

		}

		TEST_METHOD(ShowCompleted)
		{

		}

		TEST_METHOD(ShowOverdue)
		{

		}

		void initializeHardcodedStorage(Storage* storage) {

		}

		void generateIdealDisplayByDate(Display* idealDisplay) {

		}

		void validateDisplay(Display actualDisplay, Display idealDisplay) {

		}
	};
}