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
				endDayOfWeek = "Sun";
				break;
			case 1:
				endDayOfWeek = "Mon";
				break;
			case 2:
				endDayOfWeek = "Tue";
				break;
			case 3:
				endDayOfWeek = "Wed";
				break;
			case 4:
				endDayOfWeek = "Thu";
				break;
			case 5:
				endDayOfWeek = "Fri";
				break;
			case 6:
				endDayOfWeek = "Sat";
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
				startDayOfWeek = "Sun";
				break;
			case 1:
				startDayOfWeek = "Mon";
				break;
			case 2:
				startDayOfWeek = "Tue";
				break;
			case 3:
				startDayOfWeek = "Wed";
				break;
			case 4:
				startDayOfWeek = "Thu";
				break;
			case 5:
				startDayOfWeek = "Fri";
				break;
			case 6:
				startDayOfWeek = "Sat";
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
				endDayOfWeek = "Sun";
				break;
			case 1:
				endDayOfWeek = "Mon";
				break;
			case 2:
				endDayOfWeek = "Tue";
				break;
			case 3:
				endDayOfWeek = "Wed";
				break;
			case 4:
				endDayOfWeek = "Thu";
				break;
			case 5:
				endDayOfWeek = "Fri";
				break;
			case 6:
				endDayOfWeek = "Sat";
				break;
			default:
				break;
			}

			displayState += "-" + endDayOfWeek + ", " + to_string(endDay) + "/" + to_string(endMonth) + "/" + to_string(endYear);
		}
		
	}

	return displayState;
}
