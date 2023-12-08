/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse OneOf.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "common.h"
#include "comment_parser.h"
#include "oneof_parser.h"
#include "../lib/uuid.h"
#include "../lib/memory.h"

PbOneOf* make_pb_oneof(char* name, PbCommentList* comments)
{

	PbOneOf* obj = (PbOneOf*)g_malloc(sizeof(PbOneOf));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();
	free_uuid4(uuid);
	return obj;
}

void parse_oneof(
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

		PbOneOf* pb_one_of = make_pb_oneof(name, comments);
		g_free(to_void_ptr(&name));

		if (is_empty_stack(object_stack))
		{
			append_linked_list(pb_one_of, "PbOneOf", protobuf->objects);
		}
		else
		{
			append_linked_list(pb_one_of, "PbOneOf", get_parent_elements(object_stack));
		}

		// parse single line comment
		PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_one_of->comments, line_comment);
		}

		push_stack(pb_one_of, "PbOneOf", object_stack);
	}
}