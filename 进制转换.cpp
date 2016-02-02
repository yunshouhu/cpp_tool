#include <iostream>
#include <string>
using namespace std;

string transform(int x, int y, string s)
{
	string res = "";
	int sum = 0;
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		if (s[i] == '-') continue;
		if (s[i] >= '0' && s[i] <= '9')
		{
			sum = sum*x + s[i] - '0';
		}
		else {
			sum = sum*x + s[i] - 'A' + 10;

		}

	}
	while (sum)
	{
		char temp = sum %y;
		sum /= y;
		if (temp <= 9)
		{
			temp += '0';
		}
		else {
			temp = temp - 10 + 'A';
		}
		res = temp + res;
	}
	if (res.length() == 0) res = "0";
	if (s[0] == '-')
		res = '-' + res;
	return res;
}
int main(int argc, char* argv)
{

	cout << transform(10,2,"1024") << endl;
	cout << transform(10, 16, "1024") << endl;
	cout << transform(10, 8, "1024") << endl;
	cout << transform(8, 10, "1024") << endl;
	cout << transform(8, 16, "1024") << endl;
	cout << transform(16, 10, "1024") << endl;
	cout << transform(2, 10, "10000010") << endl;
	cout << transform(2, 16, "10000010") << endl;

	int aa,bb,cc,dd; 

	aa = bb = cc = dd = 1; 
	aa = bb = cc = dd = 1; 
	aa = bb = cc = dd = 1;
	
	(aa + 1 == 2) ? bb = aa + 2 : aa + 3;
	cout << aa << bb << endl;


	char A[]= "He has tez !";
	cout << strlen(A) << endl;
	return 0;
}
