#include <a_samp>

stock isDateInPast(year, month = 99, day = 99)
{
	new actualDay, actualMonth, actualYear;
	getdate(actualYear, actualMonth, actualDay);

	return isDateInPastOf(year, month, day, actualYear, actualMonth, actualDay);
}

stock isTimeInPast(hour, minute = 99, second = 99)
{
	new actualHour, actualMinute, actualSecond;
	gettime(actualHour, actualMinute, actualSecond);

	return isTimeInPastOf(hour, minute, second, acutalHour, actualMinute, actualSecond);
}

stock isDateTimeInPastOf(year, month, day, hour, minute, second, year2, month2, day2, hour2, minute2, second2)
{
	return isDateInPastOf(year, month, day, year2, month2, day2) && isTimeInPastOf(hour, minute, second, hour2, minute2, second2);
}

stock isDateInPastOf(year, month = 99, day = 99, year2, month2 = 98, day2 = 98)
{
	if(year < year2)
	{
		return true;
	}

	if(year == year2)
	{
		if(month < month2)
		{
			return true;
		}

		if(month == month2)
		{
			if(day < day2)
			{
				return true;
			}
		}
	}

	return false;
}

stock  isTimeInPastOf(hour, minute = 99, second = 99, hour2, minute2 = 98, second2 = 98)
{
	if(hour < hour2)
	{
		return true;
	}

	if(hour == hour2)
	{
		if(minute < minute2)
		{
			return true;
		}

		if(minute == minute2)
		{
			if(second < second2)
			{
				return true;
			}
		}
	}

	return false;
}