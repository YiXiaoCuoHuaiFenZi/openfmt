/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-21
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <stdlib.h>
#include "comment_parser.h"
#include "package_parser.h"
#include "common.h"
#include "../lib/memory.h"


void parse_package(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	char* ss = get_str_until(proto_str, index, ';', false);
	if (ss != NULL)
	{
		char* value = trim(ss);
		g_free(to_void_ptr(&ss));

		PbPackage* pb_package = (PbPackage*)g_malloc(sizeof(PbPackage));
		pb_package->value = value;
		pb_package->comments = comments;

		// parse line comment
		PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
		if (single_line_comment != NULL)
		{
			append_list(PbCommentNode, pb_package->comments, single_line_comment);
		}
		protobuf->package = pb_package;
	}
}