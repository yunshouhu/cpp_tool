#pragma once

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


string transform(int x, int y, string s);
bool endWith(const char * str, const char * end);
void getCurrentFileList(std::vector<std::string> &filelist, char *ext);
char* boolToStr(int flag);
