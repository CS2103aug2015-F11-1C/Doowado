#include "Command.h"

//@@author A0102794E

Command::Command()
{
}


Command::~Command()
{
}

void Command::execute(Storage* data, Display* display) {

}

void Command::undo(Storage * data, Display * display) {

}

//@@author A0114137R

std::string Command::generateDateDisplayState(ptime entryStartTime, ptime entryEndTime)
{
	std::string displayState;

	if (entryStartTime.is_not_a_date_time()) {
		if (!entryEndTime.is_not_a_date_time()) {
			date endDate = entryEndTime.date();

			int endDay = endDate.day();
			int endMonth = endDate.month();
			int endYear = endDate.year();
			int intEndDayOfWeek = endDate.day_of_week();
			std::string endDayOfWeek;

			switch (intEndDayOfWeek)
			{
			case 0:
				endDayOfWeek = "Sunday";
				break;
			case 1:
				endDayOfWeek = "Monday";
				break;
			case 2:
				endDayOfWeek = "Tuesday";
				break;
			case 3:
				endDayOfWeek = "Wednesday";
				break;
			case 4:
				endDayOfWeek = "Thursday";
				break;
			case 5:
				endDayOfWeek = "Friday";
				break;
			case 6:
				endDayOfWeek = "Saturday";
				break;
			default:
				break;
			}

			displayState = endDayOfWeek + ", " + to_string(endDay) + "/" + to_string(endMonth) + "/" + to_string(endYear);
		}
		else {
			displayState = "";
		}
	}
	else {
		if (!entryEndTime.is_not_a_date_time()) {
			date startDate = entryStartTime.date();

			int startDay = startDate.day();
			int startMonth = startDate.month();
			int startYear = startDate.year();
			int intStartDayOfWeek = startDate.day_of_week();

			std::string startDayOfWeek;

			switch (intStartDayOfWeek)
			{
			case 0:
				startDayOfWeek = "Sunday";
				break;
			case 1:
				startDayOfWeek = "Monday";
				break;
			case 2:
				startDayOfWeek = "Tuesday";
				break;
			case 3:
				startDayOfWeek = "Wednesday";
				break;
			case 4:
				startDayOfWeek = "Thursday";
				break;
			case 5:
				startDayOfWeek = "Friday";
				break;
			case 6:
				startDayOfWeek = "Saturday";
				break;
			default:
				break;
			}

			displayState = startDayOfWeek + ", " + to_string(startDay) + "/" + to_string(startMonth) + "/" + to_string(startYear);
		
			date endDate = entryEndTime.date();

			int endDay = endDate.day();
			int endMonth = endDate.month();
			int endYear = endDate.year();
			int intEndDayOfWeek = endDate.day_of_week();
			std::string endDayOfWeek;

			switch (intEndDayOfWeek)
			{
			case 0:
				endDayOfWeek = "Sunday";
				break;
			case 1:
				endDayOfWeek = "Monday";
				break;
			case 2:
				endDayOfWeek = "Tuesday";
				break;
			case 3:
				endDayOfWeek = "Wednesday";
				break;
			case 4:
				endDayOfWeek = "Thursday";
				break;
			case 5:
				endDayOfWeek = "Friday";
				break;
			case 6:
				endDayOfWeek = "Saturday";
				break;
			default:
				break;
			}

			displayState += "-" + endDayOfWeek + ", " + to_string(endDay) + "/" + to_string(endMonth) + "/" + to_string(endYear);
		}
		
	}

	return displayState;
}
