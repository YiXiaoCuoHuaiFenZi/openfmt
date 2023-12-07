/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Extend.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "../lib/str.h"
#include "../lib/uuid.h"
#include "common.h"
#include "comment_parser.h"
#include "extend_parser.h"
#include "../lib/memory.h"

PbExtend* make_pb_extend(char* name, PbCommentList* comments)
{
	PbExtend* obj = (PbExtend*)g_malloc(sizeof(PbExtend));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->parent_type = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();

	free_uuid4(uuid);
	return obj;
}

void parse_extend(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
)
{
	char* extend_str = get_str_until(proto_str, index, '{', false);
	if (extend_str != NULL)
	{
		char* name = trim(extend_str);
		g_free(to_void_ptr(&extend_str));

		PbExtend* pb_extend = make_pb_extend(name, comments);
		g_free(to_void_ptr(&name));

		if (is_empty_stack(object_stack))
		{
			append_linked_list(pb_extend, "PbExtend", protobuf->objects);
		}
		else
		{
			append_linked_list(pb_extend, "PbExtend", get_parent_elements(object_stack));
		}

		// 解析单行注释
		PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_extend->comments, line_comment);
		}

		push_stack(pb_extend, "PbExtend", object_stack);
	}
}