#pragma once
#ifndef CALCULATE
# define CALCULATE

#include "postfix.h"

void calculate(intstack* outstack);
int operate(intstack* outstack, char* op);

#endif