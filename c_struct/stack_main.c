
#define _CRT_SECURE_NO_WARNINGS

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test_Vector()
{
	struct stack* alist = (struct stack*)malloc(sizeof(struct stack));
	stackInitialize(alist,1024);

	int i = 0;
	for (i = 0; i < 15; i++)
	{

		char* tmp = (char*)malloc(sizeof(char)* 512);
		memset(tmp, 0, sizeof(char)* 512);
		sprintf(tmp, "hehe%d", i);
		printf("%s\n", tmp);
		stackPush(alist, tmp);
	}

	printf("\n\n");

	int len = stackSize(alist);
	for (i = 0; i < len; i++)
	{
		char* tmp;
		//tmp=stackGet(alist, i);
		tmp=stackPop(alist);
		printf("%s\n", tmp);
	}

	stackFree(alist);



}

int main(int argc, char* argv[])
{

	test_Vector();

	return 0;
}