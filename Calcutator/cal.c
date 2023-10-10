#include "cal.h"

void calculate(intstack* outstack)
{
	for (int i = 0; i < pfn; i++)
	{
		if (strcmp(postfix[i], "*") == 0 || strcmp(postfix[i], "/") == 0 || strcmp(postfix[i], "+") == 0 || strcmp(postfix[i], "-") == 0)
		{
			push_intstack(outstack, operate(outstack, postfix[i]));
		}
		else
		{
			push_intstack(outstack, atoi(postfix[i]));
		}
	}
}

int operate(intstack* outstack, char* op)
{
	char ch = op[0];

	int op1 = pop_intstack(outstack);
	int op2 = pop_intstack(outstack);

	switch (ch)
	{
	case '*':
		return op2 * op1;
	case '/':
		return op2 / op1;
	case '+':
		return op2 + op1;
	case '-':
		return op2 - op1;
		/*default:
			return 0;*/
	}
}