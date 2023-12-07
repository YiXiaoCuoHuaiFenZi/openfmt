/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse enum.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "../lib/str.h"
#include "../lib/uuid.h"
#include "common.h"
#include "comment_parser.h"
#include "enum_parser.h"
#include "../lib/memory.h"

PbEnum* make_pb_enum(char* name, PbCommentList* comments)
{
	PbEnum* obj = (PbEnum*)g_malloc(sizeof(PbEnum));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();
	free_uuid4(uuid);
	return obj;
}

void parse_pb_enum(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
)
{
	char* str = get_str_until(proto_str, index, '{', false);
	if (str != NULL)
	{
		char* name = trim(str);
		g_free(to_void_ptr(&str));

		PbEnum* pb_enum = make_pb_enum(name, comments);
		g_free(to_void_ptr(&name));

		if (is_empty_stack(object_stack))
		{
			append_linked_list(pb_enum, "PbEnum", protobuf->objects);
		}
		else
		{
			append_linked_list(pb_enum, "PbEnum", get_parent_elements(object_stack));
		}

		// 解析单行注释
		PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_enum->comments, line_comment);
		}

		push_stack(pb_enum, "PbEnum", object_stack);
	}
}