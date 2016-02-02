#include <iostream>
#include <fstream>
#include "CBigInt.h"
#include <string>
using namespace std ;


int main(int argc, char** argv)
{
	/**
	ifstream in("data.txt") ;
	#define  cin in 
	string num1, num2 ;
	cin >> num1 >> num2 ;
	*/
	string num1, num2;
	cin >> num1 >> num2;
	CBigInt bi1(num1);
	CBigInt bi2(num2) ;
	cout << "第一个操作数是：" << bi1 << endl ;
	cout << "第二个操作数是：" << bi2 << endl;
	cout << "乘法结果:" << bi1 * bi2 << endl;
	cout <<"加法结果：" << (bi1 + bi2) << endl;
	cout << "减法结果：" <<(bi1 - bi2) << endl;
	cout << "除法的结果是：" << bi1/bi2 << endl;
	cout << "取模的结果是：" << bi1 % bi2 << endl;
	return 0 ;
}
