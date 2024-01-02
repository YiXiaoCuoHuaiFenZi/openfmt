/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message.
**    创建日期：    2022-10-25
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "../lib/str.h"
#include "../lib/uuid.h"
#include "common.h"
#include "comment_parser.h"
#include "message_parser.h"
#include "../lib/memory.h"
#include "../lib/os.h"

PbMessage* make_pb_message(char* name, PbCommentList* comments)
{
	PbMessage* obj = (PbMessage*)g_malloc(sizeof(PbMessage));
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

void parse_message(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		Protobuf* protobuf,
		Stack object_stack
)
{
	char* s = pick_str_until(proto_str + *index, '{', false);
	if (s == NULL)
		fail("target char not found.");

	*index = *index + strlen(s) + 1; // increase extra 1 to skip the '{' charactor.

	char* name = trim(s);
	g_free(to_void_ptr(&s));

	PbMessage* pb_message = make_pb_message(name, comments);
	g_free(to_void_ptr(&name));

	if (is_empty_stack(object_stack))
	{
		append_linked_list(pb_message, "PbMessage", protobuf->objects);
	}
	else
	{
		append_linked_list(pb_message, "PbMessage", get_parent_elements(object_stack));
	}

	// parse line comment
	PbComment* line_comment = pick_up_line_comment(proto_str, index);
	if (line_comment != NULL)
	{
		append_list(PbCommentNode, pb_message->comments, line_comment);
	}

	push_stack(pb_message, "PbMessage", object_stack);
}