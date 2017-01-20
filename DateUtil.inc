#include <a_samp>

#if defined USE_BWC
	#tryinclude <DateUtil\DateUtilBWC>
	#tryinclude <DateUtilBWC>
#endif

//Start at year 1 after christi
#if !defined INITIAL_YEAR
	#define INITIAL_YEAR 1970
#endif

#define YYYY_DD_MM 0
#define YYYY_MM_DD 1
#define DD_MM_YYYY 2
#define MM_DD_YYYY 3

#define TIME_UNIT_HOUR 0
#define TIME_UNIT_MINUTE 1
#define TIME_UNIT_SECOND 2
#define TIME_UNIT_MILLISECOND 3

stock IsDateInPast(year, month, day)
{
	new actualDay, actualMonth, actualYear;
	getdate(actualYear, actualMonth, actualDay);

	return IsDateInPastOf(year, month, day, actualYear, actualMonth, actualDay);
}

stock IsTimeInPast(hour, minute, second)
{
	new actualHour, actualMinute, actualSecond;
	gettime(actualHour, actualMinute, actualSecond);

	return IsTimeInPastOf(hour, minute, second, actualHour, actualMinute, actualSecond);
}

stock IsDateTimeInPastOf(year, month, day, hour, minute, second, year2, month2, day2, hour2, minute2, second2)
{
	return IsDateInPastOf(year, month, day, year2, month2, day2) && IsTimeInPastOf(hour, minute, second, hour2, minute2, second2);
}

stock IsDateTimeInPast(year, month, day, hour, minute, second)
{
	return IsDateInPast(year, month, day) && IsTimeInPast(hour, minute, second);
}


stock IsDateInPastOf(year, month, day, year2, month2, day2)
{
	if(!IsDateValid(year, month, day) || !IsDateValid(year2, month2, day2))
	{
		return -1;
	}

	return year < year2 || year == year2 && (month < month2 || (month == month2 && day < day2));
}

stock  IsTimeInPastOf(hour, minute, second, hour2, minute2, second2)
{
	if(!IsTimeValid(hour, minute, second) || !IsTimeValid(hour2, minute2, second2))
	{
		return -1;
	}

	return hour < hour2 || hour == hour2 && (minute < minute2 || (minute == minute2 && second < second));
}

stock IsLeapYear(year)
{
	return (year % 4) || ((year % 100 == 0) && (year % 400)) ? false : true;
}

stock GetDaysOfYear(year)
{
	return IsLeapYear(year) ? 366 : 365;
}

stock GetDaysOfMonth(year, month)
{
	return (month < 1 || month > 12) ? -1 : (month == 2) ? (28 + IsLeapYear(year)) : 31 - (month - 1) % 7 % 2;
}

stock IsDateValid(year, month = 1, day = 1)
{
	return month >= 1 && month <= 12 && day >= 1 && day <= GetDaysOfMonth(year, month);
}

stock IsTimeValid(hour, minute = 0, second = 0, millisecond = 0)
{
	return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59 && millisecond >= 0 && millisecond <= 999;
}

stock IsDateTimeValid(year, month, day, hour, minute = 0, second = 0, millisecond = 0)
{
	return IsDateValid(year, month, day) && IsTimeValid(hour, minute, seconds, millisecond);
}

stock DateToDays(year, month, day, bool:validDate = false)
{
	if(!validDate)
	{
		if(!IsDateValid(year, month, day))
		{
			return -1;
		}	
	}

	new days = 0;

	for(new i = INITIAL_YEAR; i < year; i++)
	{
		days += GetDaysOfYear(i);
	}

	for(new i = 1; i < month; i++)
	{
		days += GetDaysOfMonth(year, i);
	}

	days += day;

	return days;
}

stock DaysToDate(days, &year, &month, &day)
{
	year = INITIAL_YEAR;
	day = month = 0;
	while(days > 0)
	{
		if(days >= 366)
		{
			year++;
			if(IsLeapYear(year))
			{
				days -= 366;
			}
			else
			{
				days -= 365;
			}
		}
		else if(days == 365)
		{
			year++;
			days -= 365;
		}
		else
		{
			while( days > 0)
			{
				for( new i = 1; i <= 12; i++)
				{
					new daysOfMonth = GetDaysOfMonth(year, i);
					if(days >= daysOfMonth)
					{
						month++;
						days -= daysOfMonth;
					}
					else
					{
						month++;
						day = days;
						days = 0;
						break;
					}
				}
			}
		}
	}
}

stock ConvertTimeUnitToTime(unitInput, time, &hour = 0, &minute = 0, &second = 0, &millisecond = 0)
{
	switch(unitInput)
	{
		case TIME_UNIT_HOUR:
		{
			hour = time;
			minute = second = millisecond = 0;
		}
		case TIME_UNIT_MINUTE:
		{
			hour = time / 60;
			minute = time % 60;
		}
		case TIME_UNIT_SECOND:
		{
			hour = time / 60 / 60;
			minute = time / 60 % 60;
			second = time % 60;
		}
		case TIME_UNIT_MILLISECOND:
		{
			hour = time / 1000 / 60 / 60;
			minute = time / 1000 / 60 % 60;
			second = time / 1000 % 60;
			millisecond = time % 1000;
		}
	}
}

stock ConvertTimeToTimeUnit(unitOutput, hour, minute = 0, second = 0, millisecond = 0)
{
	new converted = 0;

	if(unitOutput != TIME_UNIT_MILLISECOND)
	{
		converted = ConvertTimeToTimeUnit(TIME_UNIT_MILLISECOND, hour, minute, second, millisecond);
	}

	switch(unitOutput)
	{
		case TIME_UNIT_HOUR:
		{
			converted = converted / 1000 / 60 / 60;
		}
		case TIME_UNIT_MINUTE:
		{
			converted = converted / 1000 / 60;
		}
		case TIME_UNIT_SECOND:
		{
			converted = converted / 1000;
		}
		case TIME_UNIT_MILLISECOND:
		{
			converted = (hour * 60 * 60 * 1000) + (minute * 60 * 1000) + (second * 1000) + millisecond;
		}
	}

	return converted;
}

//TODO(MSC) Write Unit Tests
stock ConvertTimeUnitToTimeUnit(unitInput, unitOutput, time)
{
	switch(unitInput)
	{
		case TIME_UNIT_HOUR:
		{
			switch(unitOutput)
			{
				case TIME_UNIT_MINUTE:
				{
					time *= 60;
				}
				case TIME_UNIT_SECOND:
				{
					time = time * 60 * 60;
				}
				case TIME_UNIT_MILLISECOND:
				{
					time = time * 60 * 60 * 1000;
				}	
			}
		}
		case TIME_UNIT_MINUTE:
		{
			switch(unitOutput)
			{
				case TIME_UNIT_HOUR:
				{
					time /= 60;
				}
				case TIME_UNIT_SECOND:
				{
					time *= 60;
				}
				case TIME_UNIT_MILLISECOND:
				{
					time = time * 60 * 1000;
				}	
			}
		}
		case TIME_UNIT_SECOND:
		{
			switch(unitOutput)
			{
				case TIME_UNIT_HOUR:
				{
					time = time / 60 / 60;
				}
				case TIME_UNIT_MINUTE:
				{
					time /= 60;
				}
				case TIME_UNIT_MILLISECOND:
				{
					time *= 1000;
				}	
			}
		}
		case TIME_UNIT_MILLISECOND:
		{
			switch(unitOutput)
			{
				case TIME_UNIT_HOUR:
				{
					time = time / 1000 / 60 / 60;
				}
				case TIME_UNIT_MINUTE:
				{
					time = time / 1000 / 60;
				}
				case TIME_UNIT_SECOND:
				{
					time /= 1000;
				}
			}
		}	
	}

	return time;
}

stock GetDateDifference(year, month, day, year2, month2, day2)
{
	if(!IsDateValid(year, month, day) || !IsDateValid(year2, month2, day2))
	{
		return -1;
	}

	new difference = DateToDays(year, month, day) - DateToDays(year2, month2, day2);

	return difference < 0 ? difference * -1 : difference;
}

stock GetTimeDifference(hour, minute, second, hour2, minute2, second2) 
{
	if(!IsTimeValid(hour, minute, second) || !IsTimeValid(hour2, minute2, second2))
	{
		return -1;
	}

	new difference = (((hour * 60 * 60) + (minute * 60) + second) - ((hour2 * 60 * 60) + (minute2 * 60) + second2));

	return difference < 0 ? difference * -1 : difference;
}

stock IsTimeInRangeOf(hour, minute, second, hourEarlier, minuteEarlier, secondEarlier, hourLater, minuteLater, secondLater)
{
	if(hour < hourEarlier)
	{
		return 0;
	}

	if(hour == hourEarlier)
	{
		if(minute < minuteEarlier)
		{
			return 0;
		}
		
		if(minute == minuteEarlier)
		{
			if(second < secondEarlier)
			{
				return 0;
			}
		}
	}
	else
	{
		if(hour > hourLatest)
		{
			return 0;
		}
		
		if(hour <= hourlatest)
		{
			if(minute > minuteLater)
			{
				return 0;
			}
			
			if(minute <= minuteLater)
			{
				if(second > secondLater)
				{
					return 0;
				}
			}
		}		
	}

	return 1;
}

stock AddDaysToDate(&year, &month, &day, amount)
{
	new days = DateToDays(year, month, day);

	days += amount;

	DaysToDate(days, year, month, day);
	return days;
}

stock AddSecondsToTime(&hour, &minute, &second, amount)
{
	new newHour = hour;
	new newMinute = minute;
	new newSecond = second;
	new seconds = TimeToSeconds(newHour, newMinute, newSecond);
	sconds += amount;

	SecondsToTime(newHour, newMinute, newSecond);

	if(IsTimeValid(newHour, newMinute, newSecond))
	{
		hour = newHour;
		minute = newMinute;
		second = newSecond;
	}
}

//http://wiki.sa-mp.com/wiki/Code_Snippets#Split
static stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

stock StringToDate(&year, &month, &day, date[], dateFormat = YYYY_MM_DD , separator = '/')
{
	new data[3][5];
	split(date, data, separator);
	new number[3];

	number[0] = strval(data[0]);
	number[1] = strval(data[1]);
	number[2] = strval(data[2]);

	for(new i = 0; i < sizeof(number); i++)
	{
		if(number[i] == 0)
		{
			year = month = day = -1;
			return 0;
		}
	}

	switch(dateFormat)
	{
		case YYYY_DD_MM:
		{
			year = number[0];
			month = number[2];
			day = number[1];
		}
		case YYYY_MM_DD:
		{
			year = number[0];
			month = number[1];
			day = number[2];	
		}
		case DD_MM_YYYY:
		{
			year = number[2];
			month = number[1];
			day = number[0];
		}
		case MM_DD_YYYY:
		{
			year = number[2];
			month = number[0];
			day = number[1];
		}
		default:
		{
			year = month = day = -1;
			return 0;
		}
	}

	return 1;
}

stock DateToString(year, month, day, dateFormat = YYYY_MM_DD , separator = '/')
{
	new date[11];

	switch(dateFormat)
	{
		case YYYY_DD_MM:
		{
			format(date, sizeof(date), "%04d%c%02d%c%02d", year, separator, day, separator, month);
		}
		case YYYY_MM_DD:
		{
			format(date, sizeof(date), "%04d%c%02d%c%02d", year, separator, month, separator, day);
		}
		case DD_MM_YYYY:
		{
			format(date, sizeof(date), "%02d%c%02d%c%04d", day, separator, month, separator, year);
		}
		case MM_DD_YYYY:
		{
			format(date, sizeof(date), "%02d%c%02d%c%04d", month, separator, day, separator, year);
		}
		default:
		{
			return "";
		}
	}

	return date;
}