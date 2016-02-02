

#ifndef STRINGX_H
#define STRINGX_H

//https://github.com/justinkadima/cString
#ifdef __cplusplus
extern "C" {
#endif

int string_equal(const char* s1,const char* s2);
char* string_malloc(size_t len);
char* string_clone(const char* str);
char* string_join(const char* str1,const char* str2);

int string_resize(char** str,size_t newsz);
int string_append(char** str,const char* post);
int string_prepend(const char* ante,char** str);

int string_countOccurence(const char* str,const char* token);
int string_isNullOrEmpty(const char* str);

    

char* string_trim(const char* str);
char* string_trimRight(const char* str);
char* string_trimLeft(const char* str);
char* string_trimMultiple(const char* str,const char* keys);
    
unsigned int string_endsWith(const char* str,const char* token);
unsigned int string_startsWith(const char* str,const char* token);

typedef enum
{
	Out,
	In
}TokensInclusion;

char* string_replaceBetweenTokens(const char* str,const char* tokenstart,const char* tokenend,const char* val,TokensInclusion withtokens);
char* string_extractBetweenTokens(const char* str,const char* tokenstart,const char* tokenend);
char* string_replace(const char* str,const char* oldval,const char* newval);

int string_split(const char* text,const char* delim,char*** tokens,int maxnr);

typedef struct
{
    char** tokens;
    int nr;
}split_result;

int iterate_split_result(split_result* res,char** val);
void free_split_result(split_result* res);
split_result* string_split_result(const char* text,const char* delim,int maxnr);

char* string_toLower(const char* str);
char* string_toUpper(const char* str);

char* string_XORcypher(char* str,const char* key);
char* string_random(int len);

char* string_htmlEncode(const char* str);
char* string_urlEncode(const char* str);




#ifdef __cplusplus
}
#endif

#endif
