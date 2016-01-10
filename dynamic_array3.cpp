
/************************************************************************/
/*三维数组                                                               */
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
#define Z 3


typedef Type(*Arr)[ROW][COL];//三维数组指针，开辟COL列数组

Arr _New()
{
	Arr p = new Type[Z][ROW][COL];

	return p;
}
void _Assign(Arr p)
{
	for (int k = 0; k < Z; ++k)
	{
		for (int i = 0; i < ROW; ++i)
		{
			for (int j = 0; j < COL; ++j)
			{
				p[k][i][j] = i + j+k;
			}
		}
	}
}
void _Print(Arr p)
{

	for (int k = 0; k < Z; ++k)
	{
		for (int i = 0; i < ROW; ++i)
		{
			for (int j = 0; j < COL; ++j)
			{
				cout << p[k][i][j]<< " ";
			}			
		}
		cout << endl;
	}
}
void _Delete(Arr p)
{
	delete []p;//c++释放数组

}

int main(int argc, char* argv[])
{
	Arr p = _New();
	_Assign(p);
	_Print(p);
	_Delete(p);
	return 0;
}