#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest{
	TEST_CLASS(ParserTest){
	public:
	
		//add floating task
		TEST_METHOD(parseTest1) {
			Parser parse;
			ParserResult output;
			string input = "add watch harry potter";
			string expectedCommand = "add";
			string expectedDescription = "watch harry potter";
			string expectedEntryType = "";
			int expectedIndex;
			string expectedStartDate = "";
			string expectedStartTime = "";
			string expectedEndDate = "";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription);
		}

		//add deadline event
		TEST_METHOD(parseTest2) {
			Parser parse;
			ParserResult output;
			string input = "add complete the man on monday by 31.12.2015";
			string expectedCommand = "add";
			string expectedDescription = "complete the man on monday";
			string expectedEntryType = "";
			int expectedIndex;
			string expectedStartDate = "";
			string expectedStartTime = "";
			string expectedEndDate = "20151231";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription);
			Assert::AreEqual(output.getEndDate()[0], expectedEndDate);
		}

		//add a task
		TEST_METHOD(parseTest3) {
			Parser parse;
			ParserResult output;
			string input = "add cs tutorial from 8/8/2015 1125 to 25/10/2015 1230";
			string expectedCommand = "add";
			string expectedDescription = "cs tutorial";
			string expectedEntryType = "";
			int expectedIndex;
			string expectedStartDate = "20150808";
			string expectedStartTime = "11:25:00";
			string expectedEndDate = "20151025";
			string expectedEndTime = "12:30:00";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription);
			Assert::AreEqual(output.getStartDate()[0], expectedStartDate);
			Assert::AreEqual(output.getStartTime()[0], expectedStartTime);
			Assert::AreEqual(output.getEndDate()[0], expectedEndDate);
			Assert::AreEqual(output.getEndTime()[0], expectedEndTime);
		}

		//add with quotation marks
		TEST_METHOD(parseTest4) {
			Parser parse;
			ParserResult output;
			string input = "   add    \"complete the man on monday\"    ";
			string expectedCommand = "add";
			string expectedDescription = "complete the man on monday";
			string expectedEntryType = "";
			int expectedIndex;
			string expectedStartDate = "";
			string expectedStartTime = "";
			string expectedEndDate = "";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription);
		}

		//edit description only
		TEST_METHOD(parseTest5) {
			Parser parse;
			ParserResult output;
			string input = "edit T29 i will go to IBD";
			string expectedCommand = "edit";
			string expectedDescription = "i will go to IBD";
			string expectedEntryType = "t";
			int expectedIndex = 29;
			string expectedStartDate = "";
			string expectedStartTime = "";
			string expectedEndDate = "";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription);
			Assert::AreEqual(output.getEntryType()[0], expectedEntryType);
			Assert::AreEqual(output.getIndex()[0], expectedIndex);
		}

		//edit starting time only
		TEST_METHOD(parseTest6) {
			Parser parse;
			ParserResult output;
			string input = "edit E29 st 8/aug/2015 0629";
			string expectedCommand = "edit";
			string expectedDescription = "";
			string expectedEntryType = "e";
			int expectedIndex = 29;
			string expectedStartDate = "20150808";
			string expectedStartTime = "06:29:00";
			string expectedEndDate = "";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getEntryType()[0], expectedEntryType);
			Assert::AreEqual(output.getIndex()[0], expectedIndex);
			Assert::AreEqual(output.getStartDate()[0], expectedStartDate);
			Assert::AreEqual(output.getStartTime()[0], expectedStartTime);
		}

		//edit ending time only 
		TEST_METHOD(parseTest7) {
			Parser parse;
			ParserResult output;
			string input = "edit E29 ed 25/oct/2015 915";
			string expectedCommand = "edit";
			string expectedDescription = "";
			string expectedEntryType = "e";
			int expectedIndex = 29;
			string expectedStartDate = "";
			string expectedStartTime = "";
			string expectedEndDate = "20151025";
			string expectedEndTime = "09:15:00";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getEntryType()[0], expectedEntryType);
			Assert::AreEqual(output.getIndex()[0], expectedIndex);
			Assert::AreEqual(output.getEndDate()[0], expectedEndDate);
			Assert::AreEqual(output.getEndTime()[0], expectedEndTime);
		}

		//edit both starting and ending time to null
		TEST_METHOD(parseTest8) {
			Parser parse;
			ParserResult output;
			string input = "edit t5 from null to null";
			string expectedCommand = "edit";
			string expectedDescription = "";
			string expectedEntryType = "t";
			int expectedIndex = 5;
			string expectedStartDate = "null";
			string expectedStartTime = "";
			string expectedEndDate = "null";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getEntryType()[0], expectedEntryType);
			Assert::AreEqual(output.getIndex()[0], expectedIndex);
			Assert::AreEqual(output.getStartDate()[0], expectedStartDate);
			Assert::AreEqual(output.getEndDate()[0], expectedEndDate);
		}

		//search for multiple keywords
		TEST_METHOD(parseTest9) {
			Parser parse;
			ParserResult output;
			string input = "search i|want| to|||go  |||   home";
			string expectedCommand = "search";
			string expectedDescription1 = "i";
			string expectedDescription2 = "want";
			string expectedDescription3 = "to";
			string expectedDescription4 = "go";
			string expectedDescription5 = "home";
	
			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription1);
			Assert::AreEqual(output.getDescription()[1], expectedDescription2);
			Assert::AreEqual(output.getDescription()[2], expectedDescription3);
			Assert::AreEqual(output.getDescription()[3], expectedDescription4);
			Assert::AreEqual(output.getDescription()[4], expectedDescription5);
		}

		//show for a range of date
		TEST_METHOD(parseTest10) {
			Parser parse;
			ParserResult output;
			string input = "show from 8/8/2015 1958 to 25/10/2015 2101";
			string expectedCommand = "show";
			string expectedDescription = "";
			string expectedEntryType = "";
			int expectedIndex = 5;
			string expectedStartDate = "20150808";
			string expectedStartTime = "19:58:00";
			string expectedEndDate = "20151025";
			string expectedEndTime = "21:1:00";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getStartDate()[0], expectedStartDate);
			Assert::AreEqual(output.getStartTime()[0], expectedStartTime);
			Assert::AreEqual(output.getEndDate()[0], expectedEndDate);
			Assert::AreEqual(output.getEndTime()[0], expectedEndTime);
		}

		//add a number only
		TEST_METHOD(parseTest11) {
			Parser parse;
			ParserResult output;
			string input = "add 629";
			string expectedCommand = "add";
			string expectedDescription1 = "629";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getDescription()[0], expectedDescription1);
		}

		TEST_METHOD(parseTest12) {
			Parser parse;
			ParserResult output;
			string input = "show 1.jan.2015";
			string expectedCommand = "show";
			string expectedDescription = "";
			string expectedEntryType = "";
			int expectedIndex;
			string expectedStartDate = "";
			string expectedStartTime = "";
			string expectedEndDate = "20150101";
			string expectedEndTime = "";

			output = parse.parse(input);

			Assert::AreEqual(output.getUserCommand(), expectedCommand);
			Assert::AreEqual(output.getEndDate()[0], expectedEndDate);
		}

		TEST_METHOD(removeExtraSpacePadding) {
			Parser parse;
			string input1 = "add finish ie4210 due by tmr";
			string expected1 = "add finish ie4210 due by tmr";
			string input2 = "      add finish ie4210 due by tmr        ";
			string expected2 = "add finish ie4210 due by tmr";

			Assert::AreEqual(parse.removeExtraSpacePadding(input1), expected1);
			Assert::AreEqual(parse.removeExtraSpacePadding(input2), expected2);
		}

		TEST_METHOD(isIndexVaild) {
			Parser parse;
			string input1 = "t1";
			string input2 = "T1";
			string input3 = "e1";
			string input4 = "E1";
			string input5 = "f1";

			Assert::IsTrue(parse.isIndexVaild(input1));
			Assert::IsTrue(parse.isIndexVaild(input2));
			Assert::IsTrue(parse.isIndexVaild(input3));
			Assert::IsTrue(parse.isIndexVaild(input4));
			Assert::IsFalse(parse.isIndexVaild(input5));
		}

		//valid input with delimiter "/"
		TEST_METHOD(extractYearMonthDayTest1) {
			Parser parse;
			string input = "12/10/2015";
			vector<int> result;
			int expectedYear = 2015;
			int expectedMonth = 10;
			int expectedDay = 12;

			result = parse.extractYearMonthDay(input);
			Assert::AreEqual(result[0], expectedYear);
			Assert::AreEqual(result[1], expectedMonth);
			Assert::AreEqual(result[2], expectedDay);
		}

		//valid input with delimiter "."
		TEST_METHOD(extractYearMonthDayTest2) {
			Parser parse;
			string input = "12.10.2015";
			vector<int> result;
			int expectedYear = 2015;
			int expectedMonth = 10;
			int expectedDay = 12;

			result = parse.extractYearMonthDay(input);
			Assert::AreEqual(result[0], expectedYear);
			Assert::AreEqual(result[1], expectedMonth);
			Assert::AreEqual(result[2], expectedDay);
		}

		//valid input with date and month only case 1
		TEST_METHOD(extractYearMonthDayTest3) {
			Parser parse;
			string input = "12/10";
			vector<int> result;
			int expectedYear = 2015;
			int expectedMonth = 10;
			int expectedDay = 12;

			result = parse.extractYearMonthDay(input);
			Assert::AreEqual(result[0], expectedYear);
			Assert::AreEqual(result[1], expectedMonth);
			Assert::AreEqual(result[2], expectedDay);
		}

		//valid input with date and month only case 2
		TEST_METHOD(extractYearMonthDayTest4) {
			Parser parse;
			string input = "12.oct";
			vector<int> result;
			int expectedYear = 2015;
			int expectedMonth = 10;
			int expectedDay = 12;

			result = parse.extractYearMonthDay(input);
			Assert::AreEqual(result[0], expectedYear);
			Assert::AreEqual(result[1], expectedMonth);
			Assert::AreEqual(result[2], expectedDay);
		}

		//valid input with day only
		TEST_METHOD(extractYearMonthDayTest5) {
			Parser parse;
			string input = "today";
			vector<int> result;
			vector<int> expected = parse.currentTime();

			result = parse.extractYearMonthDay(input);
			Assert::AreEqual(result[0], expected[0]);
			Assert::AreEqual(result[1], expected[1]);
			Assert::AreEqual(result[2], expected[2]);
		}

		//test for case where year, month and day are all changed
		TEST_METHOD(solveDayOverFlowTest1) {
			Parser parse;
	
			int inputYear = 2015;
			int inputMonth = 12;
			int inputDay = 37;
			int expectedYear = 2016;
			int expectedMonth = 1;
			int exprctedDay = 6;

			parse.solveDayOverFlow(inputYear, inputMonth, inputDay);
			Assert::AreEqual(inputYear, expectedYear);
			Assert::AreEqual(inputMonth, expectedMonth);
			Assert::AreEqual(inputDay, exprctedDay);
		}

		//test for case of febuary in leap year
		TEST_METHOD(solveDayOverFlowTest2) {
			Parser parse;

			int inputYear = 2016;
			int inputMonth = 2;
			int inputDay = 32;
			int expectedYear = 2016;
			int expectedMonth = 3;
			int exprctedDay = 3;

			parse.solveDayOverFlow(inputYear, inputMonth, inputDay);
			Assert::AreEqual(inputYear, expectedYear);
			Assert::AreEqual(inputMonth, expectedMonth);
			Assert::AreEqual(inputDay, exprctedDay);
		}

		//test for case of febuary in non leap year
		TEST_METHOD(solveDayOverFlowTest3) {
			Parser parse;

			int inputYear = 2015;
			int inputMonth = 2;
			int inputDay = 32;
			int expectedYear = 2015;
			int expectedMonth = 3;
			int exprctedDay = 4;

			parse.solveDayOverFlow(inputYear, inputMonth, inputDay);
			Assert::AreEqual(inputYear, expectedYear);
			Assert::AreEqual(inputMonth, expectedMonth);
			Assert::AreEqual(inputDay, exprctedDay);
		}

		//non leap year
		TEST_METHOD(numberOfDaysInMonthTest1) {
			Parser parse;
			int inputMonth1 = 2;
			int inputYear1 = 2015;
			int expected1 = 28;

			Assert::AreEqual(parse.numberOfDaysInMonth(inputYear1, inputMonth1), expected1);
		}

		//leap year
		TEST_METHOD(numberOfDaysInMonthTest2) {
			Parser parse;
			int inputMonth2 = 2;
			int inputYear2 = 2016;
			int expected2 = 29;
	
			Assert::AreEqual(parse.numberOfDaysInMonth(inputYear2, inputMonth2), expected2);
		}

		//month with 31
		TEST_METHOD(numberOfDaysInMonthTest3) {
			Parser parse;
			int inputMonth3 = 12;
			int inputYear3 = 2015;
			int expected3 = 31;

			Assert::AreEqual(parse.numberOfDaysInMonth(inputYear3, inputMonth3), expected3);
		}

		//month with 30
		TEST_METHOD(numberOfDaysInMonthTest4) {
			Parser parse;
			int inputMonth4 = 4;
			int inputYear4 = 2015;
			int expected4 = 30;

			Assert::AreEqual(parse.numberOfDaysInMonth(inputYear4, inputMonth4), expected4);
		}

		//invalid input
		TEST_METHOD(numberOfDaysInMonthTest5) {
			Parser parse;
			int inputMonth5 = 13;
			int inputYear5 = 2015;
			int expected5 = -1;

			Assert::AreEqual(parse.numberOfDaysInMonth(inputYear5, inputMonth5), expected5);
		}

		//non leap year
		TEST_METHOD(isLeapYearTest1) {
			Parser parse;
			int input1 = 2015;

			Assert::IsFalse(parse.isLeapYear(input1));
		}

		//leap year
		TEST_METHOD(isLeapYearTest2) {
			Parser parse;
			int input2 = 2016;

			Assert::IsTrue(parse.isLeapYear(input2));
		}

		//short form input
		TEST_METHOD(convertStringWeekdayToIntTest1) {
			Parser parse;
			string input1 = "fri";
			int expected1 = 5;

			Assert::AreEqual(parse.convertStringWeekdayToInt(input1), expected1);
		}

		//invalid input
		TEST_METHOD(convertStringWeekdayToIntTest2) {
			Parser parse;
			string input2 = "frii";
			int expected2 = -1;

			Assert::AreEqual(parse.convertStringWeekdayToInt(input2), expected2);
		}

		//full input
		TEST_METHOD(convertStringWeekdayToIntTest3) {
			Parser parse;
			string input3 = "friday";
			int expected3 = 5;

			Assert::AreEqual(parse.convertStringWeekdayToInt(input3), expected3);
		}

		//short form input
		TEST_METHOD(convertStringMonthToIntTest1) {
			Parser parse;
			string input1 = "jan";
			int expected1 = 1;

			Assert::AreEqual(parse.convertStringMonthToInt(input1), expected1);
		}

		//invalid input
		TEST_METHOD(convertStringMonthToIntTest2) {
			Parser parse;
			string input2 = "jann";
			int expected2 = -1;

			Assert::AreEqual(parse.convertStringMonthToInt(input2), expected2);
		}

		//full input
		TEST_METHOD(convertStringMonthToIntTest3) {
			Parser parse;
			string input3 = "january";
			int expected3 = 1;

			Assert::AreEqual(parse.convertStringMonthToInt(input3), expected3);
		}

		TEST_METHOD(isDayValidTest1) {
			Parser parse;
			string inputDay1 = "31";
			int inputMonth1 = 2;
			int inputYear1 = 2015;
			int expected1 = -1;

			Assert::AreEqual(parse.isDayValid(inputYear1, inputMonth1, inputDay1), expected1);
		}

		//boundary value test case 1
		TEST_METHOD(isDayValidTest2) {
			Parser parse;
			string inputDay2 = "28";
			int inputMonth2 = 2;
			int inputYear2 = 2015;
			int expected2 = 28;

			Assert::AreEqual(parse.isDayValid(inputYear2, inputMonth2, inputDay2), expected2);
		}

		//boundary value test case 2
		TEST_METHOD(isDayValidTest3) {
			Parser parse;
			string inputDay3 = "31";
			int inputMonth3 = 12;
			int inputYear3 = 2015;
			int expected3 = 31;

			Assert::AreEqual(parse.isDayValid(inputYear3, inputMonth3, inputDay3), expected3);
		}

		//boundary value test case 3
		TEST_METHOD(isDayValidTest4) {
			Parser parse;
			string inputDay4 = "0";
			int inputMonth4 = 12;
			int inputYear4 = 2015;
			int expected4 = -1;

			Assert::AreEqual(parse.isDayValid(inputYear4, inputMonth4, inputDay4), expected4);
		}

		//boundary value test case 4
		TEST_METHOD(isDayValidTest5) {
			Parser parse;
			string inputDay5 = "1";
			int inputMonth5 = 1;
			int inputYear5 = 2015;
			int expected5 = 1;

			Assert::AreEqual(parse.isDayValid(inputYear5, inputMonth5, inputDay5), expected5);
		}

		//boundary value test case 1
		TEST_METHOD(isMonthValidTest1) {
			Parser parse;
			string input1 = "12";
			int expected1 = 12;

			Assert::AreEqual(parse.isMonthValid(input1), expected1);
		}

		//boundary value test case 2
		TEST_METHOD(isMonthValidTest2) {
			Parser parse;
			//boundary value
			string input2 = "1";
			int expected2 = 1;

			Assert::AreEqual(parse.isMonthValid(input2), expected2);
		}

		//boundary value test case 3
		TEST_METHOD(isMonthValidTest3) {
			Parser parse;
			string input3 = "0";
			int expected3 = -1;

			Assert::AreEqual(parse.isMonthValid(input3), expected3);
		}

		//boundary value test case 4
		TEST_METHOD(isMonthValidTest4) {
			Parser parse;
			string input4 = "13";
			int expected4 = -1;

			Assert::AreEqual(parse.isMonthValid(input4), expected4);
		}

		//boundary value test case 1
		TEST_METHOD(isYearValidTest1) {
			Parser parse;
			string input2 = "2000";
			int expected2 = 2000;

			Assert::AreEqual(parse.isYearValid(input2), expected2);
		}

		//boundary value test case 2
		TEST_METHOD(isYearValidTest2) {
			Parser parse;
			string input3 = "2999";
			int expected3 = 2999;

			Assert::AreEqual(parse.isYearValid(input3), expected3);
		}

		//boundary value test case 3
		TEST_METHOD(isYearValidTest3) {
			Parser parse;
			string input4 = "3000";
			int expected4 = -1;

			Assert::AreEqual(parse.isYearValid(input4), expected4);
		}

		//boundary value test case 4
		TEST_METHOD(isYearValidTest4) {
			Parser parse;
			string input5 = "1999";
			int expected5 = -1;

			Assert::AreEqual(parse.isYearValid(input5), expected5);
		}

		//boundary value test case 1
		TEST_METHOD(extractTimeTest1) {
			Parser parse;
			string input = "2359";
			int expected = 2359;

			Assert::AreEqual(parse.extractTime(input), expected);
		}

		//boundary value test case 2
		TEST_METHOD(extractTimeTest2) {
			Parser parse;
			string input = "0000";
			int expected = 0;

			Assert::AreEqual(parse.extractTime(input), expected);
		}

		//boundary value test case 1
		TEST_METHOD(isTimeValidTest1) {
			Parser parse;
			int inputHour = 0;
			int inputMinute = 0;

			Assert::IsTrue(parse.isTimeValid(inputHour, inputMinute));
		}

		//boundary value test case 2
		TEST_METHOD(isTimeValidTest2) {
			Parser parse;
			int inputHour = 23;
			int inputMinute = 59;

			Assert::IsTrue(parse.isTimeValid(inputHour, inputMinute));
		}

		//boundary value test case 3
		TEST_METHOD(isTimeValidTest3) {
			Parser parse;
			int inputHour = 24;
			int inputMinute = 0;

			Assert::IsFalse(parse.isTimeValid(inputHour, inputMinute));
		}

		//boundary value test case 4
		TEST_METHOD(isTimeValidTest4) {
			Parser parse;
			int inputHour = 23;
			int inputMinute = 60;

			Assert::IsFalse(parse.isTimeValid(inputHour, inputMinute));
		}

		TEST_METHOD(fragmentizeStringTest1) {
			Parser parse;
			string input = "watch spy    bridge   tmr";
			vector<string> output;
			string expectedFirstWord = "watch";
			string expectedSecondtWord = "spy";
			string expectedThirdWord = "bridge";
			string expectedFourthWord = "tmr";

			output = parse.fragmentizeString(input);
			
			Assert::AreEqual(output[0], expectedFirstWord);
			Assert::AreEqual(output[1], expectedSecondtWord);
			Assert::AreEqual(output[2], expectedThirdWord);
			Assert::AreEqual(output[3], expectedFourthWord);
		}

		//with valid delimiter
		TEST_METHOD(findDateDelimiterPosTest1) {
			Parser parse;
			string input = "watch movie on mon";
			size_t expected = 12;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with invalid delimiter
		TEST_METHOD(findDateDelimiterPosTest2) {
			Parser parse;
			string input = "watch movie oon mon";
			size_t expected = string::npos;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//without a delimiter
		TEST_METHOD(findDateDelimiterPosTest3) {
			Parser parse;
			string input = "watch movie";
			size_t expected = string::npos;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with 2 delimitors occurrence
		TEST_METHOD(findDateDelimiterPosTest4) {
			Parser parse;
			string input = "watch the man on tuesday on mon 12";
			size_t expected = 25;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with quotation only
		TEST_METHOD(findDateDelimiterPosTest5) {
			Parser parse;
			string input = "\"watch the man on tue\"";
			size_t expected = string::npos;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with quotation followed by date & time keywords
		TEST_METHOD(findDateDelimiterPosTest6) {
			Parser parse;
			string input = "\"watch the man on tue\" fri 12";
			size_t expected = 21;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with quotation followed by delimiter and date & time keywords
		TEST_METHOD(findDateDelimiterPosTest7) {
			Parser parse;
			string input = "\"watch the man on tue\" on fri 12";
			size_t expected = 23;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with quotation followed by delimiter without space and date & time keywords
		TEST_METHOD(findDateDelimiterPosTest8) {
			Parser parse;
			string input = "\"watch the man on tue\"on fri 12";
			size_t expected = 21;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with quotation followed by invalid delimiter with space and date & time keywords
		TEST_METHOD(findDateDelimiterPosTest9) {
			Parser parse;
			string input = "\"watch the man on tue\" yo fri 12";
			size_t expected = string::npos;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		//with quotation followed by invalid delimiter without space and date & time keywords
		TEST_METHOD(findDateDelimiterPosTest10) {
			Parser parse;
			string input = "\"watch the man on tue\"yo fri 12";
			size_t expected = 21;

			Assert::AreEqual(parse.findDateDelimiterPos(input), expected);
		}

		TEST_METHOD(convertStringToIntTest1) {
			Parser parse;
			string input = "123";
			int expected = 123;

			Assert::AreEqual(parse.convertStringToInt(input), expected);
		}

	};
}