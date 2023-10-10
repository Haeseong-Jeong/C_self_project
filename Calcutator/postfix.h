#pragma once
#ifndef POSTFIX
# define POSTFIX
#define max_ptf


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#define max_pf 100

//�̰͵� ����� ����ü�� ���������...
char* postfix[max_pf];
int pfn;


void makepostfix(chstack* opstack, intstack* outstack, char* inputstr);
int rank_op(char op);
char* optostr(char operater);
char* numtostr(int num);
void optopostfix(chstack* opstack, char inputop);
void freepostfix();
void printpostfix();


#endif