/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:
**    Created Date:    2023-12-04
**    Updated Date:    2023-12-04
***********************************************************************************************************************/
#include "os.h"
#include <stdlib.h>
#include <stdio.h>

void fail(const char* message)
{
	printf("%s", message);
	exit(-1);
}