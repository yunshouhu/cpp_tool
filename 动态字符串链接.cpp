#define _CRT_SECURE_NO_DEPRECATE

//#include <vld.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>

//C++调用c函数
//http://blog.csdn.net/imcainiao11/article/details/7369447
extern "C" {
	#include "string_buffer.h"
}


void my_strcat(char* a,char* b,char **str)
{
	int a_len = strlen(a);
	int b_len = strlen(b);
	int c_len = a_len + b_len;
	*str = (char*)malloc(sizeof(char)*c_len);
	memset(*str, 0, sizeof(char)*c_len);
	strcpy(*str, a);
	strcat(*str, b);
}
void my_strcat2(char* a, char* b, char **str)
{
	int a_len = strlen(a);
	int b_len = strlen(b);
	int c_len = a_len + b_len;
	if(*str==NULL)
	{
		*str = (char*)malloc(sizeof(char)*c_len);
	}
	sprintf(*str, "%s%s", a, b);

}


int main()
{
	
	char* str=NULL;
	my_strcat2("java", "android",&str);
	printf("%s\n", str);
	my_strcat2("java2", "android2", &str);
	printf("%s\n", str);
	//free(str); //程序会卡住
	StringBuffer *sb=string_buffer_new();
	int len_i = string_buffer_append(sb, "123456");
	len_i=string_buffer_append(sb, "android");
	len_i = string_buffer_append(sb, "java中文");
	printf("%s\n", string_buffer_get_string(sb));

	return 0;
}