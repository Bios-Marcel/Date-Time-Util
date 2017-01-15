#include <a_samp>
#include <DateUtil\DateUtil>

public OnFilterScriptInit()
{
	print("Start Date / Time Util Unit Testing");
	assertThat("IsDateInPast", IsDateInPast(2017, 1, 1), true);
	assertThat("IsDateInPast", IsDateInPast(2107, 12, 1), false);

	assertThat("IsTimeInPast", IsTimeInPast(24, 1, 1), -1);

	assertThat("IsTimeInPastOf", IsTimeInPastOf(0, 56, 59, 23, 55, 59), true);
	assertThat("IsTimeInPastOf", IsTimeInPastOf(23, 50, 59, 23, 55, 59), true);
	assertThat("IsTimeInPastOf", IsTimeInPastOf(23, 56, 59, 23, 55, 59), false);

	assertThat("IsTimeInPastOf", IsDateTimeInPast(2017, 1, 1, 1, 1, 1), true);
	assertThat("IsTimeInPastOf", IsDateTimeInPast(2117, 1, 1, 1, 1, 1), false);
	print("End Unit Testing of Date / Time Util");
}

assertThat(title[], condition, expectedResult)
{
	if(condition == expectedResult)
	{
		return true;
	}

	printf("%s: Expected: %d Result: %d", title, expectedResult, condition);	
	return false;
}