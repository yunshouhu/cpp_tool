//
//  debug.h
//  glututor1
//
//  Created by Macbook White on 11/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#define _CRT_SECURE_NO_DEPRECATE

#ifndef DEBUG_H
#define DEBUG_H

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<stdarg.h>
#include<string.h>

typedef enum
{
        Info,
        Warning,
        Fatal
    
}DebugLevel;

//https://github.com/justinkadima/cLibrary/blob/master/debug.c

#define __info(mes,...) debug(__FILE__,__LINE__,Info,mes,__VA_ARGS__)

#define __fatal(mes,...) debug(__FILE__,__LINE__,Fatal,mes,__VA_ARGS__)

#define __warn(mes,...) debug(__FILE__,__LINE__,Warning,mes,__VA_ARGS__)

void debug(char* file,int line,DebugLevel level,char *mes,...);


#endif
