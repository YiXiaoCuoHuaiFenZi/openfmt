/***********************************************************************************************************************
**    Author:          YiXiaoCuoHuaiFenZi
**    Functionality:   Parse service.
**    Created Date:    2022-11-15
**    Updated Date:    2023-06-28
***********************************************************************************************************************/
#include "common.h"
#include "comment_parser.h"
#include "service_parser.h"
#include "../lib/uuid.h"
#include "../lib/memory.h"
#include "../lib/os.h"

PbService* make_pb_service(char* name, PbCommentList* comments)
{
	PbService* obj = (PbService*)g_malloc(sizeof(PbService));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->name = str_copy(name);
	obj->comments = comments;
	obj->elements = create_linked_list();
	free_uuid4(uuid);
	return obj;
}

void parse_service(
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
	else
		*index = *index + strlen(s) + 1; // increase extra 1 to skip the '{' charactor.

	if (s != NULL)
	{
		char* name = trim(s);
		g_free(to_void_ptr(&s));

		PbService* pb_service = make_pb_service(name, comments);
		g_free(to_void_ptr(&name));

		if (is_empty_stack(object_stack))
		{
			append_linked_list(pb_service, "PbService", protobuf->objects);
		}
		else
		{
			append_linked_list(pb_service, "PbService", get_parent_elements(object_stack));
		}

		// parse line comment
		PbComment* line_comment = pick_up_line_comment(proto_str, index);
		if (line_comment != NULL)
		{
			append_list(PbCommentNode, pb_service->comments, line_comment);
		}

		push_stack(pb_service, "PbService", object_stack);
	}
}