#define _CRT_SECURE_NO_DEPRECATE
//#include <vld.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <stdlib.h>
#include <direct.h>
#include <vector>
#include <string>
#include <iostream>
#include <iterator>
using namespace std;


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

void getCurrentFileList(std::vector<std::string> &filelist,char *ext)
{
	long file;
	struct _finddata_t find;	
	_chdir(".");
	if ((file = _findfirst("*.*", &find)) == -1L)
	{
		//printf("空白!\n");		
	}
	if(endWith(find.name,ext))
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
int readFile(char* filename,char *query)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("读取文件%s失败!", filename);
		return -1;
	}
	bool isPrinfFileName = false;
	while (!feof(fp))
	{
		char line[1024];
		char *p;
		fgets(line, 1024, fp);
		p = strstr(line, query);
		if (p != NULL)
		{
			if(isPrinfFileName==false)
			{
				printf("%s:\n", filename);
				isPrinfFileName = true;
			}
			fputs(line, stdout);
		}
	}
	fclose(fp);
	return 0;
}
//kaifang开房数据查询.exe android .txt  把txt文件放在同一个目录下
int main(int argc,char *argv[])
{
	char *query = "hehe";
	char *ext = ".txt";
	if(argc<=1)
	{
		printf("useage:%s query .ext",argv[0]);
		return -1;
	}
	if(argc>1)
	{
		query = argv[1];		
	}
	if(argc>2)
	{
		ext = argv[2];
	}
	time_t startTime, endTime;
	time(&startTime);
	vector<string> filelist;
	getCurrentFileList(filelist,ext);
	std::vector<string>::iterator it;
	for (it = filelist.begin(); it != filelist.end();it++)
	{
		char* filename = const_cast<char*> (it->c_str());
		readFile(filename, query);
	}
	time(&endTime);

	printf("查询%s,总共花费%.2f秒\n",query, difftime(endTime, startTime));

	return 0;
}
