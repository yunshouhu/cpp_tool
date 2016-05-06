
#define _CRT_SECURE_NO_WARNINGS

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>


void test_Vector()
{
	struct vector* alist=(struct vector*)malloc(sizeof(struct vector));
	vector_init(alist);

	int i = 0;
	for (i = 0; i < 15; i++)
	{

		char* tmp = (char*)malloc(sizeof(char)* 512);
		memset(tmp, 0, sizeof(char)* 512);
		sprintf(tmp, "hehe%d", i);
		printf("%s\n", tmp);
		vector_add(alist, tmp);
	}

	int len = vector_count(alist);
	for (i = 0; i < len; i++)
	{
		char* tmp;
		vector_get(alist, i,&tmp);
		printf("%s\n",tmp);
	}
	
	vector_free(alist);



}

int main(int argc, char* argv[])
{

	test_Vector();

	return 0;
}