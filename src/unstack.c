/*
    module  : unstack.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

/**
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
PRIVATE void do_unstack(void)
{
    Node *cur;

#ifndef NCHECK
    if (optimizing)
	del_history(1);
    COMPILE;
    ONEPARAM("unstack");
    LIST("unstack");
#endif
    for (cur = reverse(stk->u.lis), stk = memory; cur; cur = cur->next)
	DUPLICATE(cur);
}