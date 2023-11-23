/***********************************************************************************************************************
**    作   者：    一小撮坏分子
**    功能描述：    Parse enum.
**    创建日期：    2022-11-15
**    更新日期：    2023-06-28
***********************************************************************************************************************/
#include "lib/str.h"
#include "lib/uuid.h"
#include "comment_parser.h"
#include "enum_parser.h"
#include "lib/memory.h"

PbEnum* parse_pb_enum(char* line, SQueue line_queue, PbCommentList* comments)
{
	char* s = sub_str_between_str(line, "enum", "{");
	char* name = trim(s);
	g_free(&s);

	PbEnum* obj = (PbEnum*)g_malloc(sizeof(PbEnum));
	UUID* uuid = uuid4();
	obj->id = str_copy(uuid->hex);
	obj->parent_id = NULL;
	obj->name = name;
	obj->comments = comments;
	obj->elements = create_linked_list();
	PbComment* pb_comment = parse_comment(line);
	if (pb_comment != NULL)
	{
		append_list(PbCommentNode, obj->comments, pb_comment);
	}
	de_str_queue(line_queue);
	free_uuid4(uuid);
	return obj;
}


PbEnum* new_parse_pb_enum(char* name, PbCommentList* comments)
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