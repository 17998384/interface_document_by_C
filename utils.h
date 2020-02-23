
//Created by 葛振东 on 2020/02/23
//Copyright	 2020 葛振东. All rights reserved.

#pragma once
#include <stdio.h>
#include "my_string.h"

//读取文件,转换为字符串
String* read_file(char* source);

//根据字符串获取解析对象的个数
int get_object_num(char* source, char* format);

//切割字符串
char* my_split(char* source, char* format);

//切割字符串
char* my_split_plus(char* source, char* format, char* last_pointer);

//获取切割字符串的last指针
char* get_split_last_pointer();

//向文件输出多行
void put_multi_row(char* buffer, int num);