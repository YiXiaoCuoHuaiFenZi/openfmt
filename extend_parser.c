/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse Extend.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "common.h"
#include "comment_parser.h"
#include "extend_parser.h"
#include "lib/memory.h"

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
		State* state,
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
		if (state->current_obj != NULL)
		{
			pb_extend->parent_id = get_parent_id(state);
			pb_extend->parent_type = state->current_obj_type;
			append_linked_list(pb_extend, "PbExtend", get_parent_elements(state));
			current_obj_to_parent_obj(state);
		}
		else
		{
			append_linked_list(pb_extend, "PbExtend", protobuf->objects);
		}

		// 解析单行注释
		PbComment* line_comment = pick_up_single_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_extend->comments, line_comment);
		}

		state->l_brace++;
		state->current_obj = pb_extend;
		state->current_obj_type = "PbExtend";
		g_hashtable_put(pb_extend->id, state->current_obj_type, pb_extend, NULL, state->obj_dic);
	}
}