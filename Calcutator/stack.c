#include "stack.h"

void init_chstack(chstack* s)
{
	memset(s->stack, NULL, sizeof(s->stack));
	s->top = -1;
}

int Isfull_chstack(chstack* s)
{
	if (s->top == max_chst - 1)
	{
		printf("Char Stack if Full\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

int Isempty_chstack(chstack* s)
{
	if (s->top == -1)
	{
		printf("char Stack if Empty\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

void push_chstack(chstack* s, char ch)
{
	if (Isfull_intstack(s) == 1)
	{
		printf("char Stack if Full\n");
	}
	else
	{
		s->stack[++(s->top)] = ch;
	}
}

char pop_chstack(chstack* s)
{
	if (Isfull_intstack(s) == 1)
	{
		printf("Char Stack if Full\n");
	}
	else
	{
		static char popdata;
		popdata = s->stack[s->top];
		s->stack[(s->top)--] = '\0';
		return popdata;
	}
}

void print_chstack(chstack* s)
{
	for (int i = 0; i < max_chst; i++)
	{
		printf("char stack[%d] = %c\n", i, s->stack[i]);
	}
}

////////////////////////////////////////int////////////////////////////////////////
////////////////////////////////////////int////////////////////////////////////////

void init_intstack(intstack* s)
{
	memset(s->stack, NULL, sizeof(s->stack));
	s->top = -1;
}

int Isfull_intstack(intstack* s)
{
	if (s->top == max_intst - 1)
	{
		printf("Stack if Full\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

int Isempty_intstack(intstack* s)
{
	if (s->top == -1)
	{
		printf("Stack if Empty\n");
		return 1;
	}
	else
	{
		return 0;
	}
}

void push_intstack(intstack* s, int num)
{
	if (Isfull_intstack(s) == 1)
	{
		printf("Stack if Full\n");
	}
	else
	{
		s->stack[++(s->top)] = num;
	}
}

int pop_intstack(intstack* s)
{
	if (Isfull_intstack(s) == 1)
	{
		printf("Stack if Full\n");
	}
	else
	{
		static int popdata;
		popdata = s->stack[s->top];
		s->stack[(s->top)--] = NULL;
		return popdata;
	}
}

void print_intstack(intstack* s)
{
	for (int i = 0; i < max_intst; i++)
	{
		printf("Int stack[%d] = %d\n", i, s->stack[i]);
	}
}
