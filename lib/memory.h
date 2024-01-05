/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   general memory resource management functions
**    Created Date:    2023-05-17
**    Updated Date:    2023-05-17
***********************************************************************************************************************/
#ifndef OPENFMT_MEMORY_H
#define OPENFMT_MEMORY_H

#include  <stdio.h>
#include  <stdlib.h>

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   memory allocation with check.
**    Parameters:      size:   the size of memory to be allocated.
**                     return: void pointer, if NULL, allocate failed with message printed.
**    Created Date:    2023-05-17
**    Updated Date:    2023-05-17
***********************************************************************************************************************/
void* g_malloc(size_t size);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   free memory and set the target pointer to NULL.
**    Parameters:      ptr:    pointer to the target pointer, the memory pointed to by the target pointer will be freed.
**                     return: None.
**    Created Date:    2023-05-17
**    Updated Date:    2023-06-01
***********************************************************************************************************************/
void* g_free(void** ptr);

/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   convert pointer to void**
**    Created Date:    2023-12-06
**    Updated Date:    2023-12-06
***********************************************************************************************************************/
#define to_void_ptr(value) (void**)(value)

#endif //OPENFMT_MEMORY_H
