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

//效果和strcat一样
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
//效果和strcat一样
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

int string_expand_buffer(char *self, size_t min, int self_length)
{
	char *new_buf = NULL;
	size_t new_capacity;
	new_capacity = self_length + min;
	new_buf =(char*) realloc(self, new_capacity);
	if (new_buf != NULL) {
		self= new_buf;
		memset(self+ self_length, 0, min);
		return 0;
	}
	else {
		return -1;
	}
}
int string_append_n(char *self, const char *str, size_t n,int self_length)
{
	if (self == NULL) 
		return -1;
	string_expand_buffer(self, n, self_length);
	memcpy(self + self_length, str, n);
	self_length += n;
	self[self_length] = '\0';
	return self_length;
}
//真正实现c语言的string_append
int string_append(char *self, const char *str, int self_length)
{
	return string_append_n(self, str, strlen(str), self_length);
}
int string_init(char **pdata,char* data)
{
	int len_i = strlen(data);
	*pdata = (char*)malloc(sizeof(char) * len_i);
	memset(*pdata, 0, sizeof(char) *len_i);
	strcpy(*pdata, data);
	return len_i;
}

int main()
{
	/**
	char* str=NULL;
	my_strcat2("java", "android",&str);
	printf("%s\n", str);
	my_strcat2("java2", "android2", &str);
	printf("%s\n", str);
	//free(str); //程序会卡住
	*/

	StringBuffer *sb=string_buffer_new();
	int len_i = string_buffer_append(sb, "123456");
	len_i=string_buffer_append(sb, "android");
	len_i = string_buffer_append(sb, "java中文");
	printf("%s\n", string_buffer_get_string(sb));

	//char *pdata = NULL;
	//len_i = string_init(&pdata,"我来自中国");

	char *pdata = "我来自中国";
	len_i = string_init(&pdata, pdata);
	len_i= string_append(pdata, "test", len_i);
	printf("%s\n", pdata);
	len_i = string_append(pdata, "android", len_i);
	printf("%s\n", pdata);
	len_i = string_append(pdata, "java龙飞凤舞", len_i);
	printf("%s\n", pdata);

	return 0;
}
