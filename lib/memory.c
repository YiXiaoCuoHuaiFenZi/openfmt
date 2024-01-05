/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   implementations of general memory resource management functions.
**    Created Date:    2023-05-17
**    Updated Date:    2023-06-01
***********************************************************************************************************************/
#include "memory.h"

void* g_malloc(size_t size)
{
	void* ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("%s\n", "Out of space!");
		exit(-1);
	}

	return ptr;
}

void* g_free(void** ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}

	return NULL;
}