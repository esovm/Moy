/*
    module  : someall.h
    version : 1.18
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
    fprintf(outfp, "{ /* SOMEALL */");
    fprintf(outfp, "unsigned i, num = %d;", INITIAL);
    fprintf(outfp, "char *str;");
    fprintf(outfp, "ulong_t set;");
    fprintf(outfp, "Node *list, *save;");
    fprintf(outfp, "switch (stk->op) {");
    fprintf(outfp, "case LIST_:");
    fprintf(outfp, "list = stk->u.lis; POP(stk);");
    fprintf(outfp, "for (; list; list = list->next) {");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "DUPLICATE(list);");
    compile(prog);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case STRING_:");
    fprintf(outfp, "str = stk->u.str; POP(stk);");
    fprintf(outfp, "for (; *str; str++) {");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "PUSH(CHAR_, (long_t)*str);");
    compile(prog);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "if (num != %d) break; } break;", INITIAL);
    fprintf(outfp, "case SET_:");
    fprintf(outfp, "set = stk->u.set; POP(stk);");
    fprintf(outfp, "for (i = 0; i < SETSIZE_; i++)");
    fprintf(outfp, "if (set & ((long_t)1 << i)) {");
    fprintf(outfp, "save = stk;");
    fprintf(outfp, "PUSH(INTEGER_, i);");
    compile(prog);
    fprintf(outfp, "num = stk->u.num; stk = save;");
    fprintf(outfp, "if (num != %d) break; } break; }", INITIAL);
    fprintf(outfp, "PUSH(BOOLEAN_, num); }");
    return 1;
}
#endif

PRIVATE void PROCEDURE(void)
{
    char *str;
    ulong_t set;
    int i, num = INITIAL;
    Node *prog, *list, *save;

#ifndef OLD_RUNTIME
    if (compiling && PUT_PROC(PROCEDURE))
	return;
    COMPILE;
#endif
    TWOPARAMS(NAME);
    ONEQUOTE(NAME);
    prog = stk->u.lis;
    POP(stk);
    switch (stk->op) {
    case LIST_:
	list = stk->u.lis;
	POP(stk);
	for (; list; list = list->next) {
	    save = stk;
	    DUPLICATE(list);
	    exeterm(prog);
	    num = stk->u.num;
	    stk = save;
	    if (num != INITIAL)
		break;
	}
	break;
    case STRING_:
	str = stk->u.str;
	POP(stk);
	for (; *str; str++) {
	    save = stk;
	    PUSH(CHAR_, (long_t)*str);
	    exeterm(prog);
	    num = stk->u.num;
	    stk = save;
	    if (num != INITIAL)
		break;
	}
	break;
    case SET_:
	set = stk->u.set;
	POP(stk);
	for (i = 0; i < SETSIZE_; i++)
	    if (set & ((long_t)1 << i)) {
		save = stk;
		PUSH(INTEGER_, i);
		exeterm(prog);
		num = stk->u.num;
		stk = save;
		if (num != INITIAL)
		    break;
	    }
	break;
    default:
	BADAGGREGATE(NAME);
	break;
    }
    PUSH(BOOLEAN_, num);
}

#undef PROCEDURE
#undef NAME
#undef INITIAL
#undef CAT
#undef PUT_PROC
