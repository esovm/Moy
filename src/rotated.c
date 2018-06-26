/*
    module  : rotated.c
    version : 1.3
    date    : 06/25/18
*/
#include "runtime.h"

/**
rotated  :  X Y Z W  ->  Z Y X W
As if defined by:   rotated  ==  [rotate] dip
*/
#define PROCEDURE	do_rotated
#define NAME		"rotated"
#define PARAMCOUNT	FOURPARAMS
#define ARGUMENT	do_rotate
#include "dipped.h"