/*
    module  : uncons_str.c
    version : 1.2
    date    : 07/08/18
*/
#ifdef RUNTIME
void do_uncons_str(void)
{
    char *str;

    TRACE;
    str = (char *)stk[-1];
    stk[-1] = *str++;
    do_push((node_t)str);
}
#else
/**
uncons_str  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
PRIVATE void do_uncons_str(void)
{
    char *str;
    int i = 0;
    Node *save;
    ulong_t set;

#ifndef NCHECK
    if (compiling && stk && ((stk->op == LIST_ && stk->u.lis->op > USR_ &&
	stk->u.lis->op <= SYMBOL_) || stk->op == STRING_ || stk->op == SET_))
	;
    else
	COMPILE;
#endif
    ONEPARAM("uncons");
    switch (stk->op) {
    case LIST_:
	CHECKEMPTYLIST(stk->u.lis, "uncons");
	save = stk->u.lis;
	if (OUTSIDE) {
	    stk->op = stk->u.lis->op;
	    stk->u = stk->u.lis->u;
	} else
	    GUNARY(stk->u.lis->op, stk->u.lis->u.ptr);
	PUSH(LIST_, save->next);
	break;
    case STRING_:
	str = stk->u.str;
	CHECKEMPTYSTRING(str, "uncons");
	if (OUTSIDE) {
	    stk->u.num = *str;
	    stk->op = CHAR_;
	} else
	    UNARY(CHAR_NEWNODE, *str);
	PUSH(STRING_, ++str);
	break;
    case SET_:
	set = stk->u.set;
	CHECKEMPTYSET(set, "uncons");
	while (!(set & (1 << i)))
	    i++;
	if (OUTSIDE) {
	    stk->u.num = i;
	    stk->op = INTEGER_;
	} else
	    UNARY(INTEGER_NEWNODE, i);
	PUSH(SET_, set & ~(1 << i));
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE("uncons");
#endif
    }
}
#endif