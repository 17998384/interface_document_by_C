#include <stdio.h>
#include <stdlib.h>

void check_memory(void* pointer)
{
	if (!pointer)
	{
		printf("�����ڴ�ʧ��!");
		exit(-100);
	}
}