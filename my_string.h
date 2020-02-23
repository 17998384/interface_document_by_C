
//Created by ¸ðÕñ¶« on 2020/02/23
//Copyright	 2020 ¸ðÕñ¶«. All rights reserved.

#pragma once
#include <string.h>
typedef struct string
{
	int length;
	char* buffer;
}String;


//´´½¨×Ö·û´®
String* new_string();

//×Ö·û´®³¤¶È
int string_length(String* str);

//×·¼Ó×Ö·û´®
String* string_append(String* str, char* source);

//Çå¿Õ×Ö·û´®
String* string_clear(String* str);

//É¾³ý×Ö·û´®
void delete_string(String* str);