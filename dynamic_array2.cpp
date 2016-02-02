
/************************************************************************/
/*
1、使用C语言方式模拟二维数组的动态开辟与释放
2、使用C++ 语言方式模拟二维数组的动态开辟与释放
3、扩展多维数组的动态开辟与释放                                                                     */
/************************************************************************/

#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <vld.h>
#include <iostream>
using namespace std;
//目标是出现No memory leaks detected
#define Type int   //char int
#define ROW 3
#define COL 4

typedef Type(*Arr)[COL];//数组指针，开辟COL列数组

Arr _New()
{
	Arr p = new Type[ROW][COL];

	return p;
}
void _Assign(Arr p)
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			p[i][j] = i + j;

		}

	}
}
void _Print(Arr p)
{

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout << p[i][j]<<" ";
		}
		cout <<endl;
	}
}
void _Delete(Arr p)
{
	delete[]p;//c++释放数组

}

int main(int argc, char* argv[])
{
	Arr p = _New();
	_Assign(p);
	_Print(p);
	_Delete(p);
	system("pause");
	return 0;
}
