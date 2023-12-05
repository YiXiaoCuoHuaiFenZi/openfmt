/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-24
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "import_parser.h"
#include "package_parser.h"
#include <string.h>
#include "lib/str.h"
#include "lib/memory.h"

PbImport* make_import(char* value, PbCommentList* comments)
{
	PbImport* pb_import = (PbImport*)g_malloc(sizeof(PbImport));
	pb_import->value = value;
	pb_import->comments = comments;

	return pb_import;
}