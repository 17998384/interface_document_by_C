#pragma once
#include <stdio.h>
#include "my_string.h"

//��ȡ�ļ�,ת��Ϊ�ַ���
String* read_file(char* source);

//�����ַ�����ȡ��������ĸ���
int get_object_num(char* source, char* format);