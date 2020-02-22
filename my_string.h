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

//É¾³ý×Ö·û´®
void delete_string(String* str);