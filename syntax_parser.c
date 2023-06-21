/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse syntax.
**    创建日期：    2022-10-07
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include <string.h>
#include "syntax_parser.h"
#include "lib/str.h"
#include "lib/memory.h"


PbSyntax *parse_syntax(char *line)
{
    // get option name
    char *s1 = sub_str_between_str(line, "=", ";");
    char *value = trim(s1);
    g_free(&s1);

    PbSyntax *pbSyntax = (PbSyntax *) g_malloc(sizeof(PbSyntax));
    pbSyntax->value = value;
    pbSyntax->comments = NULL;

    return pbSyntax;
}
