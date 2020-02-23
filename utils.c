#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
static char* last = NULL;
String* read_file(char* source)
{
	FILE* file = fopen(source, "r");
	if (!file)
	{
		printf("文件打开失败,自动退出!");
		exit(-1);
	}
	//创建字符串对象
	String* str = new_string();
	//创建缓冲区
	char* buffer = (char*)malloc(1024);
	check_memory(str);
	check_memory(buffer);
	//读取文件追加到字符串对象
	while (!feof(file))
	{
		fgets(buffer, 1024, file);
		string_append(str, buffer);
	}
	free(buffer);
	fclose(file);
	return str;
}

int get_object_num(char* source, char* format)
{
	char* copy_source = (char*)malloc(sizeof(char) * strlen(source) + 1);
	check_memory(copy_source);
	strcpy(copy_source, source);
	int count = 0;
	char* next = NULL;
	char* temp = my_split_plus(copy_source, format, NULL);
	while (temp)
	{
		++count;
		next = get_split_last_pointer();
		temp = my_split_plus(NULL, format, next);
	}
	free(copy_source);
	return count;
}

char* my_split(char* source, char* format)
{
	if (format == NULL)
	{
		return NULL;
	}
	if (source == NULL)
	{
		source = last;
		if (source == NULL)
		{
			return NULL;
		}
	}
	int count = 0;
	int source_index = 0;
	int temp_source_index = 0;
	int format_index = 0;
	int format_length = strlen(format);
	while (source[source_index] != '\0')
	{
		if (source[source_index++] == format[format_index++])
		{
			count++;
			if (count == format_length)
			{
				temp_source_index = source_index - count;
				for (int i = 0; i < count; i++)
				{
					source[temp_source_index++] = '\0';
				}
				last = source + source_index;
				if (*last == '\0')
					last = NULL;
				return source;
			}
			continue;
		}
		format_index = 0;
		count = 0;
		last = NULL;
	}
	return source;
}

char* my_split_plus(char* source, char* format, char* last_pointer)
{
	last = last_pointer;
	return my_split(source, format);
}

char* get_split_last_pointer()
{
	return last;
}

void put_multi_row(char* buffer, int num)
{
	int i = 0;
	do { strcat(buffer, "\n"); i++; } while (i < num);
}
