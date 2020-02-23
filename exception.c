
//Created by ¸ğÕñ¶« on 2020/02/23
//Copyright	 2020 ¸ğÕñ¶«. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "exception.h"

void check_memory(void* pointer)
{
	if (!pointer)
	{
		printf("ÉêÇëÄÚ´æÊ§°Ü!");
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
