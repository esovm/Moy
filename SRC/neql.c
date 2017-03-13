/*
    module  : neql.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
!=  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
#define PROCEDURE	do_neql
#define NAME		"!="
#define CONSTRUCTOR	BOOLEAN_
#define OPR		!=
#define SETCMP		i!=j
#include "comprel.c"
