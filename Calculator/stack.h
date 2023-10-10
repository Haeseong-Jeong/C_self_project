#pragma once
#ifndef STACK
#define STACK

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# define max_chst 10
# define max_intst 10
# define max_pf 20

typedef struct
{
	char stack[max_chst];
	int top;
}chstack;

typedef struct
{
	int stack[max_intst];
	int top;
}intstack;

//ch
void init_chstack(chstack* s);
int Isfull_chstack(chstack* s);
int Isempty_chstack(chstack* s);
void push_chstack(chstack* s, char ch);
char pop_chstack(chstack* s);
void print_chstack(chstack* s);

//int
void init_intstack(intstack* s);
int Isfull_intstack(intstack* s);
int Isempty_intstack(intstack* s);
void push_intstack(intstack* s, int num);
int pop_intstack(intstack* s);
void print_intstack(intstack* s);

#endif

