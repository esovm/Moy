/*
    module  : plus.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
+  :  M I  ->  N
Numeric N is the result of adding integer I to numeric M.
Also supports float.
*/
#define PROCEDURE	do_plus
#define NAME		"+"
#define OPER		+
#include "plusminus.h"
/* plus.c */