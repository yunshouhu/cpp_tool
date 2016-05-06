
#define _CRT_SECURE_NO_WARNINGS

#include "vector_matteckert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void json_object_array_entry_free(void *data)
{
	//json_object_put((struct json_object*)data);
	//printf("json_object_array_entry_free=%s\n", data);
}

void test_Vector()
{

	struct vector* alist = vector_new(0, 1, json_object_array_entry_free);

	int i = 0;
	for (i = 0; i < 15; i++)
	{

		char* tmp = (char*)malloc(sizeof(char)* 512);
		memset(tmp, 0, sizeof(char)* 512);
		sprintf(tmp, "hehe%d", i);
		printf("%s\n", tmp);
		vector_add(alist, tmp);
	}

	int len = vector_size(alist);
	for (i = 0; i < len; i++)
	{
		char* tmp=(char*)malloc(sizeof(char)*512);
		vector_get(alist, i, &tmp);
		printf("%s\n", tmp);
	}

	vector_free(alist);


}

int main(int argc, char* argv[])
{

	test_Vector();

	return 0;
}