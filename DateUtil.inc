#include <a_samp>

//Start at year 1 after christi
#if !defined INITIAL_YEAR
	#define INITIAL_YEAR 1
#endif

#define YYYY_DD_MM 0
#define YYYY_MM_DD 1
#define DD_MM_YYYY 2
#define MM_DD_YYYY 3

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

stock IsDateValid(year, month, day)
{
	return month >= 1 && month <= 12 && day >= 1 && day <= GetDaysOfMonth(year, month);
}

stock IsTimeValid(hour, minute, second)
{
	return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59;
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

stock TimeToSeconds(hour, minute, second)
{
	return (hour * 60 * 60) + (minute * 60) + second;
}

stock SecondsToTime(seconds, &hour, &minute, &second)
{
	hour = (seconds / 60) / 60;
	minute = (seconds / 60) % 60;
	second = seconds % 60;
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

	new difference = (((hour * 60 * 60) + (minute * 60) + second) - ((hour2 * 60 * 60) + (minute2 * 60) + second2));

	return difference < 0 ? difference * -1 : difference;
}

stock IsTimeInRangeOf(hour, minute, second, hourEarlier, minuteEarlier, secondEarlier, hourLater, minuteLater, secondLater)
{
	if(hour < hourEarlier)
	{
		return 0;
	}
	else if(hour == hourEarlier)
	{
		if(minute < minuteEarlier)
		{
			return 0;
		}
		else if(minute == minuteEarlier)
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
		else if(hour <= hourlatest)
		{
			if(minute > minuteLater)
			{
				return 0;
			}
			else if(minute <= minuteLater)
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