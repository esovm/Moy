/*
    module  : frename.c
    version : 1.7
    date    : 07/10/18
*/
#ifndef FRENAME_X
#define FRENAME_C

/**
frename  :  P1 P2  ->  B
The file system object with pathname P1 is renamed to P2.
B is a boolean indicating success or failure.
*/
PRIVATE void do_frename(void)
{
#ifndef NCHECK
    COMPILE;
#endif
    TWOPARAMS("frename");
    STRING("frename");
    STRING2("frename");
    if (OUTSIDE) {
	stk->next->u.num = !rename(stk->next->u.str, stk->u.str);
	stk->next->op = BOOLEAN_;
	POP(stk);
    } else
	BINARY(BOOLEAN_NEWNODE, !rename(stk->next->u.str, stk->u.str));
}
#endif
