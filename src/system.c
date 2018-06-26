/*
    module  : system.c
    version : 1.4
    date    : 06/25/18
*/
#include "runtime.h"

/**
system  :  "command"  ->
Escapes to shell, executes string "command".
The string may cause execution of another program.
When that has finished, the process returns to Joy.
*/
PRIVATE void do_system(void)
{
    char *str;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("system");
    STRING("system");
#endif
    str = stk->u.str;
    POP(stk);
    system(str);
}