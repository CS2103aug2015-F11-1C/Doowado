#include "ShowCommand.h"

string ShowCommand::generateDisplayState(date startDate, date endDate)
{
	string displayState;

	if (startDate.is_not_a_date()) {
		int endDay = endDate.day();
		int endMonth = endDate.month();
		int endYear = endDate.year();
		int intEndDayOfWeek = endDate.day_of_week();
		string endDayOfWeek;
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

	else
	{
		int startDay = startDate.day();
		int startMonth = startDate.month();
		int startYear = startDate.year();
		int intStartDayOfWeek = startDate.day_of_week();
		string startDayOfWeek;
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

		displayState += " - " + startDayOfWeek + ", " + to_string(startDay) + "/" + to_string(startMonth) + "/" + to_string(startYear);
	}
	
	return displayState;
}

ShowCommand::ShowCommand(ptime requestedDate)
{
	_requestedDate = requestedDate;
}


ShowCommand::~ShowCommand()
{
}

void ShowCommand::execute(Storage * data, Display * display)
{
	data->retrieveByDate(_requestedDate, _requestedEventList, _requestedTaskList);

	display->updateDisplayEventList(_requestedEventList);
	display->updateDisplayTaskList(_requestedTaskList);

	generateFeedback();
	date startDate(not_a_date_time);
	date endDate = _requestedDate.date();
	string displayState = generateDisplayState(startDate, endDate);

	display->updateCommandFeedback(_feedback);
	display->setEventDisplayState(displayState);
	display->setTaskDisplayState(displayState);
}

void ShowCommand::generateFeedback()
{
	_feedback.push_back("Showing");
	_feedback.push_back(to_simple_string(_requestedDate));
}
