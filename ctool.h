#pragma once

#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <io.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <ctype.h>
#include <sys/stat.h>
#define BOOL int
#define TRUE 1
#define FALSE 0
//目标是实现跨平台的基本库，类似java的api一样
BOOL startsWith(const char* str, const char* token);
BOOL endWith(const char * str, const char * end);
char* boolToStr(BOOL flag);
char* intToStr(int number);
long my_atol(const char *nptr);
//char*=>int
int  my_atoi(const char *nptr);
void charToStr(char ch, char **buffer);
int str_pos(char *str, char *chr);

//file_util
//https://github.com/justinkadima/cosmonaut/blob/master/src/string_util.c

int file_exists(char *path);
off_t file_size(char *path);
























