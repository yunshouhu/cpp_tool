//
//  debug.c
//
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include "debug.h"


void debug(char* file,int line,DebugLevel level,char *mes,...)
{
    
    char buf[256];
	
	va_list args;
    va_start (args, mes);
    vsprintf (buf,mes, args);
    va_end (args);

    switch(level)
    {
        case Info:
            fprintf(stderr, "INFO: %s FILE: %s LINE: %i\n",buf,file,line);
            break;
        case Warning:
            fprintf(stderr, "WARNING: %s FILE: %s LINE: %i ERROR: %s\n",buf,file,line,strerror(errno));
            
#if defined(DEBUG)
            
            fprintf(stderr,"Continue(y/n)?\n");
            while(1)
            {
                char key=getchar();
                
                if(key=='n')
                {
                    fprintf(stderr,"Will abord...\n");
                    exit(EXIT_FAILURE);
                }
                if(key=='y')
                {
                    fprintf(stderr, "Will continue..\n");
                    break;
                }
                
            }
            
#endif
            
            break;
        case Fatal:
            fprintf(stderr, "FATAL: %s FILE: %s LINE: %i ERROR: %s\n",buf,file,line,strerror(errno));
            fprintf(stderr,"Will abord...\n");
            exit(EXIT_FAILURE);
            break;
            
            
    }
    
}
