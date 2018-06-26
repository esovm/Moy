/*
    module  : treerec.c
    version : 1.6
    date    : 06/25/18
*/
#include "runtime.h"

#ifndef NCHECK
int put_treerec(void)
{
    void *save;
    Node *prog[2];
    unsigned ident;
    FILE *oldfp, *newfp;

    del_history(2);
    if (!(LIST_1 && LIST_2))
	return 0;
    prog[1] = stk->u.lis;
    prog[0] = stk->next->u.lis;
    printstack(outfp);
    fprintf(outfp, "do_cons();");
    fprintf(declfp, "void do_treerec_%d(void);", ident = ++identifier);
    fprintf(outfp, "do_treerec_%d();", ident);
    oldfp = outfp;
    newfp = outfp = nextfile();
    fprintf(outfp, "void do_treerec_%d(void) {", ident);
    fprintf(outfp, "if (stk->next->op == LIST_) {");
    fprintf(outfp, "NULLARY(LIST_NEWNODE,");
    fprintf(outfp, "ANON_FUNCT_NEWNODE(do_treerec_%d, 0));", ident);
    fprintf(outfp, "do_cons();");
    save = new_history();
    add_history2(LIST_, ANON_FUNCT_);
    evaluate(prog[1]);
    old_history(save);
    fprintf(outfp, "} else { POP(stk);");
    del_history(1);
    evaluate(prog[0]);
    fprintf(outfp, "} }");
    closefile(newfp);
    outfp = oldfp;
    return 1;
}
#endif

/**
treerec  :  T [O] [C]  ->  ...
T is a tree. If T is a leaf, executes O. Else executes [[[O] C] treerec] C.
*/
static void treerec(void)
{
    Node *save;

    if (stk->next->op == LIST_) {
	NULLARY(LIST_NEWNODE, ANON_FUNCT_NEWNODE(treerec, 0));
	do_cons();
	exeterm(stk->u.lis->u.lis->next);
    } else {
	save = stk;
	POP(stk);
	exeterm(save->u.lis->u.lis);
    }
}

PRIVATE void do_treerec(void)
{
#ifndef NCHECK
    if (optimizing && put_treerec())
	return;
    COMPILE;
    THREEPARAMS("treerec");
    TWOQUOTES("treerec");
#endif
    do_cons();
    treerec();
}