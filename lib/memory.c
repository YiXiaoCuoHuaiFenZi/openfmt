/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    implementations of general memory resource management functions.
**    创建日期：    2023-05-17
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include "memory.h"

void *g_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
    {
        printf("%s\n", "Out of space!");
        exit(-1);
    }

    return ptr;
}

void *g_free(void **ptr)
{
    if (*ptr)
    {
        free(*ptr);
        *ptr = NULL;
    }

    return NULL;
}