#include <a_samp>
#include <Development\DevTools>
#include <DateUtil\DateUtil>

public OnFilterScriptInit()
{
	print("Start Date / Time Util Unit Testing");
	print(" ");

	TEST_SUITE_START_EX(IsDateInPast)
		assertThat("IsDateInPast(2017, 1, 1)", IsDateInPast(2017, 1, 1), true);
		assertThat("IsDateInPast(2107, 12, 1)", IsDateInPast(2107, 12, 1), false);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("IsDateInPast(2017, 1, 1)", IsDateInPast(2017, 1, 1), true);
		assertThat("IsDateInPast(2107, 12, 1)", IsDateInPast(2107, 12, 1), false);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("IsTimeInPast(24, 1, 1)", IsTimeInPast(24, 1, 1), -1);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("IsTimeInPastOf(0, 56, 59, 23, 55, 59)", IsTimeInPastOf(0, 56, 59, 23, 55, 59), true);
		assertThat("IsTimeInPastOf(23, 50, 59, 23, 55, 59)", IsTimeInPastOf(23, 50, 59, 23, 55, 59), true);
		assertThat("IsTimeInPastOf(23, 56, 59, 23, 55, 59)", IsTimeInPastOf(23, 56, 59, 23, 55, 59), false);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("IsDateTimeInPast(2017, 1, 1, 1, 1, 1)", IsDateTimeInPast(2017, 1, 1, 1, 1, 1), true);
		assertThat("IsDateTimeInPast(2117, 1, 1, 1, 1, 1)", IsDateTimeInPast(2117, 1, 1, 1, 1, 1), false);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("IsLeapYear(1803)", IsLeapYear(1803), false);
		assertThat("IsLeapYear(1803)", IsLeapYear(1804), true);
		assertThat("IsLeapYear(1803)", IsLeapYear(1805), false);
		assertThat("IsLeapYear(1803)", IsLeapYear(1806), false);
		assertThat("IsLeapYear(1803)", IsLeapYear(2016), true);
		assertThat("IsLeapYear(1803)", IsLeapYear(2017), false);
		assertThat("IsLeapYear(1803)", IsLeapYear(2018), false);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("GetDaysOfYear(1803)", GetDaysOfYear(1803), 365);
		assertThat("GetDaysOfYear(1804)", GetDaysOfYear(1804), 366);
		assertThat("GetDaysOfYear(1805)", GetDaysOfYear(1805), 365);
		assertThat("GetDaysOfYear(1806)", GetDaysOfYear(1806), 365);
		assertThat("GetDaysOfYear(2016)", GetDaysOfYear(2016), 366);
		assertThat("GetDaysOfYear(2017)", GetDaysOfYear(2017), 365);
		assertThat("GetDaysOfYear(2018)", GetDaysOfYear(2018), 365);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("GetDaysOfMonth(2016, 1)", GetDaysOfMonth(2016, 1), 31);
		assertThat("GetDaysOfMonth(2016, 2)", GetDaysOfMonth(2016, 2), 29);
		assertThat("GetDaysOfMonth(2017, 1)", GetDaysOfMonth(2017, 1), 31);
		assertThat("GetDaysOfMonth(2017, 2)", GetDaysOfMonth(2017, 2), 28);
		assertThat("GetDaysOfMonth(2017, 3)", GetDaysOfMonth(2017, 3), 31);
		assertThat("GetDaysOfMonth(2017, 4)", GetDaysOfMonth(2017, 4), 30);
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("IsDateValid(2017, 2, 1)", IsDateValid(2017, 1, 1), true);
		assertThat("IsDateValid(2017, 2, 1)", IsDateValid(2017, 12, 31), true);
		assertThat("IsDateValid(2017, 2, 1)", IsDateValid(2017, 2, 29), false);
		assertThat("IsDateValid(2017, 0, 1)", IsDateValid(2017, 0, 1), false);
		assertThat("IsDateValid(2017, 13, 1)", IsDateValid(2017, 13, 1), false);
		assertThat("IsDateValid(2017, 10, 0)", IsDateValid(2017, 10, 0), false);
	TEST_SUITE_END


	TEST_SUITE_START
		assertThat("IsTimeValid(24, 0, 0)", IsTimeValid(24, 0, 0), false);
		assertThat("IsTimeValid(25, 0, 0)", IsTimeValid(25, 0, 0), false);
		assertThat("IsTimeValid(-1, 0, 0)", IsTimeValid(-1, 0, 0), false);
		assertThat("IsTimeValid(23, 0, 0)", IsTimeValid(23, 0, 0), true);
		assertThat("IsTimeValid(1, 0, 0)", IsTimeValid(1, 0, 0), true);
		assertThat("IsTimeValid(0, 0, 0)", IsTimeValid(0, 0, 0), true);
		assertThat("IsTimeValid(23, 59, 59)", IsTimeValid(23, 59, 59), true);
		assertThat("IsTimeValid(23, 59, 60)", IsTimeValid(23, 59, 60), false);	
	TEST_SUITE_END

	TEST_SUITE_START
		new hour, minute, second;
		SecondsToTime(70, hour, minute, second);
		assertThat("SecondsToTime(70, X, Y, Z) - 1", hour, 0);
		assertThat("SecondsToTime(70, X, Y, Z) - 2", minute, 1);
		assertThat("SecondsToTime(70, X, Y, Z) - 3", second, 10);
		SecondsToTime(3920, hour, minute, second);
		assertThat("SecondsToTime(70, X, Y, Z) - 1", hour, 1);
		assertThat("SecondsToTime(70, X, Y, Z) - 2", minute, 5);
		assertThat("SecondsToTime(70, X, Y, Z) - 3", second, 20);	
	TEST_SUITE_END

	TEST_SUITE_START
		//TODO(MSC) More Tests (for more Time Units)
		assertThat("ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 1, 5, 20)", ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 1, 5, 20), 3920);
		assertThat("ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 0, 0, 0)", ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 0, 0, 0), 0);
		assertThat("ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 0, 0, 1)", ConvertTimeToTimeUnit(TIME_UNIT_SECOND, 0, 0, 1), 1);	
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("GetDateDiff(2017, 1, 1, 2017, 1, 5)", GetDateDiff(2017, 1, 1, 2017, 1, 5), 4);
		assertThat("GetDateDiff(2017, 1, 1, 2017, 1, 5)", GetDateDiff(2017, 1, 1, 2017, 1, 1), 0);	
	TEST_SUITE_END

	TEST_SUITE_START
		assertThat("GetTimeDiff(24, 0, 0, 0, 0, 0)", GetTimeDiff(24, 0, 0, 0, 0, 0), -1);
		assertThat("GetTimeDiff(0, 0, 0, 23, 0, 0)", GetTimeDiff(23, 0, 0, 0, 0, 0), 82800);
	TEST_SUITE_END

	print(" ");
	print("End Unit Testing of Date / Time Util");
}
