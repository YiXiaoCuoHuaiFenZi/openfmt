/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-21
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "lib/str.h"
#include "option_parser.h"
#include "lib/memory.h"

PbOption *parse_option(char *line)
{
    // get option name
    char *s1 = sub_str_between_str(line, "option", "=");
    char *name = trim(s1);

    // get option value
    char *s2 = sub_str_between_str(line, "=", ";");
    char *value = trim(s2);

    g_free(&s1);
    g_free(&s2);

    PbOption *pbOption = (PbOption *) g_malloc(sizeof(PbOption));
    pbOption->name = name;
    pbOption->value = value;
    pbOption->comments = NULL;

    return pbOption;
}