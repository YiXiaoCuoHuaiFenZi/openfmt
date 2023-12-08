/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-24
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "import_parser.h"
#include "package_parser.h"
#include <string.h>
#include "../lib/str.h"
#include "../lib/memory.h"
#include "common.h"
#include "comment_parser.h"

void parse_import(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	char* target_str = get_str_until(proto_str, index, ';', false);
	if (target_str != NULL)
	{
		char* value = trim(target_str);
		g_free(to_void_ptr(&target_str));

		PbImport* pb_import = (PbImport*)g_malloc(sizeof(PbImport));
		pb_import->value = value;
		pb_import->comments = comments;

		// parse single line comment
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_import->comments, single_line_comment);
		}

		if (protobuf->imports == NULL)
		{
			protobuf->imports = create_list(PbImportNode);
		}
		append_list(PbImportNode, protobuf->imports, pb_import);
	}
}