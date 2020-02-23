#include <stdio.h>
#include <stdlib.h>
#include "exception.h"

void check_memory(void* pointer)
{
	if (!pointer)
	{
		printf("…Í«Îƒ⁄¥Ê ß∞‹!");
		exit(-100);
	}
}

void check_null(void* pointer)
{
	if (!pointer)
	{
		printf("NULL POINTER EXCEPTION!");
		exit(-200);
	}
}
