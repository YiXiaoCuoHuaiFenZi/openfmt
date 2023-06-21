/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-21
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include "package_parser.h"
#include <stdlib.h>
#include "lib/str.h"
#include "lib/memory.h"

PbPackage *parse_package(char *line)
{
    char *s = sub_str_between_str(line, "package", ";");
    char *value = trim(s);
    g_free(&s);

    PbPackage *pbPackage = (PbPackage *) g_malloc(sizeof(PbPackage));
    pbPackage->value = value;
    pbPackage->comments = NULL;

    return pbPackage;
}