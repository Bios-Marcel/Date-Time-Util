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
	return year < year2 || year == year2 && (month < month2 || (month == month2 && day < day2));
}

stock  isTimeInPastOf(hour, minute = 99, second = 99, hour2, minute2 = 98, second2 = 98)
{
	return hour < hour2 || hour == hour2 && (minute < minute2 || (minute == minute2 && second < second))
}


stock isLeapYear(year)
{
	return (year % 4) || ((year % 100 == 0) && (year % 400)) ? false : true;
}

stock getDaysOfMonth(year, month)
{
	return (month == 2) ? (28 + isLeapYear(year)) : 31 - (month - 1) % 7 % 2;
}

stock isDateValid(year, month, day)
{
	return month >= 1 && month <= 12 && day >= 1 && day <= getDaysOfMonth(year, month);
}