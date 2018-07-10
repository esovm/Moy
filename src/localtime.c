/*
    module  : localtime.c
    version : 1.5
    date    : 07/10/18
*/
#ifndef LOCALTIME_X
#define LOCALTIME_C

/**
localtime  :  I  ->  T
Converts a time I into a list T representing local time:
[year month day hour minute second isdst yearday weekday].
Month is 1 = January ... 12 = December;
isdst is a Boolean flagging daylight savings/summer time;
weekday is 1 = Monday ... 7 = Sunday.
*/
#define PROCEDURE	do_localtime
#define NAME		"localtime"
#define FUNC		localtime
#include "unmktime.h"
#endif
