#include "ctool.h"
#include "stringx/stringx.h"
#include "debug.h"


//c语言任意进制转换
char* transform(int x, int y, char* s)
{
	char *res="";
	int sum = 0;
	for (unsigned int i = 0; i < strlen(s); ++i)
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
		char data[2] = { 0 };
		sprintf(data, "%c", temp);
		res = string_join(data, res);
	}
	if (strlen(res) == 0) res = "0";
	if (s[0] == '-')
	{
		res=string_join("-", res);
	}
	return res;
}

void test_stringx()
{
	split_result* res = string_split_result("123abc123edfgh123ijklm123nop123qrsvx123", "123", 0);
	char* temp;
	while (iterate_split_result(res, &temp))
	{
		puts(temp);
	}
	free_split_result(res);

	printf("%s\n", boolToStr(string_equal("test_txt", "test_txt")));
	printf("%s\n", string_clone("test_txt"));
	printf("%s\n", string_join("中文_", string_join("test_txt", "_hehe")));

	printf("%s\n", boolToStr(string_isNullOrEmpty("test.txt")));
	printf("%s\n", boolToStr(string_isNullOrEmpty("")));
	printf("%s\n", boolToStr(string_isNullOrEmpty(NULL)));

	printf("%s\n", string_trim(" test _   txt "));


	printf("%s %s\n", boolToStr(string_endsWith("test.txt", "txt")), boolToStr(string_endsWith("test.txt", "txxdxt")));
	printf("%s %s\n", boolToStr(string_startsWith("test.txt", "test")), boolToStr(string_startsWith("test.txt", "1test")));

	printf("%s \n", string_replace("123abc123edfgh123ijklm123nop123qrsvx123", "123", "你是猪"));


	printf("%s\n", string_toLower("WWW.BAIDU.COM"));
	printf("%s\n", string_toUpper("www.baidu.com"));
	//抑或加密
	char p[1024] = { 0 };;//只能使用非const
	strcpy(p, "www.baidu.com");
	printf("%s\n", string_XORcypher(p, "java"));

	//随机字符串
	printf("%s\n", string_random(15));
	printf("%s\n", string_htmlEncode("www.baidu.com"));
	printf("%s\n", string_urlEncode("www.baidu.com"));

}
void test_ctool()
{
	printf("%s\n", boolToStr(endWith("test.txt", "txt")));
	printf("%s\n", boolToStr(startsWith("test.txt", "test")));

	printf("%s\n", intToStr(1024));
	printf("%d\n", my_atoi("1024"));
	char p = 'B';
	char data[2] = {0};
	data[0] = p;
	printf("%s\n", data);

	printf("%s\n", transform(10,2,"1024"));
	printf("%s\n", transform(10, 16, "1024"));
	printf("%s\n", transform(2, 10, "10000010"));
	printf("%s\n", transform(2, 16, "10000010"));

	printf("%d\n", str_pos("test.txt_fuck", "txt"));
	

	printf("%s\n", boolToStr(file_exists("d://test.txt")));
	printf("%d\n", file_size("d://test.txt"));


	char *s = "1234789";
	int *arr2 = charsToInts(s);
	for (int i = 0; i < strlen(s); i++)
	{
		printf("%d", arr2[i]);
	}
	printf("\n");
	printf("%s\n", intToStr(10245));
	printf("%s\n", charToStr('A'));

	char dest[1024]={0};
	substr(dest, "123456789", 6, 5);
	printf("%s\n", dest);

	printf("%s\n", left(dest,"abcdefghijk",5));
	printf("%s\n", right(dest, "abcdefghijk8", 5));
	printf("%s\n", mid(dest, "abcdefghijk", 5,2));

}
void test_debug()
{
	__info("hehe");
	
	//__warn("hehe__warn");
	//__fatal("hehe __fatal");


}
int main(int argc, char *argv[])
{
	test_ctool();
	test_debug();



	return 0;
}
