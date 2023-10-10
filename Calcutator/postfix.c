#include "postfix.h"


void makepostfix(chstack* opstack, intstack* outstack, char* inputstr)
{
	int num = 0;
	for (int i = 0; i <= strlen(inputstr); i++)// <=���� num ������, opstack������ �� ������ �ִ�.
	{
		if (inputstr[i] >= '0' && inputstr[i] <= '9')
		{
			num = num * 10 + (inputstr[i] - 48);
		}
		else
		{
			if (num == 0)
			{
				optopostfix(opstack, inputstr[i]);
			}
			else
			{
				postfix[pfn++] = numtostr(num);
				num = 0;
				optopostfix(opstack, inputstr[i]);
			}
		}
	}
}

int rank_op(char op)
{
	switch (op)
	{
	case '*': case '/':
		return 2;
	case '+':case '-':
		return 1;
	/*case '(':
		return 3;*/
	default:
		return 0;
	}
}

char* optostr(char operater)
{
	static char ch[2] = { '\0' };
	ch[0] = operater;
	ch[1] = '\0';
	return _strdup(ch);
}

char* numtostr(int num)
{
	static char numtext[10];
	sprintf(numtext, "%d", num);
	return _strdup(numtext);
}

void optopostfix(chstack* opstack, char inputop)
{
	if (inputop == '(')
	{
		push_chstack(opstack, inputop);
	}

	else if (inputop == ')')
	{
		while (opstack->stack[opstack->top] != '(')
		{
			char ch = pop_chstack(opstack);
			postfix[pfn++] = optostr(ch);
		}
		pop_chstack(opstack);
	}
	else
	{
		// for�� �������� null ���� ���� rank = 0 �̱� ������ �����ִ� �����ڰ� �˾Ƽ� �� ������ �ȴ�.
		while (rank_op(inputop) < rank_op(opstack->stack[opstack->top]))
		{
			char ch = pop_chstack(opstack);
			postfix[pfn++] = optostr(ch);
		}
		push_chstack(opstack, inputop);
	}

}

void freepostfix()
{
	for (int i = 0; i < max_pf; i++)
	{
		free(postfix[i]);
		postfix[i] = NULL;
	}
}

void printpostfix()
{
	for (int i = 0; i < pfn; i++)
	{
		printf("postfix[%d] = %s\n", i, postfix[i]);
	}
}
