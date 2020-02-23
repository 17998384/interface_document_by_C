#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"
#include "interface_document.h"
#include "interface_document_file.h"
#include <Windows.h>
#define COUNT 100000
#define INTERFACE_BODYS_PATH "C:\\Users\\a1799\\Desktop\\interface_body.txt"
#define INTERFACE_HEADS_PATH "C:\\Users\\a1799\\Desktop\\interface_head.txt"
#define OUTPUT_FILE_PATH "C:\\Users\\a1799\\Desktop\\test_file.md"
#define INTERFACE_DOCUMENT_TITLE "测试接口文档"
#define INTERFACE_SIZE 2
void test_my_string()
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

void test_interface_document()
{
	printf("create...\n");
	String* interface_bodys_str = read_file(INTERFACE_BODYS_PATH);
	String* interface_heads_str = read_file(INTERFACE_HEADS_PATH);
	InterfaceBody** interface_bodys = parse_interface_body(interface_bodys_str, INTERFACE_SIZE);
	InterfaceHead** interface_heads = parse_interface_head(interface_heads_str, INTERFACE_SIZE);
	//构建接口文档
	InterfaceDocument* interface_document = build_interface_document(INTERFACE_SIZE
		, interface_bodys_str, interface_heads_str, interface_bodys, interface_heads);
	//输出到文件
	//output_to_file(interface_document, OUTPUT_FILE_PATH, INTERFACE_DOCUMENT_TITLE);
	printf("create success!\n");
	delete_interface_document(interface_document);
}

void test_readfile()
{
	String* interface_bodys_str = read_file(INTERFACE_BODYS_PATH);
	delete_string(interface_bodys_str);
}


int main(void)
{
	for (int i = 0; i < COUNT; i++)
	{
		test_interface_document();
		//test_my_string();
		//get_object_num("fdsfdsfdfdsfdsf\nfdfd", "\n");
		//test_readfile();
		//Sleep(1);
	}
	return 0;
}