#include <stdio.h>
#include <stdlib.h>

void check_memory(void* pointer)
{
	if (!pointer)
	{
		printf("ÉêÇëÄÚ´æÊ§°Ü!");
		exit(-100);
	}
}