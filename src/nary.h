/*
    module  : nary.h
    version : 1.14
    date    : 03/28/20
*/
#ifndef OLD_RUNTIME
#define CAT(a, b)	a ## b
#define PUT_PROC(a)	CAT(put_, a)()

int PUT_PROC(PROCEDURE)
{
    Node *prog;

    if (!LIST_1)
	return 0;
    prog = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* %s */", NAME);
    fprintf(outfp, "Node temp, *top = %s;", TOPSTR);
    compile(prog);
    fprintf(outfp, "temp = *stk; stk = top; DUPLICATE(&temp); }");
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    Node *prog, *top, temp;

#ifndef OLD_RUNTIME
    if (compiling && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
#endif
    PARAMCOUNT(NAME);
    ONEQUOTE(NAME);
    prog = stk->u.lis;
    POP(stk);
    top = TOP;
    exeterm(prog);
#ifndef NCHECK
    if (!stk)
	execerror("value to push", NAME);
#endif
    temp = *stk;
    stk = top;
    DUPLICATE(&temp);
}

#undef PROCEDURE
#undef NAME
#undef PARAMCOUNT
#undef TOP
#undef TOPSTR
#undef ARITY
#undef CAT
#undef PUT_PROC
