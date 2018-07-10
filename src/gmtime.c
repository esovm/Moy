/*
    module  : gmtime.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef GMTIME_X
#define GMTIME_C

/**
gmtime  :  I  ->  T
Converts a time I into a list T representing universal time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is false; weekday is 1 = Monday ... 7 = Sunday.
*/
#define PROCEDURE	do_gmtime
#define NAME		"gmtime"
#define FUNC		gmtime
#include "unmktime.h"
#endif
