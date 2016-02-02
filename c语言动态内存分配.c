#include <stdio.h>
#include <stdlib.h>
#include <vld.h>

//正确使用指针
void test002()
{
	int len = 25;
	//pi指向申请内存的指针不要动，保留内容位置 后面好释放
	int     *pi = malloc( sizeof(int)*len);
	int     *tempPi = pi;
	int     i = 0;

	//只移动tempPi即可
	for (i = 0; i < len; i++) {
		*tempPi++ = i;
	}
	//指向初始位置
	tempPi = pi;
	for (i = 0; i < 25; i++) {
		printf("%d ", *tempPi++);
	}
	free(pi);
	printf("\nhello world\n");


}
int main()
{
	int *pstr, *pstr2;
	int i = 0;
	int len = 20;
	pstr = (int*)malloc(sizeof(int)*len);
	//保留原来指针位置，即原来的内存空间位置。
	pstr2 = pstr;
	for (i = 0; i < len;i++)
	{
		*pstr = i;
		pstr++;
	}
	//恢复指针
	pstr = pstr2;
	for (i = 0; i < len; i++)
	{
		int data = *pstr;
		printf("%d ", data);
		pstr++;
	}
	printf("\n");
	//只能释放pstr2原始指针位置，他才是指向申请的内存空间，而pstr所指内存已经后移
	free(pstr2);
	pstr2 = NULL;
	pstr = NULL;

	test002();


}
