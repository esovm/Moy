/*
    module  : xor.c
    version : 1.2
    date    : 03/12/17
*/
#include "runtime.h"

/*
xor  :  X Y  ->  Z
Z is the symmetric difference of sets X and Y,
logical exclusive disjunction for truth values.
*/
#define PROCEDURE	do_xor
#define NAME		"xor"
#define OPER1		^
#define OPER2		!=
#include "andorxor.c"
