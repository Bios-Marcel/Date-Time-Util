#include <a_samp>

//Just because i like it
#define isDateInPast IsDateInPast
#define isTimeInPast IsTimeInPast
#define isDateInPastOf IsTimeInPastOf
#define isTimeInPastOf IsDateInPastOf
#define isDateTimeInPast IsDateTimeInPastOf
#define isDateValid IsDateValid
#define isTimeValid IsTimeValid
#define isDateTimeValid IsDateTimeValid
#define isLeapYear IsLeapYear
#define getDaysOfMonth GetDaysOfMonth
#define dateToDays DateToDays
#define getTimeDiff GetTimeDiff
#define getDateDiff GetDateDiff

stock IsDateInPast(year, month = 99, day = 99)
{
	new actualDay, actualMonth, actualYear;
	getdate(actualYear, actualMonth, actualDay);

	return IsDateInPastOf(year, month, day, actualYear, actualMonth, actualDay);
}

stock IsTimeInPast(hour, minute = 99, second = 99)
{
	new actualHour, actualMinute, actualSecond;
	gettime(actualHour, actualMinute, actualSecond);

	return IsTimeInPastOf(hour, minute, second, acutalHour, actualMinute, actualSecond);
}

stock IsDateTimeInPastOf(year, month, day, hour, minute, second, year2, month2, day2, hour2, minute2, second2)
{
	return IsDateInPastOf(year, month, day, year2, month2, day2) && IsTimeInPastOf(hour, minute, second, hour2, minute2, second2);
}

stock IsDateTimeInPast(year, month, day, hour, minute, second)
{
	return IsDateInPast(year, month, day) && IsTimeInPast(hour, minute, second);
}


stock IsDateInPastOf(year, month = 99, day = 99, year2, month2 = 98, day2 = 98)
{
	if(!IsDateValid(year, month, day) || !IsDateValid(year2, month2, day2))
	{
		return -1;
	}

	return year < year2 || year == year2 && (month < month2 || (month == month2 && day < day2));
}

stock  IsTimeInPastOf(hour, minute = 99, second = 99, hour2, minute2 = 98, second2 = 98)
{
	if(!IsTimeValid(hour, minute, second) || !IsTimeValid(hour2, minute2, second2))
	{
		return -1;
	}

	return hour < hour2 || hour == hour2 && (minute < minute2 || (minute == minute2 && second < second))
}

stock IsLeapYear(year)
{
	return (year % 4) || ((year % 100 == 0) && (year % 400)) ? false : true;
}

stock GetDaysOfMonth(year, month)
{
	if(month < 1 || month > 12)
	{
		return -1;
	}

	return (month == 2) ? (28 + IsLeapYear(year)) : 31 - (month - 1) % 7 % 2;
}

stock IsDateValid(year, month, day)
{
	return month >= 1 && month <= 12 && day >= 1 && day <= GetDaysOfMonth(year, month);
}

stock IsTimeValid(hour, minute, seconds)
{
	return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && seconds <= 59;
}

stock IsDateTimeValid(year, month, day, hour, minute, second)
{
	return IsDateValid(year, month, day) && IsTimeValid(hour, minute, seconds);
}

stock DateToDays(year, month, day)
{
	if(!IsDateValid(year, month, day))
	{
		return -1;
	}	

	new days = 0;

	//Start at year 1 after christi
	for(new i = 1; i < year; i++)
	{
		days += IsLeapYear(i) ? 366 : 365;
	}

	for(new i = 1; i < month; i++)
	{
		days += GetDaysOfMonth(year, month);
	}

	days += day;

	return days;
}

stock GetDateDiff(year, month, day, year2, month2, day2)
{
	if(!IsDateValid(year, month, day) || !IsDateValid(year2, month2, day2))
	{
		return -1;
	}

	new difference = DateToDays(year, month, day) - DateToDays(year2, month2, day2);

	return difference < 0 ? difference * -1 : difference;
}

stock GetTimeDiff(hour, minute, second, hour2, minute2, second2)
{
	if(!IsTimeValid(hour, minute, second) || !IsTimeValid(hour2, minute2, second2))
	{
		return -1;
	}

	new difference = (((hour * 60 * 60) + (minute * 60) + seconds) - ((hour2 * 60 * 60) + (minute2 * 60) + seconds2));

	return difference < 0 ? difference * -1 : difference;
}