
/************************************************************************/
/*
1、使用C语言方式模拟二维数组的动态开辟与释放
2、使用C++ 语言方式模拟二维数组的动态开辟与释放
3、扩展多维数组的动态开辟与释放                                                                     */
/************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <vld.h>
//目标是出现No memory leaks detected
#define Type int   //char int
#define ROW 3
#define COL 4

Type** _New(int row, int col)
{
	Type **p = new Type *[row];//申请数组指针空间
	assert(p != NULL);
	for (int i = 0; i < row; ++i)
	{
		p[i] = new Type[col];
		assert(p[i] != NULL);

	}
	return p;
}
void _Assign(Type **p, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			p[i][j] = i + j;

		}

	}
}
void _Print(Type **p, int row, int col)
{

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}
}
void _Delete(Type **p, int row)
{
	for (int i = 0; i < row; ++i)
	{
		delete[]p[i];//c++ 释放数组空间
	}
	delete[]p;//c++释放数组

}

int main(int argc, char* argv[])
{
	Type **p = _New(ROW, COL);
	_Assign(p, ROW, COL);
	_Print(p, ROW, COL);
	_Delete(p, ROW);

	printf("c++\n");
	system("pause");
	return 0;
}
