/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse message.
**    创建日期：    2022-10-25
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "common.h"
#include "comment_parser.h"
#include "message_parser.h"
#include "lib/memory.h"

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
		State* state,
		Protobuf* protobuf
)
{
	char* message_str = get_str_until(proto_str, index, '{', false);
	if (message_str != NULL)
	{
		char* name = trim(message_str);
		g_free(&message_str);

		PbMessage* pb_message = make_pb_message(name, comments);
		g_free(&name);
		if (state->current_obj != NULL)
		{
			pb_message->parent_id = get_parent_id(state);
			pb_message->parent_type = state->current_obj_type;
			append_linked_list(pb_message, "PbMessage", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}
		else
		{
			append_linked_list(pb_message, "PbMessage", protobuf->objects);
		}

		// 解析单行注释
		PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_message->comments, line_comment);
		}

		state->l_brace++;
		state->current_obj = pb_message;
		state->current_obj_type = "PbMessage";
		g_hashtable_put(pb_message->id, state->current_obj_type, pb_message, NULL, state->obj_dic);
	}
}