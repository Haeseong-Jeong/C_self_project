#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "postfix.h"
#include "cal.h"


int main()
{
	char inputstr[100];
	scanf("%s", inputstr);

	// ���� �����
	chstack opstack;//opstack
	intstack outstack;//result
	init_chstack(&opstack);
	init_intstack(&outstack);

	// postfix �� �����
	makepostfix(&opstack, &outstack, inputstr);

	//���
	calculate(&outstack);


	printf("Result = %d\n", outstack.stack[0]);
	freepostfix();
	return 0;
}