/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2023-12-04
**    更新日期：    2023-12-04
***********************************************************************************************************************/
#include "os.h"
#include <stdlib.h>
#include <stdio.h>

void fail(const char* message)
{
	printf("%s", message);
	exit(-1);
}