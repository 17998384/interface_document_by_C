#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

String* read_file(char* source)
{
	FILE* file = fopen(source, "r");
	if (!file)
	{
		printf("�ļ���ʧ��,�Զ��˳�!");
		exit(-1);
	}
	//�����ַ�������
	String* str = new_string();
	//����������
	char* buffer = (char*)malloc(1024);
	check_memory(str);
	check_memory(buffer);
	//��ȡ�ļ�׷�ӵ��ַ�������
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
	int count = 0;
	char* temp = strtok(source, format);
	while (temp)
	{
		++count;
		temp = strtok(NULL, format);
	}
	return count;
}