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
char *charToStr(char ch);
int* charsToInts(char *s);
int str_pos(char *str, char *chr);
char * substr(char *dest, const char* src, unsigned int start, unsigned int len);

/*从字符串的左边截取n个字符*/
char * left(char *dst, char *src, int n);
/*从字符串的中间截取n个字符*/
char * mid(char *dst, char *src, int n, int m);
/*从字符串的右边截取n个字符*/
char * right(char *dst, char *src, int n);

//file_util
//https://github.com/justinkadima/cosmonaut/blob/master/src/string_util.c

int file_exists(char *path);
off_t file_size(char *path);
























