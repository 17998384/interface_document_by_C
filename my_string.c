#define _CRT_SECURE_NO_WARNINGS
#include "my_string.h"

void string_dilatation(String* str)
{
	str->length = str->length * 2;
	char* new_buffer = (char*)malloc(sizeof(char) * str->length);
	memset(new_buffer, NULL, str->length);
	strcpy(new_buffer, str->buffer);
	free(str->buffer);
	str->buffer = new_buffer;
}

String* new_string()
{
	String* str = (String*)malloc(sizeof(String));
	str->length = 1024;
	str->buffer = (char*)malloc(sizeof(char) * str->length);
	memset(str->buffer, NULL, 1024);
	return str;
}

int string_length(String* str)
{
	if (!str)
	{
		return NULL;
	}
	return strlen(str->buffer);
}

String* string_append(String* str, char* source)
{
	if (!str || !source)
	{
		printf("string对象或目标字符串为null");
		exit(-2);
	}
	//如果需要扩容
	if (strlen(source) > (str->length - string_length(str)))
	{
		string_dilatation(str);
	}
	strcat(str->buffer, source);
}

void delete_string(String* str)
{
	free(str->buffer);
	free(str);
}
