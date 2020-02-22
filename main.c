#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"
#include "interface_document.h"
#define COUNT 1000
int test_my_string()
{
	String* str = new_string();
	for (int i = 0; i < COUNT; i++)
	{
		string_append(str, "fdsfsdfewfsdsdfdsfds");
	}
	printf("字符串的内容是:%s\n", str->buffer);
	printf("字符串的长度是:%d\n", string_length(str));
	delete_string(str);
}
int main(void)
{
	InterfaceBody** inter_face_body = parse_interface_body("C:\\Users\\a1799\\Desktop\\format.txt", 2);
	system("pause");
	return 0;
}