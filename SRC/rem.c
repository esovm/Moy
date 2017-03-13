/*
    module  : rem.c
    version : 1.3
    date    : 03/12/17
*/
#include "runtime.h"

/*
rem  :  I J  ->  K
Integer K is the remainder of dividing I by J.  Also supports float.
*/
PRIVATE void do_rem(void)
{
#ifndef NCHECK
    if (optimizing && NUMERIC_1 && NUMERIC_2)
	;
    else
	COMPILE;
    TWOPARAMS("rem");
    FLOAT2("rem");
    if ((stk->op == FLOAT_ && !stk->u.dbl) ||
	(stk->op == INTEGER_ && !stk->u.num))
	execerror("non-zero operand", "rem");
#endif
    if (OUTSIDE) {
	if (stk->next->op == FLOAT_)
	    stk->next->u.dbl = fmod(stk->next->u.dbl, FLOATVAL);
	else if (stk->op == FLOAT_) {
	    stk->next->u.dbl = fmod((double) stk->next->u.num, stk->u.dbl);
	    stk->next->op = FLOAT_;
	} else
	    stk->next->u.num %= stk->u.num;
	POP(stk);
    } else if (stk->op == FLOAT_ || stk->next->op == FLOAT_)
	BINARY(FLOAT_NEWNODE, fmod(FLOATVAL2, FLOATVAL));
    else
	BINARY(INTEGER_NEWNODE, stk->next->u.num % stk->u.num);
}
