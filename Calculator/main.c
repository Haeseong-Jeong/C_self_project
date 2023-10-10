#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "postfix.h"
#include "cal.h"


int main()
{
	char inputstr[100];
	scanf("%s", inputstr);

	// 스택 만들기
	chstack opstack;//opstack
	intstack outstack;//result
	init_chstack(&opstack);
	init_intstack(&outstack);

	// postfix 식 만들기
	makepostfix(&opstack, &outstack, inputstr);

	//계산
	calculate(&outstack);


	printf("Result = %d\n", outstack.stack[0]);
	freepostfix();
	return 0;
}