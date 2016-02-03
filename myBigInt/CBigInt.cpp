#include "CBigInt.h"
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
#include <cassert>
using namespace std;

CBigInt :: CBigInt() : values(""), flag(true)
{
}

CBigInt :: CBigInt(const int i)
{
	values.clear() ;
	if (i >= 0) flag = true ;
	else
		flag = false ;
	int v = abs(i) ;
	while(v)
	{
		values.push_back(char('0' + (v % 10))) ;
		v /= 10 ;
	}
	reverse(values.begin(), values.end()) ;
	if (values.empty())
	{
		values.push_back('0') ;
		flag = true ;
	}
}

CBigInt :: CBigInt(const string& strValues)
{
	setValue(strValues) ; //调用成员函数完成
}

CBigInt :: CBigInt(const CBigInt& bigInt) : values(bigInt.values), flag(bigInt.flag)
{
}

CBigInt :: ~CBigInt()
{}

const CBigInt CBigInt :: absolute() const
{
	CBigInt ret(*this) ;
	ret.flag = true ;
	return ret ;
}
int CBigInt :: compareBitInt(const CBigInt& rhs)const
{
	//异号情况
	if (flag && !rhs.flag) return 1 ;
	if (!flag && rhs.flag) return -1 ;

	//同号情况，先比较绝对值，然后根据符号判断大小
	int ret = 0 ;
	if (values.length() > rhs.values.length()) ret = 1 ;
	else
		if (values.length() < rhs.values.length()) ret = -1 ;
	else
		ret = values.compare(rhs.values) ;

	if (flag) return ret ;
	return -ret ;
}


void CBigInt :: setValue(const string& strValues)
{
	values.clear() ;
	string tmpStr(strValues.begin() + strValues.find_first_not_of(' '), strValues.end()) ; //去掉前面的空格
	if (tmpStr.empty())
	{
		values.push_back('0') ;
		flag = true ;
		return ;
	}

	if (tmpStr.at(0) == '-' )
		flag = false ;
	else
		flag = true ;
	int i = tmpStr.find_first_of("0123456789") ;
	int j = tmpStr.find_last_of("0123456789") ;

	values = tmpStr.substr(i, j - i + 1) ;//从符号位之后开始的所有数字，直到遇到第一个非数字位
}

CBigInt& CBigInt :: operator = (const CBigInt& rhs)
{
	this->values = rhs.values ;
	this->flag = rhs.flag ;
	return *this ;
}

ostream& operator << (ostream& ou, const CBigInt& bigInt)
{
	if (!bigInt.flag)
		ou << '-';
	ou << bigInt.values ;
	return ou ;
}

istream& operator >> (istream& in, CBigInt& bigInt)
{
	string str ;
	in >> str ;
	bigInt.setValue(str) ; //设置读入的新的数值
	return in ;
}

const CBigInt operator + (const CBigInt& lhs, const CBigInt& rhs)
{
	CBigInt ret ;
	if (lhs.flag == rhs.flag) //符号相同
	{
		string lvalues(lhs.values) , rvalues(rhs.values) ;
		reverse(lvalues.begin(), lvalues.end()) ;
		reverse(rvalues.begin(), rvalues.end()) ;

		//逐位相加
		int i = 0;
		for ( ; i < lvalues.length() && i < rvalues.length(); ++ i)
			ret.values.push_back(lvalues.at(i) + rvalues.at(i) - '0') ;

		if (i < lvalues.length())
			for (; i < lvalues.length(); ++ i)
				ret.values.push_back(lvalues.at(i)) ;
		else
			for (; i < rvalues.length(); ++ i)
				ret.values.push_back(rvalues.at(i)) ;
		//处理进位
		int carry = 0;
		for (int i = 0; i < ret.values.length(); ++ i)
		{
			int newValue = ret.values.at(i) - '0' + carry ;
			carry = newValue/ 10 ;
			ret.values.at(i) = newValue - carry * 10 + '0' ;
		}
		if (carry)
			ret.values.push_back(carry + '0') ;

		//处理符号
		ret.flag = lhs.flag ;
	}
	else //符号不同
	{
		CBigInt absL = lhs.absolute() ;
		CBigInt absR = rhs.absolute() ;
		int compFlag = absL.compareBitInt(absR) ;
		if (compFlag == 0)
		{
			ret.setValue("0") ;
			ret.flag = true ;
			return ret ;
		}
		else
		{
			if (compFlag == -1) //交换位置，使得absL > absR
			{
				CBigInt tmp(absL) ;
				absL = absR ;
				absR = tmp ;
			}

			reverse(absL.values.begin(), absL.values.end()) ;
			reverse(absR.values.begin(), absR.values.end()) ;

			//处理差值
			int i = 0;
			for (; i < absL.values.length() && i < absR.values.length(); ++ i)
				ret.values.push_back(absL.values.at(i) - absR.values.at(i) + '0') ;
			
			if (i < absL.values.length()) //不可能出现i < absR.values.length()的情况
				for (; i < absL.values.length(); ++ i) 
					ret.values.push_back(absL.values.at(i)) ;
			
			//处理借位
			int carry = 0 ;
			for (i = 0; i < ret.values.length(); ++ i)
			{
				int newValue = ret.values.at(i) - carry - '0' ;
				if (newValue < 0) carry = 1 ; //向前借位
				else carry = 0 ;
				ret.values.at(i) = newValue + carry * 10 + '0' ;
			}
			//处理符号
			if (compFlag == 1)
				ret.flag = lhs.flag ;
			else
				ret.flag = rhs.flag;
		}
	}

	reverse(ret.values.begin(), ret.values.end()) ;
	int i = ret.values.find_first_not_of(" 0") ;
	if (i == string :: npos)//空的，说明结果是0
	{
		ret.setValue("0") ;
		ret.flag = true ;
		return ret ;
	}
	ret.values = string(ret.values.begin() + ret.values.find_first_not_of(" 0"), ret.values.end()) ; //去掉前面的空白和0
	return ret ;
}

const CBigInt operator - (const CBigInt& lhs, const CBigInt& rhs)
{
	CBigInt tmpRhs(rhs) ;
	tmpRhs.flag = !tmpRhs.flag ; //取负号

	return (lhs + tmpRhs) ;
}

//乘法操作符重载
const CBigInt operator * (const CBigInt& lhs, const CBigInt& rhs)
{
	CBigInt ret ;
	int flag1 = lhs.compareBitInt(CBigInt(0)) ;
	int flag2 = rhs.compareBitInt(CBigInt(0)) ;
	if (flag1 == 0 || flag2 == 0)
	{
		ret.setValue("0") ;
		ret.flag = true ;
		return ret ;
	}
	if (lhs.flag == rhs.flag) 
		ret.flag = true ;//同号为正，异号为负
	else 
		ret.flag = false ;

	string lvalues(lhs.values), rvalues(rhs.values) ;
	reverse(lvalues.begin(), lvalues.end())  ;
	reverse(rvalues.begin(), rvalues.end()) ;
	ret.values.resize(lvalues.size() + rvalues.size(), '0') ;

	//相乘
	for (int i = 0; i < lvalues.size(); ++ i)
		for (int j = 0; j < rvalues.size(); ++ j)
		{
			int newValue = ret.values[i + j] +  (lvalues[i] - '0') * (rvalues[j] - '0') - '0';
			int carry = newValue / 10 ;
			ret.values[i + j] = newValue % 10 + '0' ;

			//这里之所以对每一位进行进位处理，是为了防止出现溢出情况的出现，如'0' + 9 * 9 = 48 + 81 > 127已经溢出
			for (int k = i + j + 1; carry != 0 && k < ret.values.size(); ++ k) //处理进位
			{
				ret.values[ k - 1 ] = newValue % 10 + '0' ;
				newValue = ret.values[k] + carry - '0';
				ret.values[k] = newValue % 10 + '0' ;
				carry = newValue / 10 ;
			}
		}

	reverse(ret.values.begin(), ret.values.end()) ; //翻转
	ret.values = string(ret.values.begin() + ret.values.find_first_not_of(" 0"), ret.values.end()) ; //去掉前面的空白和0

	return ret ;
}

const CBigInt operator / (const CBigInt& lhs, const CBigInt& rhs)  //除法操作重载
{
	CBigInt ret ;
	assert(rhs.compareBitInt(CBigInt(0)) != 0) ;
	ret.setValue("0") ; //初始化为0

	CBigInt absL(lhs.absolute()) ;
	CBigInt absR(rhs.absolute()) ;

	int comFlag = absL.compareBitInt(absR) ;
	if (comFlag < 0)
		return ret ;
	if(comFlag == 0)
	{
		ret.setValue("1") ;
		if (lhs.flag == rhs.flag) ret.flag = true ;
		else
			ret.flag = false ;
		return ret ;
	}
	int movCount = absL.values.size() - absR.values.size() ;

	const CBigInt tenBigInt(10) ;
	//使用减法实现除法的操作
	do 
	{
		CBigInt tmp(absR) ;
		for (int i = 0; i < movCount; ++ i) //tmp是10的movCount次方
			tmp = tmp * tenBigInt ;
		int addNum = 0 ;
		while(absL.compareBitInt(tmp) >= 0)
		{
			absL = absL - tmp ;
			addNum ++ ;
		}

		ret = ret * tenBigInt + CBigInt (addNum) ;

		movCount -- ;

	}while (movCount >= 0);

	if (lhs.flag == rhs.flag) ret.flag = true ;
	else
		ret.flag = false ;

	return ret ;
}

const CBigInt operator % (const CBigInt& lhs, const CBigInt& rhs)  //取模运算操作符重载
{
	CBigInt divTmp = lhs / rhs ;
	return (lhs - rhs * divTmp) ;
}