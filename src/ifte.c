/*
    module  : ifte.c
    version : 1.18
    date    : 03/28/20
*/
#ifndef IFTE_C
#define IFTE_C

#ifndef OLD_RUNTIME
int put_ifte(void)
{
    Node *prog[3];

    if (!(LIST_1 && LIST_2 && LIST_3))
	return 0;
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    printstack(outfp);
    fprintf(outfp, "{ /* IFTE */");
    fprintf(outfp, "int num;");
    compile(prog[0]);
    fprintf(outfp, "num = stk->u.num; POP(stk); if (num) {");
    compile(prog[1]);
    fprintf(outfp, "} else {");
    compile(prog[2]);
    fprintf(outfp, "} }");
    return 1;
}
#endif

/**
ifte  :  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
PRIVATE void do_ifte(void)
{
    Node *prog[3] /* , *save */;

#ifndef OLD_RUNTIME
    if (compiling && put_ifte())
	return;
    COMPILE;
#endif
    THREEPARAMS("ifte");
    THREEQUOTES("ifte");
    prog[2] = stk->u.lis;
    POP(stk);
    prog[1] = stk->u.lis;
    POP(stk);
    prog[0] = stk->u.lis;
    POP(stk);
    exeterm(prog[0]);
    prog[0] = stk->u.num ? prog[1] : prog[2];
    POP(stk);
    exeterm(prog[0]);
}
#endif
