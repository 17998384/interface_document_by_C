#pragma once
#include <stdio.h>
#include "my_string.h"

//读取文件,转换为字符串
String* read_file(char* source);

//根据字符串获取解析对象的个数
int get_object_num(char* source, char* format);