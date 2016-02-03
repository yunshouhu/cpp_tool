#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>


/********************************************************************
*  Function：  my_strstr()
*  Description: 在一个字符串中查找一个子串;
*  Input：      ps: 源;      pd：子串
*  Return :    0：源字符串中没有子串; 1：源字符串中有子串;
*********************************************************************/
char * my_strstr(char * ps, char *pd)
{
	char *pt = pd;
	int c = 0;
	while (*ps != '\0')
	{
		if (*ps == *pd)
		{
			while (*ps == *pd && *pd != '\0')
			{
				ps++;
				pd++;
				c++;
			}
		}
		else
		{
			ps++;
		}
		if (*pd == '\0')
		{
			return (ps - c);
		}
		c = 0;
		pd = pt;
	}
	return 0;
}

/********************************************************************
*  Function：  my_memcpy()
*  Description: 复制一个内存区域到另一个区域;
*  Input：      src: 源;
count: 复制字节数.
*  Output：      dest: 复制目的地;
*  Return :      dest;
*********************************************************************/
void * my_memcpy(void * dest, const void *src, size_t count)
{
	char *tmp = (char *)dest, *s = (char *)src;
	while (count--)
		*tmp++ = *s++;
	return dest;
}

/********************************************************************
*  Function：  str_replace()
*  Description: 在一个字符串中查找一个子串，并且把所有符合的子串用
另一个替换字符串替换。
*  Input：      p_source:要查找的母字符串； p_seach要查找的子字符串;
p_repstr：替换的字符串;
*  Output：      p_result:存放结果;
*  Return :      返回替换成功的子串数量;
*  Others:      p_result要足够大的空间存放结果，所以输入参数都要以\0结束;
*********************************************************************/
int str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr)
{
	int c = 0;
	int repstr_leng = 0;
	int searchstr_leng = 0;
	char *p1;
	char *presult = p_result;
	char *psource = p_source;
	char *prep = p_repstr;
	char *pseach = p_seach;
	int nLen = 0;
	repstr_leng = strlen(prep);
	searchstr_leng = strlen(pseach);

	do {
		p1 = strstr(psource, p_seach);
		if (p1 == 0)
		{
			strcpy(presult, psource);
			return c;
		}
		c++;  //匹配子串计数加1;
		//printf("结果:%s\r\n", p_result);
		//printf("源字符:%s\r\n", p_source);
		// 拷贝上一个替换点和下一个替换点中间的字符串
		nLen = p1 - psource;
		memcpy(presult, psource, nLen);
		// 拷贝需要替换的字符串
		memcpy(presult + nLen, p_repstr, repstr_leng);
		psource = p1 + searchstr_leng;
		presult = presult + nLen + repstr_leng;
	} while (p1);

	return c;
}
#define MAX 200
int main(void)
{
	int i = 0;
	char s[MAX] = { 0 };        //存放源字串
	char s1[MAX] = { 0 };        //存放子字串
	char s2[MAX] = { 0 };        //存放替换字串
	char result_a[2000] = { 0 };//存放替换结果;
	puts("Please input the string for s:");
	gets_s(s,MAX);
	puts("Please input the string for s1:");
	gets_s(s1, MAX);
	puts("Please input the string for s2:");
	gets_s(s2, MAX);
	i = str_replace(result_a, s, s1, s2);
	printf("替换%d个子字符串;\r\n", i);
	printf("替换后结果:%s\r\n", result_a);
}