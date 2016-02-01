#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stringx.h"



char* string_malloc(size_t len)
{
	char* ret=(char*)malloc(len+1);
	if(ret!=NULL)
	{
		ret[len]='\0';
		
	}
	return ret;

}

char* string_clone(const char* str)
{
    if(str!=NULL)
    {
            char* ret=string_malloc(strlen(str));
            if(ret)
            {
           		strcpy(ret,str);
           		return ret;
            }
    }
    return NULL;
}

int string_equal(const char* s1,const char* s2)
{
	if(s1==NULL || s2==NULL) return 0;
	return (strcmp(s1,s2)==0);
}



int string_isNullOrEmpty(const char* str)
{
	if(str!=NULL && str[0]!='\0')return 0;
	return 1;

}

int string_countOccurence(const char* str,const char* token)
{
	int x=0;
	if(!string_isNullOrEmpty(str) && !string_isNullOrEmpty(token))
	{
		
		char* temp=(char*)str;
		while((temp=strstr(temp,token))!=NULL)
		{
			temp+=strlen(token);
			x++;
		}
	}
	return x;
}



char* string_replace(const char* str,const char* oldval,const char* newval)
{
	if(!string_isNullOrEmpty(str) && !string_isNullOrEmpty(oldval) && !string_isNullOrEmpty(newval))
	{

		int oc=string_countOccurence(str,oldval);

		if(oc>0)
		{
			size_t diff=strlen(newval)-strlen(oldval);
			size_t nsize=strlen(str)+oc*diff+1;
			
			char* buff=(char*) calloc(1,nsize);

			if(buff!=NULL)
			{
				char* temp=NULL;
				char* mark=(char*)str;

				while((temp=strstr(mark,oldval))!=NULL)
				{
					
					size_t off=strlen(mark)-strlen(temp);

					strncat(buff,mark,off);
					strncat(buff,newval,strlen(newval));

					temp+=strlen(oldval);
					mark=temp;
				}

				strncat(buff,mark,strlen(mark));

				return buff;
			}

			free(buff);

		}

	}
	return NULL;
}


char* string_extractBetweenTokens(const char* str,const char* tokenstart,const char* tokenend)
{
	if(!string_isNullOrEmpty(str) && !string_isNullOrEmpty(tokenstart) && !string_isNullOrEmpty(tokenend))
	{
		char* tok1=strstr((char*)str,tokenstart);
		if(tok1!=NULL)
		{
			tok1+=strlen(tokenstart);
			char* tok2=strstr(tok1,tokenend);

			if(tok2!=NULL)
			{
				size_t off=strlen(tok1)-strlen(tok2);
				char* buff=(char*)calloc(1,off+1);
				strncpy(buff,tok1,off);
				return buff;
			}

		}

	}
	return NULL;

}



char* string_replaceBetweenTokens(const char* str,const char* tokenstart,const char* tokenend,const char* val,TokensInclusion withtokens)
{
	if(!string_isNullOrEmpty(str) && !string_isNullOrEmpty(tokenstart) && !string_isNullOrEmpty(tokenend) && !string_isNullOrEmpty(val))
	{
		char* tok1=strstr((char*)str,tokenstart);
		if(tok1!=NULL)
		{
			if(withtokens==In)
			{
				tok1+=strlen(tokenstart);
				
			}
			
			size_t dift1=strlen(str)-strlen(tok1);
			char* tok2=strstr(tok1,tokenend);

			if(tok2!=NULL)
			{
				if(withtokens==Out)
				{
					tok2+=strlen(tokenend);
				}
				size_t newsize=dift1+strlen(val)+strlen(tok2);
				char* buff=(char*)calloc(1,newsize+1);

				strncat(buff,str,dift1);
				strcat(buff,val);
				strcat(buff,tok2);

				return buff;


			}

		}


	}

	return NULL;
}


unsigned int string_startsWith(const char* str,const char* token)
{	
		if(str==NULL || token==NULL)return 0;
        return (strncmp(str,token,strlen(token))==0);
        
}

unsigned int string_endsWith(const char* str,const char* token)
{
	
        if(!string_isNullOrEmpty(str) && !string_isNullOrEmpty(token))
		{
           int off=strlen(str)-strlen(token);
           if(off>=0)
           {
               char* temp=(char*)str;
               temp+=off;
               return (strncmp(temp,token,strlen(token))==0);
           }
        }
        return 0;

}


int iterate_split_result(split_result* res,char** val)
{
    if(res && res->nr>0)
    {
        static int idx=-1;
        if(idx>=(res->nr-1))return 0;
        
        idx++;
        (*val)=res->tokens[idx];
        return 1;
    }
    return 0;
}
void free_split_result(split_result* res)
{
    if(res && res->nr>0)
    {
        int x;
        for(x=0;x<res->nr;x++)
        {
            free(res->tokens[x]);
            res->tokens[x]=NULL;
        }
    }
    free(res->tokens);
    res->tokens=NULL;
    
    free(res);
    res=NULL;
}

split_result* string_split_result(const char* text,const char* delim,int maxnr)
{
    if(!maxnr)maxnr=100;
    
    split_result* result=malloc(sizeof(split_result));
    result->tokens=malloc(maxnr*sizeof(char*));
    result->nr=0;
    
    char* temp=(char*)text;
    
    while(1)
    {
        char* back=temp;
        temp=strstr(temp,delim);
        if(temp)
        {
            
            if(maxnr<=(result->nr))break;
            
            int off=strlen(back)-strlen(temp);
            temp+=strlen(delim);
            if(off<=0)
            {
                continue;
            }
            char* word=malloc(off+1);
            strncpy(word,back,off);
            word[off]='\0';
        
            
            result->tokens[result->nr]=word;
            result->nr++;
            
        }
        else
        {
            break;
        }
        
    }
    return result;
    
}

int string_split(const char* text,const char* delim,char*** tokens,int maxnr)
{
    char* temp=(char*)text;
    int nrtokens=0;
    
    if(!maxnr)
    {
        maxnr=100;
    }
    
    (*tokens)=malloc(maxnr*sizeof(char*));
    
    while(1)
    {
        char* back=temp;
        temp=strstr(temp,delim);
        if(temp)
        {
           
            
            if(maxnr<=(nrtokens))break;
            
            int off=strlen(back)-strlen(temp);
            temp+=strlen(delim);
            if(off<=0)
            {
                continue;
            }
            char* word=malloc(off+1);
            strncpy(word,back,off);
            word[off]='\0';
        
            
            (*tokens)[nrtokens]=word;
            nrtokens++;
            
        }
        else
        {
            break;
        }
        
    }
    return nrtokens;
}


char* string_trimLeft(const char* str)
{
	if(!string_isNullOrEmpty(str))
	{
		int off=0;
		while(1)
		{
			
			if(str[off]==' ')
			{
				off++;
			}
			else
			{
				break;
			}
		}

		if(off>0 && off<strlen(str))
		{
			char* temp=NULL;
			char* ret=(char*)calloc(strlen(str)-off+1,sizeof(char));
			if(ret!=NULL)
			{
				temp=(char*)str;
				temp+=off*sizeof(char);
				strncpy(ret,temp,strlen(str)-off);
				return ret;
			}
		}
		

	}
	return NULL;
}

char* string_trimRight(const char* str)
{
	if(!string_isNullOrEmpty(str))
	{
		int off=0;
                int x;
                
		for(x=(int)(strlen(str)-1);x>=0;x--)
		{
			
			if(str[x]==' ')
			{
				off++;
			}
			else
			{
				break;
			}

		}

		if(off>0 && off<strlen(str))
		{
			
			char* ret=(char*)calloc(strlen(str)-off+1,sizeof(char));
			if(ret!=NULL)
			{
				strncpy(ret,str,strlen(str)-off);
				return ret;
			}
		}

	}

	return NULL;
}


char* string_trim(const char* str)
{
    if(!string_isNullOrEmpty(str))
    {
        char* temp=string_trimLeft(str);
        char* sec=NULL;
        if(temp==NULL)
        {
            sec=(char*)str;
        }
        else
        {
            sec=temp;
        }
        char* res=string_trimRight(sec);
        if(temp!=NULL)
        {
            if(res==NULL)res=temp;
            else free(temp);
            
        }
        return res;
    }
    return NULL;
}





char* string_trimMultiple(const char* str,const char* keys)
{
    
    char* temp=strpbrk(str,keys);
    char* old=(char*)str;
    
    if(temp!=NULL)
    {
      char* buf=(char*)calloc(1,strlen(str)+1); 

    while(1)
    {

        size_t diff=strlen(old)-strlen(temp);
        
        
        if(diff>0)
        {

            strncat(buf,old,diff);
            
        }
        
        old=temp+1;
        temp=strpbrk(old,keys);
        if(temp==NULL)
        {
            strncat(buf,old,strlen(old));
            break;
        }
    }
        return buf;
    }
    
    return NULL;
    
}




char* string_join(const char* str1,const char* str2)
{
    if(str1==NULL && str2==NULL)
    {
        return NULL;
    }
    
    size_t sz1=0;
    size_t sz2=0;
    
    
   
    if(str1!=NULL)sz1=strlen(str1);
    if(str2!=NULL)sz2=strlen(str2);
    
    char* ret=(char*)calloc(sz1+sz2+1,sizeof(char));
    if(ret!=NULL)
    {
        if(str1!=NULL)
        {
            ret=strcat(ret,str1);
        }
        if(str2!=NULL)
        {
            ret=strcat(ret,str2);
        }
        
        return ret;
    }
    
    return NULL;
   
    
}



int string_resize(char** str,size_t newsz)
{
	if(newsz<=0)return 0;
	
	size_t strsz=strlen(*str);
	if(strsz==newsz)return 1;
	else
	{
		char* temp=(char*)realloc(*str,newsz+1);
		if(temp)
		{
			*str=temp;
			if(newsz<strsz)
			{
			
				(*str)[newsz]='\0';
				
			}
			return 1;
		}
	}
	
	return 0;
}


int string_append(char** str,const char* post)
{
	if(!(*str) || !post)
	{
		return 0;
	}
	
	if(string_resize(&(*str),strlen(post)))
	{
		*str=strcat(*str,post);
		return 1;
	}
	return 0;
}

int string_prepend(const char* ante,char** str)
{
	if(!ante || !(*str))
	{
		return 0;
	}
	size_t sz=strlen(ante);
	
	if(string_resize(&(*str),sz+1))
	{
		memmove((*str)+sz, (*str),sz+1);
		memcpy((*str),ante,sz);
		return 1;
	}
	
	return 0;
}


char* string_toLower(const char* str)
{
    if(str!=NULL)
    {
        char* ret=string_clone(str);
        int x=0;
        int sx=strlen(str);
        while(x<sx)
        {
            ret[x]=tolower(ret[x]);
            x++;
        }
        return ret;
    }
    return NULL;
    
}

char* string_toUpper(const char* str)
{
	if(str!=NULL)
	{
		char* ret=string_clone(str);
		if(ret==NULL)return NULL;
		int x=0,sx=strlen(str);
		
		while(x<sx)
		{
			ret[x]=toupper(ret[x]);
			x++;

		}
		return ret;

	}
	return NULL;

}

char* string_htmlEncode(const char* str)
{
	if(str!=NULL)
	{
		int x=0;
        size_t len=strlen(str);
        char* ret=(char*)calloc(3*len+1,sizeof(char));
        if(ret==NULL)return NULL;
        
        char* buf=(char*)calloc(10,sizeof(char));
        if(buf==NULL)
        {
        	free(ret);
        	return NULL;
        }
        
       
        while(x<len)
        {
        	switch(str[x])
        	{
        		case '&':
        			sprintf(buf,"%s","&amp;");
        		break;
        		case '\"':
        			sprintf(buf,"%s","&quot;");
        		break;
        		case '\'':
        			sprintf(buf,"%s","&apos;");
        		break;
        		case '<':
        			sprintf(buf,"%s","&lt;");
        		break;
        		case '>':
        			sprintf(buf,"%s","&gt;");
        		break;
        		default:
        			sprintf(buf,"%c",str[x]);
        	}
        	strcat(ret,buf);
        	x++;
        }         
		free(buf);
		return ret;

	}
	return NULL;



}

char* string_urlEncode(const char* str)
{

	if(str!=NULL)
	{
		int x=0;
        size_t len=strlen(str);
        char* ret=(char*)calloc(3*len+1,sizeof(char));
        if(ret==NULL)return NULL;
        
        char* buf=(char*)calloc(10,sizeof(char));
        if(buf==NULL)
        {
        	free(ret);
        	return NULL;
        }
        
        while(x<len)
        {
        		char c=str[x];
        		
        		if( ('a' <= c && c <= 'z')|| ('A' <= c && c <= 'Z')|| ('0' <= c && c <= '9') )
        		{
        			sprintf(buf,"%c",c);
        	
        		}
        		else
        		{
        			sprintf(buf,"%%%02X",c);
        		}
        	
        	strcat(ret,buf);
        	x++;
        }         
		free(buf);
		return ret;

	}
	return NULL;

}



char* string_XORcypher(char* str,const char* key)
{
	if(string_isNullOrEmpty(str) || string_isNullOrEmpty(key))
	{
		return str;	
	
	}
	
	int szstr=(int)strlen(str);
	int szkey=(int)strlen(key);
	
	int x=0;
	int y=0;
	
	
	
	while(x<szstr)
	{
		str[x]=str[x]^key[y];
		x++;
		y++;
		
		if(y==szkey)y=0;	
	
	}
	
	return str;
}



char* string_random(int len)
{
	static const char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* ret=string_malloc(len);
	if(ret)
	{
		int idx=0;
		while(idx<len)
		{
			ret[idx]=alphabet[rand() % (sizeof(alphabet) - 1)];
			idx++;
		}
		
	}
	return ret;

}






