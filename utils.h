
//Created by ���� on 2020/02/23
//Copyright	 2020 ����. All rights reserved.

#pragma once
#include <stdio.h>
#include "my_string.h"

//��ȡ�ļ�,ת��Ϊ�ַ���
String* read_file(char* source);

//�����ַ�����ȡ��������ĸ���
int get_object_num(char* source, char* format);

//�и��ַ���
char* my_split(char* source, char* format);

//�и��ַ���
char* my_split_plus(char* source, char* format, char* last_pointer);

//��ȡ�и��ַ�����lastָ��
char* get_split_last_pointer();

//���ļ��������
void put_multi_row(char* buffer, int num);