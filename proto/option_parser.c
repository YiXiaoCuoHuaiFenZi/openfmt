/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：
**    创建日期：    2022-10-21
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include <string.h>
#include "option_parser.h"
#include "common.h"
#include "comment_parser.h"
#include "../lib/memory.h"

void parse_option(const char* proto_str, unsigned long* index, PbCommentList* comments, Protobuf* protobuf)
{
	PbOption* pb_option = (PbOption*)g_malloc(sizeof(PbOption));
	char* sss = get_str_until(proto_str, index, '=', false);
	if (sss != NULL)
	{
		char* name = trim(sss);
		g_free(to_void_ptr(&sss));
		pb_option->name = name;
	}
	char* ssss = get_str_until(proto_str, index, ';', false);
	if (ssss != NULL)
	{
		char* value = trim(ssss);
		g_free(to_void_ptr(&ssss));
		pb_option->value = value;
	}

	pb_option->comments = comments;

	// parse line comment
	PbComment* single_line_comment = pick_up_single_line_comment(proto_str, index);
	if (single_line_comment != NULL)
	{
		append_list(PbCommentNode, pb_option->comments, single_line_comment);
	}

	if (protobuf->options == NULL)
	{
		protobuf->options = create_list(PbOptionNode);
	}
	append_list(PbOptionNode, protobuf->options, pb_option);
}