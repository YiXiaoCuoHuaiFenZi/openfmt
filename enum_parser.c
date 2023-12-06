/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse enum.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "common.h"
#include "comment_parser.h"
#include "enum_parser.h"
#include "lib/memory.h"

PbEnum* make_pb_enum(char* name, PbCommentList* comments)
{
	PbEnum* obj = (PbEnum*)g_malloc(sizeof(PbEnum));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->name = str_copy(name);;
	obj->comments = comments;
	obj->elements = create_linked_list();
	free_uuid4(uuid);
	return obj;
}

void parse_pb_enum(
		const char* proto_str,
		unsigned long* index,
		PbCommentList* comments,
		State* state,
		Protobuf* protobuf
)
{
	char* str = get_str_until(proto_str, index, '{', false);
	if (str != NULL)
	{
		char* name = trim(str);
		g_free(&str);

		PbEnum* pb_enum = make_pb_enum(name, comments);
		g_free(&name);
		if (state->current_obj != NULL)
		{
			pb_enum->parent_id = get_parent_id(state);
			pb_enum->parent_type = state->current_obj_type;
			append_linked_list(pb_enum, "PbEnum", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}
		else
		{
			append_linked_list(pb_enum, "PbEnum", protobuf->objects);
		}

		// 解析单行注释
		PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_enum->comments, line_comment);
		}

		state->l_brace++;
		state->current_obj = pb_enum;
		state->current_obj_type = "PbEnum";
		g_hashtable_put(pb_enum->id, state->current_obj_type, pb_enum, NULL, state->obj_dic);
	}
}