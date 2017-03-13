/*
    module  : consswons.c
    version : 1.5
    date    : 03/12/17
*/
PRIVATE void PROCEDURE(void)
{
    char *str;

#ifndef NCHECK
    if (optimizing && AGGREGATE(AGGR) && VALID(ELEM))
	;
    else
	COMPILE;
    TWOPARAMS(NAME);
#endif
    switch (AGGR->op) {
    case LIST_:
	if (OUTSIDE) {
	    stk->next->u.lis = heapnode(ELEM->op, ELEM->u.ptr, AGGR->u.lis);
	    stk->next->op = LIST_;
	    POP(stk);
	} else
	    BINARY(LIST_NEWNODE, heapnode(ELEM->op, ELEM->u.ptr, AGGR->u.lis));
	break;
    case STRING_:
#ifndef NCHECK
	if (ELEM->op != CHAR_)
	    execerror("character", NAME);
#endif
	str = GC_malloc_atomic(strlen(AGGR->u.str) + 2);
	str[0] = (char)ELEM->u.num;
	strcpy(str + 1, AGGR->u.str);
	if (OUTSIDE) {
	    stk->next->u.str = str;
	    stk->next->op = STRING_;
	    POP(stk);
	} else
	    BINARY(STRING_NEWNODE, str);
	break;
    case SET_:
#ifndef NCHECK
	CHECKSETMEMBER(ELEM, NAME);
#endif
	if (OUTSIDE) {
	    stk->next->u.set = AGGR->u.set | (1 << ELEM->u.num);
	    stk->next->op = SET_;
	    POP(stk);
	} else
	    BINARY(SET_NEWNODE, AGGR->u.set | (1 << ELEM->u.num));
	break;
#ifndef NCHECK
    default:
	BADAGGREGATE(NAME);
#endif
    }
}

#undef PROCEDURE
#undef NAME
#undef AGGR
#undef ELEM