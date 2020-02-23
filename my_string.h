
//Created by ���� on 2020/02/23
//Copyright	 2020 ����. All rights reserved.

#pragma once
#include <string.h>
typedef struct string
{
	int length;
	char* buffer;
}String;


//�����ַ���
String* new_string();

//�ַ�������
int string_length(String* str);

//׷���ַ���
String* string_append(String* str, char* source);

//����ַ���
String* string_clear(String* str);

//ɾ���ַ���
void delete_string(String* str);