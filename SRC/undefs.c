/*
    module  : undefs.c
    version : 1.4
    date    : 03/12/17
*/
#include "runtime.h"

/*
undefs  :  ->  [..]
Push a list of all undefined symbols in the current symbol table.
*/
PRIVATE void do_undefs(void)
{
    int i;
    Node *root = 0;

    for (i = symtabindex - 1; i >= 0; i--)
	if (symtab[i].name[0] && symtab[i].name[0] != '_' &&
	    (symtab[i].flags & (IS_MODULE | IS_BUILTIN)) == 0 &&
	     !symtab[i].u.body)
	    root = heapnode(STRING_, (void *)symtab[i].name, root);
    PUSH(LIST_, root);
}
