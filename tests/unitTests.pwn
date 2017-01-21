#include <a_samp>
#include <Development\DevTools>
#include <DateUtil\DateUtil>

public OnFilterScriptInit()
{
	print("Start Date / Time Util Unit Testing");
	print("____________________________________________________________________________");
	print(" ");

	TEST_SUITE_START_EX(IsDateInPast)
		ASSERT(IsDateInPast(2017, 1, 1), true);
		ASSERT(IsDateInPast(2107, 12, 1), false);
	TEST_SUITE_END

	TEST_SUITE_START_EX(IsTimeInPast)
		ASSERT(IsTimeInPast(24, 1, 1), -1);
		ASSERT(IsTimeInPast(24, 0, 0), -1);
	TEST_SUITE_END

	TEST_SUITE_START_EX(IsTimeInPastOf)
		ASSERT(IsTimeInPastOf(0, 56, 59, 23, 55, 59), true);
		ASSERT(IsTimeInPastOf(23, 50, 59, 23, 55, 59), true);
		ASSERT(IsTimeInPastOf(23, 56, 59, 23, 55, 59), false);
	TEST_SUITE_END

	TEST_SUITE_START_EX(IsDateTimeInPast)
		ASSERT(IsDateTimeInPast(2017, 1, 1, 1, 1, 1), true);
		ASSERT(IsDateTimeInPast(2117, 1, 1, 1, 1, 1), false);
	TEST_SUITE_END

	TEST_SUITE_START_EX(IsLeapYear)
		ASSERT(IsLeapYear(1803), false);
		ASSERT(IsLeapYear(1804), true);
		ASSERT(IsLeapYear(1805), false);
		ASSERT(IsLeapYear(1806), false);
		ASSERT(IsLeapYear(2016), true);
		ASSERT(IsLeapYear(2017), false);
		ASSERT(IsLeapYear(2018), false);
	TEST_SUITE_END

	TEST_SUITE_START_EX(GetDaysOfYear)
		ASSERT(GetDaysOfYear(1803), 365);
		ASSERT(GetDaysOfYear(1804), 366);
		ASSERT(GetDaysOfYear(1805), 365);
		ASSERT(GetDaysOfYear(1806), 365);
		ASSERT(GetDaysOfYear(2016), 366);
		ASSERT(GetDaysOfYear(2017), 365);
		ASSERT(GetDaysOfYear(2018), 365);
	TEST_SUITE_END

	TEST_SUITE_START_EX(GetDaysOfMonth)
		ASSERT(GetDaysOfMonth(2016, 1), 31);
		ASSERT(GetDaysOfMonth(2016, 2), 29);
		ASSERT(GetDaysOfMonth(2017, 1), 31);
		ASSERT(GetDaysOfMonth(2017, 2), 28);
		ASSERT(GetDaysOfMonth(2017, 3), 31);
		ASSERT(GetDaysOfMonth(2017, 4), 30);
	TEST_SUITE_END

	TEST_SUITE_START_EX(IsDateValid)
		ASSERT(IsDateValid(2017, 1, 1), true);
		ASSERT(IsDateValid(2017, 12, 31), true);
		ASSERT(IsDateValid(2017, 2, 29), false);
		ASSERT(IsDateValid(2017, 0, 1), false);
		ASSERT(IsDateValid(2017, 13, 1), false);
		ASSERT(IsDateValid(2017, 10, 0), false);
	TEST_SUITE_END


	TEST_SUITE_START_EX(IsTimeValid)
		ASSERT(IsTimeValid(24, 0, 0), false);
		ASSERT(IsTimeValid(25, 0, 0), false);
		ASSERT(IsTimeValid(-1, 0, 0), false);
		ASSERT(IsTimeValid(23, 0, 0), true);
		ASSERT(IsTimeValid(1, 0, 0), true);
		ASSERT(IsTimeValid(0, 0, 0), true);
		ASSERT(IsTimeValid(23, 59, 59), true);
		ASSERT(IsTimeValid(23, 59, 60), false);	
	TEST_SUITE_END

	TEST_SUITE_START_EX(ConvertTimeUnitToTime)
		new hour, minute, second;
		ConvertTimeUnitToTime(TIME_UNIT_SECOND, 70, hour, minute, second);
		ASSERT_NO_PARAM(hour, 0);
		ASSERT_NO_PARAM(minute, 1);
		ASSERT_NO_PARAM(second, 10);
		ConvertTimeUnitToTime(TIME_UNIT_SECOND, 3920, hour, minute, second);
		ASSERT_NO_PARAM(hour, 1);
		ASSERT_NO_PARAM(minute, 5);
		ASSERT_NO_PARAM(second, 20);	
	TEST_SUITE_END

	TEST_SUITE_START_EX(ConvertTimeToTimeUnit)
		//TODO(MSC) More Tests (for more Time Units)
		ASSERT(ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 1, 5, 20), 3920);
		ASSERT(ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 0, 0, 0), 0);
		ASSERT(ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 0, 0, 1), 1);	
	TEST_SUITE_END

	TEST_SUITE_START_EX(GetDateDifference)
		ASSERT(GetDateDifference(2017, 1, 1, 2017, 1, 5), 4);
		ASSERT(GetDateDifference(2017, 1, 1, 2017, 1, 1), 0);	
	TEST_SUITE_END

	TEST_SUITE_START_EX(GetTimeDifference)
		ASSERT(GetTimeDifference(24, 0, 0, 0, 0, 0), -1);
		ASSERT(GetTimeDifference(23, 0, 0, 0, 0, 0), 82800);
	TEST_SUITE_END

	TEST_SUITE_START_EX(GetDayOfWeekName)
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 0, 1)), "");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 1)), "Sunday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 2)), "Monday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 3)), "Tuesday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 4)), "Wednesday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 5)), "Thursday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 6)), "Friday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 7)), "Saturday");
		ASSERT_STRING(GetDayOfWeekName(GetDayOfWeek(2017, 1, 8)), "Sunday");
	TEST_SUITE_END

	TEST_SUITE_START_EX(DateToString)
		ASSERT_STRING(DateToString(2017, 1, 1), "2017/01/01");
		ASSERT_STRING(DateToString(2017, 1, 2, DD_MM_YYYY, '-'), "02-01-2017");
		ASSERT_STRING(DateToString(2017, 1, 2, MM_DD_YYYY, '-'), "01-02-2017");
		ASSERT_STRING(DateToString(2017, 1, 2, YYYY_DD_MM, '-'), "2017-02-01");
		ASSERT_STRING(DateToString(17, 1, 2, YYYY_DD_MM, '\\'), "0017\\02\\01");
	TEST_SUITE_END

	print(" ");
	print("____________________________________________________________________________");
	print(" ");
	print("End Unit Testing of Date / Time Util");
	// SendRconCommand("exit");
}
