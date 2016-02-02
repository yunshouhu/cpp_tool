#include "ctool.h"


BOOL startsWith(const char* str, const char* token)
{
	if (str == NULL || token == NULL)return 0;
	return (strncmp(str, token, strlen(token)) == 0);

}

BOOL endWith(const char * str, const char * end)
{
	BOOL result = FALSE;
	if (str != NULL && end != NULL)
	{
		int l1 = strlen(str);
		int l2 = strlen(end);
		if (l1 >= l2) {
			if (strcmp(str + l1 - l2, end) == 0)
			{
				result = TRUE;
			}
		}
	}
	return result;
}
char* boolToStr(BOOL flag)
{
	return flag ? "true" : "false";
}

char* intToStr(int number)
{
	//char buffer[1024];
	//sprintf(buffer, "%d", number);
	//return buffer;
	//直接使用上面方法 不用进入函数堆栈中
	return "";
}


long my_atol(const char *nptr)
{
	int c; /* current char */
	long total; /* current total */
	int sign; /* if ''-'', then negative, otherwise positive */
	while (isspace((int)(unsigned char)*nptr))
		++nptr;

	c = (int)(unsigned char)*nptr++;
	sign = c; /* save sign indication */
	if (c == '-' || c == '+')
		c = (int)(unsigned char)*nptr++; /* skip sign */

	total = 0;

	while (isdigit(c)) {
		total = 10 * total + (c - '0'); /* accumulate digit */
		c = (int)(unsigned char)*nptr++; /* get next char */
	}

	if (sign == '-')
		return -total;
	else
		return total; /* return result, negated if necessary */
}
//自己实现my_atoi 因为atoi为非标准c函数
int  my_atoi(const char *nptr)
{
	return (int)my_atol(nptr);
}

void charToStr(char ch,char **buffer)
{
	//纯c语言没有引用 c++就可以
	//sprintf(*buffer, "%c", ch);
	/**
	001
	char p = 'B';
	char data[2] = {0};
	data[0] = p;
	printf("%s\n", data);

	002
	char data[2] = { 0 };
	sprintf(data, "%c", temp);
	*/


}
//https://github.com/justinkadima/cosmonaut/blob/master/src/string_util.c
int str_pos(char *str, char *chr)
{
	char *p = strstr(str, chr);
	if (p) {
		return p - str;
	}
	return -1;
}

int file_exists(char *path) {
	struct stat st;
	return stat(path, &st) == 0 && (st.st_mode & S_IFREG);
}

off_t file_size(char *path) {
	struct stat st;
	stat(path, &st);
	return st.st_size;
}
