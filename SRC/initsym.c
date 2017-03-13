/*
    module  : initsym.c
    version : 1.1
    date    : 03/12/17
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "joy.h"
#include "symbol.h"

#define MAXSTR		100

FILE *outfp;
char **g_argv;
int g_argc, error;
clock_t startclock;
unsigned compiling, optimizing, identifier;
unsigned autoput = 1, undeferror = 1, echoflag, tracegc;

static void quit(void)
{
    exit(0);
}

static char *name(char *str)
{
    if (!strcmp(str, "plus"))
	return "+";
    if (!strcmp(str, "minus"))
	return "-";
    if (!strcmp(str, "mul"))
	return "*";
    if (!strcmp(str, "divide"))
	return "/";
    if (!strcmp(str, "geql"))
	return ">=";
    if (!strcmp(str, "greater"))
	return ">";
    if (!strcmp(str, "leql"))
	return "<=";
    if (!strcmp(str, "less"))
	return "<";
    if (!strcmp(str, "neql"))
	return "!=";
    if (!strcmp(str, "eql"))
	return "=";
    return str;
}

void initsym(int argc, char **argv)
{
    FILE *fp;
    Entry *sym;
    unsigned adr;
    char chr, str[MAXSTR], *ptr, *tmp;

    startclock = clock();
    yyin = stdin;
    outfp = yyout = stdout;
    g_argc = argc;
    g_argv = argv;
    initmem();
    sym = lookup("quit");
    sym->u.proc = quit;
    sym->flags |= IS_BUILTIN;
    sprintf(str, "%s.sym", argv[0]);
    if ((fp = fopen(str, "r")) == 0) {
	sprintf(str, "nm %s | grep \" _do_\" >%s.sym", argv[0], argv[0]);
	system(str);
	sprintf(str, "%s.sym", argv[0]);
	fp = fopen(str, "r");
    }
    if (!fp)
	return;
    while (fscanf(fp, "%x %c %s", &adr, &chr, str) == 3) {
	ptr = name(str + 4);
	if ((tmp = strchr(ptr, '.')) != 0)
	    *tmp = 0;
	sym = lookup(ptr);
	if (sym->flags & IS_BUILTIN)
	    sym = lookup(str + 3);
	sym->u.proc = (void (*)(void))adr;
	sym->flags = IS_BUILTIN;
    }
    fclose(fp);
}
