/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-21
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "package_parser.h"
#include <stdlib.h>
#include "lib/str.h"
#include "lib/memory.h"

PbPackage* parse_package(char* line)
{
	char* s = sub_str_between_str(line, "package", ";");
	char* value = trim(s);
	g_free(&s);

	PbPackage* pb_package = (PbPackage*)g_malloc(sizeof(PbPackage));
	pb_package->value = value;
	pb_package->comments = NULL;

	return pb_package;
}