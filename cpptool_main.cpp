#include "cpptool.h"
#include "stringx/stringx.h"

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

	printf("%s\n", string_replace("123abc123edfgh123ijklm123nop123qrsvx123", "123", "你是猪"));


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
void test_cpptool()
{
	cout << transform(10, 2, "1024") << endl;
	cout << transform(10, 16, "1024") << endl;
	cout << transform(10, 8, "1024") << endl;
	cout << transform(8, 10, "1024") << endl;
	cout << transform(8, 16, "1024") << endl;
	cout << transform(16, 10, "1024") << endl;
	cout << transform(2, 10, "10000010") << endl;
	cout << transform(2, 16, "10000010") << endl;

}
int main(int argc, char *argv[])
{
	test_stringx();
	test_cpptool();



	return 0;
}
