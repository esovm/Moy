/*
    module  : mktime.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

PRIVATE void decode_time(struct tm *t);

/*
mktime  T  ->  I
Converts a list T representing local time into a time I.
T is in the format generated by localtime.
*/
PRIVATE void do_mktime(void)
{
    struct tm t;

#ifndef NCHECK
    if (optimizing && LIST_1)
	;
    else
	COMPILE;
    ONEPARAM("mktime");
    LIST("mktime");
#endif
    decode_time(&t);
    PUSH(INTEGER_, mktime(&t));
}
