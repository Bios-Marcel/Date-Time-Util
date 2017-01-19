# Date-Time-Util

## What can i do with this library?

This library contains a bunch of utlitiy functions for Dates and Times. See the list [**here**](https://github.com/Bios-Marcel/DateUtil/wiki/Functions#functions)(Still incomplete).

## How do i install this?

It's very simple, just place the DateUtil.inc inside of your includes folder like this:

* pawno
 * includes
   * DateUtil.inc

and include it into your gamemode or filterscript like this:

```Pawn
#include <DateUtil>
```

## I am getting errors, it says that some functions are not defined!

You might get these errors because your code is outdated, to fix the problem try the following.

Add this:

```Pawn
#define USE_BWC
```

in front of this:

```Pawn
#include <DateUtil>
```

doing that will automatically include the backwards compatibility include, if it exists.

## Something is not working like it should!

If you happen to find any bugs or are encountering any problems, create an [**issue**](https://github.com/Bios-Marcel/Date-Time-Util/issues/new)


