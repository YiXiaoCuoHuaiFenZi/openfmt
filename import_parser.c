/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-24
**    更新日期：    2023-06-01
***********************************************************************************************************************/
#include "import_parser.h"
#include "package_parser.h"
#include <string.h>
#include "lib/str.h"
#include "lib/memory.h"

PbImport *parse_import(char *line)
{
    char *s = sub_str_between_str(line, "import", ";");
    char *v = trim(s);
    g_free(&s);

    PbImport *pbImport = (PbImport *) g_malloc(sizeof(PbImport));
    pbImport->value = v;
    pbImport->comments = NULL;

    return pbImport;
}