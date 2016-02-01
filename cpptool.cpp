#include "cpptool.h"

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

bool endWith(const char * str, const char * end)
{
	bool result = false;
	if (str != NULL && end != NULL)
	{
		int l1 = strlen(str);
		int l2 = strlen(end);
		if (l1 >= l2) {
			if (strcmp(str + l1 - l2, end) == 0)
			{
				result = true;
			}
		}
	}
	return result;
}
char* boolToStr(int flag)
{
	return flag ? "true" : "false";
}
void getCurrentFileList(std::vector<std::string> &filelist, char *ext)
{
	long file;
	struct _finddata_t find;
	_chdir(".");
	if ((file = _findfirst("*.*", &find)) == -1L)
	{
		//printf("¿Õ°×!\n");		
	}
	if (endWith(find.name, ext))
	{
		filelist.push_back(string(find.name));
	}
	while (_findnext(file, &find) == 0)
	{
		//printf("%s\n", find.name);
		if (endWith(find.name, ext))
		{
			filelist.push_back(string(find.name));
		}
	}
	_findclose(file);
}